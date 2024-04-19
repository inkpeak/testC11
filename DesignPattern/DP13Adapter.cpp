#include"heads.h"

/*
* 
* 适配器模式
* 将一个类的接口转换成客户希望的另一个接口.Adapter 模式使得原本由于接口不兼容
* 而不能在一起工作的那些类可以一起工作。
* 
* 主要应用于希望复用一些现存的类，但是接口又与复用环境要求不一致的情况  
*/

//面向用户的接口类
class AbsTarget {

public:
	virtual void Request() = 0;
};

//被适配的对象
class Adaptee {
public:
	void method() {
		std::cout << "me" << std::endl;
	}
};
 
//适配器
class Adapter :public AbsTarget {

	Adaptee adaptee;
public:

	Adapter(Adaptee ada) :adaptee(ada) {
		adaptee = ada;
	}

	void Request() {
		adaptee.method();
	}
};
