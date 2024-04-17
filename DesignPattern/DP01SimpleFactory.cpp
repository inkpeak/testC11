#include"heads.h"

/*
* 简单工厂模式
* 定义一个工厂类，他可以根据参数的不同返回不同产品类实例，
* 被创建的实例通常都具有共同的父类.
* 工厂对象的工厂函数根据用户输入,自动new出一个子类对象并返回其父类的指针
* 这样利用父类的指针执行父类的虚函数,就可以动态绑定子类的重写函数,
* 从而实现多态.
* 优点：
* 通过一个含参的工厂方法，我们可以实例化任何产品类 
* 所以简单工厂有一个别名：上帝类。
* 缺点：
* 任何”东西“的子类都可以被生产，负担太重。当所要生产产品种类
* 非常多时，工厂方法的代码量可能会很庞大。在遵循开闭原则
* （对拓展开放，对修改关闭）的条件下，简单工厂对于增加新的产品，
* 无能为力。因为增加新产品只能通过修改工厂方法来实现。 
* 
*/

namespace DP01 {
	//运算抽象类
	class Operations
	{
	public:
		double _numberA = 0;
		double _numberB = 0;

		void set(double a, double b)
		{
			_numberA = a;
			_numberB = b;
		}
		virtual double GetResult() { return 0; }
	};

	//加法类
	class OperationAdd : public Operations
	{
	public:
		double GetResult()
		{
			return _numberA + _numberB;
		}
	};

	//减法类
	class OperationSub : public Operations
	{
	public:
		double GetResult()
		{
			return _numberA - _numberB;
		}
	};

	//乘法类
	class OperationMul : public Operations
	{
	public:
		double GetResult()
		{
			return _numberA * _numberB;
		}
	};

	//除法类
	class OperationDiv : public Operations
	{
	public:
		double GetResult()
		{
			if (_numberB == 0)
				throw std::exception("除数为0");
			else
			{
				return _numberA / _numberB;
			}
		}
	};


	class AbsFactory
	{
	public:
		static Operations* createOperate(char operate)
		{
			Operations* oper = nullptr;

			if ('+' == operate) oper = new OperationAdd();
			if ('-' == operate) oper = new OperationSub();
			if ('*' == operate) oper = new OperationMul();
			if ('/' == operate) oper = new OperationDiv();

			return oper;
		}
	};

}
