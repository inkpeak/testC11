#include"heads.h"

/*
* ������ģʽ
* ����
* ����һ�����ԣ����������ķ���һ�ֱ�ʾ��������һ��������,
* ���������ʹ�øñ�ʾ�����������еľ���
*
* ��������ת����Context�������ȡ���ݽӿں���getValue()��
*   �Լ�����ת������map<string, int> datas��
* ������ʽ��Expression������һ������������ӿں���
interpreter(Context*)=0��ͬʱ����һ����������ָ��Expression left��
*    Expression right��
*  ���������ս�����ʽ�࣬����˷���MultiExpression����д�ӿں���int interpreter(Context)��
*  ���������ս�����ʽ�࣬���������DivisionExpression����д�ӿں���int interpreter(Context)��
*  ��������ս�����ʽ�࣬����TerminalExpression����д�ӿں���int interpreter(Context*)��ֹ�ݹ���ã�ͬʱ�����Ա������ת�����ֵ��Ҳ���Ǽ�ֵ�Ե�ֵ��int value��
*
*
*/


class Expression {
public:
	virtual int interpreter(map<char, int> var) = 0;
	virtual ~Expression() {}
};

// �������ʽ
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

// ���ű��ʽ
class SymbolExpression : public Expression {
	// �����
protected:
	Expression* left;
	Expression* right;
public:
	SymbolExpression(Expression* left, Expression* right) :
		left(left), right(right) {}
};

// �ӷ�����
class AddExpression : public SymbolExpression {
public:
	AddExpression(Expression* left, Expression* right) :
		SymbolExpression(left, right) {}
	int interpreter(map<char, int> var) override {
		return left->interpreter(var) + right->interpreter(var);
	}
};


// ��������
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
			// �ӷ�����
			left = expStack.top();
			right = new VarExpression(expStr[++i]);
			//expStack.push({ left, right });
			expStack.push(left);
			expStack.push(right);
			break;
		case '-':
			// ��������
			left = expStack.top();
			right = new VarExpression(expStr[++i]);
			//expStack.push({ left, right });
			expStack.push(left);
			expStack.push(right);
			break;
		default:
			// �ս���ʽ
			expStack.push(new VarExpression(expStr[i]));
		}
	}
	Expression* expression = expStack.top();
	return expression;
}



void release(Expression* expression) {
	// �ͷű��ʽ���Ľڵ��ڴ�...
}