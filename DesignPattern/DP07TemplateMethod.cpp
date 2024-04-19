#include"heads.h"

/*
* 
* 模板方法模式。
* 定义操作中算法的骨架，将一些步骤延迟到子类
*  使子类可以不改变算法结构而修改算法步骤
* 
* 抽象模板中包含三种类型的方法： 基本方法、模板方法和钩子方法(Hook Method）
* 基本方法也叫做基本操作，是由子类实现的方法，并且在模板方法被调用。
* 模板方法是核心方法，不允许子类重写，所以都会加上final修饰符，
* 可以有一个或几个，一般是一个具体方法框架，按照固定的流程对基本方法的调度
* 钩子方法为了让模板方法的执行结果的更好地适应因外界条件改变。 
* 
* 优点
* 1.良好的扩展性，封装不变部分，扩展可变部分，把认为是不变部分的算法封装到父类实现，而可变部分的则可以通过继承来继续扩展。
* 2.提取公共部分代码，便于维护，减小维护升级成本，基本操作由父类定义，子类实现
* 基本方法是由子类实现的，因此子类可以通过扩展的方式增加相应的功能，符合开闭原则
* 
* 缺点
* 通常抽象类是负责声明某一类的事物的共同属性和抽象方法，实现类则是完成定义
* 具体的特性和方法。但是模板方法模式却颠倒了，抽象类定义了部分抽象方法，
* 由子类实现，子类执行的结果影响了父类的结果，也就是子类对父类产生了影响。
* 每个不同的实现都需要定义一个子类，这会导致类的个数增加，系统更加庞大，
* 设计也更加抽象，但是更加符合“单一职责原则”，使得类的内聚性得以提高
* 
*/

class AbsClass
{
public:
	virtual void sing() = 0;
	virtual void dance() = 0;
	virtual void rap() = 0;
	void display()
		//子类的公共行为
	{
		sing();
		dance();
		rap();
	}
};

class ConcreteClass1 :public AbsClass
{
public:
	ConcreteClass1() {}

	void sing() {
		cout << "流行音乐" << endl;
	}

	void dance() { 
		cout << "恰恰舞" << endl; 
	} 

	void rap() {
		cout << "三分球" << endl;
	}
};
 
class ConcreteClass2 :public AbsClass
{
public:
	void sing() {
		cout << "古典音乐" << endl;
	}

	void dance() { 
		cout <<"民族舞" << endl;
	}

	void rap() {
		cout <<"两分球" << endl;
	}
};
 