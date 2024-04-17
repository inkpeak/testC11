#include"heads.h"


/*
* 工厂方法模式
* 工厂方法模式的意义是定义一个创建产品对象的工厂接口,
* 将实际创建工作推迟到子类当中
* 4种角色
* 抽象工厂
* 具体工厂类，对应具体产品
* 抽象产品类
* 具体产品类
* 优点：
* 1.使系统在不修改具体工厂角色的情况下引进新的产品
*/
class AbsLeiFeng
{
public:
	virtual void doSomething() = 0;
};

class stuents :public AbsLeiFeng
{
public:
	void doSomething() {}
};


class Volunter :public AbsLeiFeng
{
public:
	void doSomething() {}
};


class AbsFactory
{
	virtual AbsLeiFeng* createPerson() = 0;
};

class VolunterFactory : public AbsFactory
{
public:
	AbsLeiFeng* createPerson()
	{
		cout << "Volunter" << endl;
		return  new Volunter;
	}
};

class StuentsFactory : public AbsFactory
{
public:
	AbsLeiFeng* createPerson()
	{
		cout << "stuents" << endl;
		return  new stuents();
	}
};