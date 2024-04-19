#include"heads.h"

/*
* 
* 抽象工厂模式
* 提供一个接口，可以创建一系列相关的对象而无需指定他们的类 
* 工厂方法模式的扩展和延伸
* 
* 优点：
* 1.产品族一致性:抽象工厂模式可以确保一次性创建一整套相关的产品,
*   保证了这些产品之间的一致性，例如风格、主题等。
* 2.易于替换产品系列:由于抽象工厂模式将产品的创建封装在工厂类中,
*   因此可以轻松替换整个产品系列，而不需要修改客户端代码。
* 3.隐藏具体产品的实现:客户端只需要知道抽象产品的接口,而不需要关心
*   具体产品的实现细节.这样可以降低客户端和具体产品类之间的耦合度.
* 4.符合开闭原则:抽象工厂模式可以轻松地添加新的产品族,而不需要
*   修改现有的代码，符合开闭原则。
* 5.提供一致的接口:抽象工厂模式提供了一致的接口来创建产品,这样可以
*   让客户端代码更加简洁和易于维护。
* 
* 抽象工厂模式缺点：
* 1.不易扩展产品等级结构:如果需要添加新的产品等级结构,比如增加新的
*   按钮类型,需要修改抽象工厂接口和所有的具体工厂类,这可能会影响现有的代码 
* 2.产品变化频率高:如果产品的变化频率较高,抽象工厂模式可能会导致系统
*   变得复杂,因为每次添加新产品都需要修改抽象工厂接口和所有的具体工厂类.
* 3.增加了系统的抽象性和理解难度：抽象工厂模式引入了额外的抽象层次，
*   可能会增加系统的复杂性和理解难度
*/


namespace DP11 {

	//轿车
	class AbsProductA
	{
	public:
		AbsProductA() {}
		~AbsProductA() {}
	};

	//SUV
	class AbsProductB
	{
	public:
		AbsProductB() {}
		~AbsProductB() {}
	};

	//大众轿车
	class ProductA1 :public AbsProductA
	{
	public:
		ProductA1() {}
		~ProductA1() {}
	};

	//小米轿车
	class ProductA2 :public AbsProductA
	{
	public:
		ProductA2() {}
		~ProductA2() {}
	};

	//大众SUV
	class ProductB1 :public AbsProductB
	{
	public:
		ProductB1() {}
		~ProductB1() {}

	};

	//小米SUV
	class ProductB2 :public AbsProductB
	{
	public:
		ProductB2() {}
		~ProductB2() {}

	};

	//汽车厂 
	class AbsFactory {
	public:
		AbsFactory() {}
		~AbsFactory() {}

		virtual AbsProductA CreateProductA() {
			AbsProductA a;
			return   a;
		}

		virtual AbsProductB CreateProductB() {
			AbsProductB a;
			return   a;
		}
	};

	//北京汽车厂
	class ConcreteFactory1 :public AbsFactory
	{
	public:
		ConcreteFactory1() {}
		~ConcreteFactory1() {}
		AbsProductA CreateProductA() {
			ProductA1 a;
			return   a;
		}

		AbsProductB CreateProductB() {
			ProductB1 a;
			return   a;
		}
	};

	//南京汽车厂
	class ConcreteFactory2 :public AbsFactory
	{
	public:
		ConcreteFactory2() {}
		~ConcreteFactory2() {}
		AbsProductA CreateProductA() {
			ProductA2 a;
			return   a;
		}

		AbsProductB CreateProductB() {
			ProductB2 a;
			return   a;
		}
	};

}