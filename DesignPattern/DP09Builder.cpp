#include"heads.h"

/*
* 建造者模式
* 对象创建型模式之一，用来隐藏复合对象的创建过程.将一个复杂对象的构造
* 与它的表示分离，使同样的构建过程可以创建不同的表示
* 
* 抽象建造者类: 为创建产品各个部分，统一抽象接口
* 具体建造者类：具体实现抽象建造者各个部件的接口
* （可选）抽象产品类：为产品提供统一接口
* 具体产品类:实现抽象产品类的接口。
* （重要）指挥类：负责安排和调度复杂对象的各个建造过程
*/


//建造对象的抽象基类
class PersonBuilder
{
public:
	virtual void buildHead() {}
	virtual void buildBody() {}
	virtual void buildLeg() {}
	virtual void buildFoot() {}
};

//建造对象的具体实现类
class PersonThinBuilder :PersonBuilder
{
	void buildHead() {
		std::cout << "thin" << std::endl;
	}
	void buildBody() {}
	void buildLeg() {}
	void buildFoot() {}
};

//面向用户的类，决定建造什么对象
class Director
{
	PersonBuilder pb;
public:
	Director(PersonBuilder p) :pb(p) {}

	void create() {
		pb.buildHead();
		pb.buildBody();
		pb.buildLeg();
		pb.buildFoot();
	}
};