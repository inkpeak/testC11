#include"heads.h" 

/*
* 
* 装饰模式
* 装饰模式是动态地将责任添加到具体对象上而不影响这个对象所对应的类
* 或者基类的方法。
* 有4个组成角色：
* Component是定义一个对象接口，可以给这些对象动态地添加职责。
* ConcreteComponent是定义了一个具体的对象,可以给这个对象添加一些职责。
* Decorator,装饰抽象类,继承了Component,从外类来扩展Component类的功能，
  但对于Component来说,是无需知道Decorator的存在的。
* ConcreteDecorator就是具体的装饰对象，起到给Component添加职责的功能
* 二、应用场景：
  a.需要动态地给一个对象添加功能,且这些功能也可以动态地被撤销时。
  b.当使用继承不利于系统的维护和扩展时或者直接不允许使用继承的方式
  对系统进行扩展时。
  c.一个原始类同时生成了多个对象，在不影响其他对象的前提下，
  以动态、透明的方式为单个对象添加新的职责，而不修改原始类。
	以游戏中服饰系统为例
*/

//服饰系统接口
class AbsComponent
{
	vector<string> clothes;
public:
	virtual ~AbsComponent() {};

	// 为后续的各种装饰操作提供一个统一的接口
	virtual void Operation()=0;

	void setClothes(string s) {
		clothes.push_back(s);
	}

	vector<string> getClothes() {
		return clothes;
	} 
};

//称号
class ConcreteComponent : public  AbsComponent
{
public:
	void Operation()
	{
		setClothes("Lv.1");
		cout << "Lv.1" << endl;
	}
};

//装饰抽象类
class AbsDecorator : public AbsComponent
{
	AbsComponent* m_com=nullptr;
public:
	AbsDecorator() {}
	AbsDecorator(AbsComponent* ac) {
		m_com = ac;
	}

	void dress(string s) { 
		setClothes(s);
	}

	virtual ~AbsDecorator() {};
	 
	virtual void Operation()=0;

protected: 
};

//头部
class ConcreateDecoratorA : public AbsDecorator
{
public:
	ConcreateDecoratorA(){};

	ConcreateDecoratorA(AbsComponent* ac):AbsDecorator(ac) { 
	}
	void Operation() {
		dress("head");
		cout << "head" << endl;
	}
};


//胸部
class ConcreateDecoratorB : public AbsDecorator
{
public:
	ConcreateDecoratorB() {};

	ConcreateDecoratorB(AbsComponent* ac) :AbsDecorator(ac) {
	}
	void Operation() {
		dress("body");
		cout << "body" << endl;
	}
};


//腿部
class ConcreateDecoratorC : public AbsDecorator
{
public:
	void Operation() {
		dress("leg");
		cout << "leg" << endl;
	}
};


//脚部
class ConcreateDecoratorD : public AbsDecorator
{
public:
	void Operation() {
		dress("foot");
		cout << "foot" << endl;
	}
};


//手臂
class ConcreateDecoratorE : public AbsDecorator
{
public:
	void Operation() {
		dress("arm");
		cout << "arm" << endl;
	}
};
