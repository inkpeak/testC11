#include"heads.h"

/*
* 
* 备忘录模式
* 在不破坏封装性的前提下，捕获一个对象的内部状态,并在对象之外保存 
* 缺点在于如果对象的状态数据较大，则内存消耗大
* 
* 结构
* 备忘录类，存储原发器对象的内部状态。原发器根据需要决定备忘录
*  存储原发器的哪些内部状态，防止原发器以外的其他对象访问备忘录。
* 原发器类，创建一个备忘录，记录它的当前时刻得内部状态;使用备忘录恢复内部状态
* 管理者类,负责保存备忘录
* 
*/
  
//备忘录类
class Memento {
	int m_state;
public:
	Memento() {}

	Memento(int id) :m_state(id) {}

	int getState() {
		return m_state;
	}
};

//原发器类
class Originator {
	int m_state;
public:
	Originator() {}
	void SetMemento(Memento ento) {
		m_state = ento.getState();
	}
	Memento CreateMemento() {
		Memento tmp(m_state);
		return  tmp;

	}
};

//管理者类
class CareTaker {
	Memento m_mento;
public: 
	CareTaker() {};

	Memento getMemento() {
		return m_mento;
	}

	void setMemento(Memento ento) {
		m_mento = ento;
	 }
};