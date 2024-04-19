#include"heads.h"

/*
* 解释器模式
* 定义
* 给定一个语言，定义它的文法的一种表示，并定义一个解释器,
* 这个解释器使用该表示来解释语言中的句子
*
* 定义数据转换类Context，定义获取数据接口函数getValue()，
*   以及定义转换数据map<string, int> datas；
* 定义表达式类Expression，定义一个解释器抽象接口函数
interpreter(Context*)=0，同时定义一个左右子树指针Expression left，
*    Expression right；
*  定义具体非终结符表达式类，比如乘法类MultiExpression，重写接口函数int interpreter(Context)；
*  定义具体非终结符表达式类，比如除法类DivisionExpression，重写接口函数int interpreter(Context)；
*  定义具体终结符表达式类，比如TerminalExpression，重写接口函数int interpreter(Context*)终止递归调用，同时定义成员变量（转换后的值，也就是键值对的值）int value；
*
*
*/


class Expression {
public:
	virtual int interpreter(map<char, int> var) = 0;
	virtual ~Expression() {}
};

// 变量表达式
class VarExpression : public Expression {
	char key;
public:
	VarExpression(const char& key) {
		this->key = key;
	}
	int interpreter(map<char, int> var) override {
		return var[key];
	}
};

// 符号表达式
class SymbolExpression : public Expression {
	// 运算符
protected:
	Expression* left;
	Expression* right;
public:
	SymbolExpression(Expression* left, Expression* right) :
		left(left), right(right) {}
};

// 加法运算
class AddExpression : public SymbolExpression {
public:
	AddExpression(Expression* left, Expression* right) :
		SymbolExpression(left, right) {}
	int interpreter(map<char, int> var) override {
		return left->interpreter(var) + right->interpreter(var);
	}
};


// 减法运算
class SubExpression : public SymbolExpression {
public:
	SubExpression(Expression* left, Expression* right) :
		SymbolExpression(left, right) {}
	int interpreter(map<char, int> var) override {
		return left->interpreter(var) + right->interpreter(var);
	}
};


Expression* analyse(string expStr) {
	stack<Expression*> expStack;
	Expression* left = nullptr;
	Expression* right = nullptr;
	for (int i = 0; i < expStr.size(); i++) {
		switch (expStr[i]) {
		case '+':
			// 加法运算
			left = expStack.top();
			right = new VarExpression(expStr[++i]);
			//expStack.push({ left, right });
			expStack.push(left);
			expStack.push(right);
			break;
		case '-':
			// 减法运算
			left = expStack.top();
			right = new VarExpression(expStr[++i]);
			//expStack.push({ left, right });
			expStack.push(left);
			expStack.push(right);
			break;
		default:
			// 终结表达式
			expStack.push(new VarExpression(expStr[i]));
		}
	}
	Expression* expression = expStack.top();
	return expression;
}



void release(Expression* expression) {
	// 释放表达式树的节点内存...
}