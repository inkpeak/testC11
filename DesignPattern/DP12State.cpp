#include"heads.h" 
/*
* 状态模式
* 是把所有的状态抽象成一个个具体的类,然后继承一个抽象状态类,在
* 每一个状态类内封装对应状态的行为，符合开放封闭原则，当增加
* 新的状态或减少状态时，只需修改关联的类即可
*/ 
class Context;

//抽象状态类  
class AbsState {
public:
	virtual void Handle(Context context) = 0;
	string name;
};
 
//上下文
class Context
{
public:
	Context() {}
	Context(AbsState* state) :m_state(state) {};

	void setState(AbsState* as) {
		m_state = as;
		cout << "state="<<as->name << endl;
	};

	AbsState* getState() {
		return m_state;
	};

	void Request() {
		m_state->Handle(*this);
	};
private:
	AbsState* m_state;
};
 

//具体状态A
class ConcreteStateA :public AbsState {
public:
	ConcreteStateA() {
		name = "caseA";
	};

	void Handle(Context context) {
		context.setState(this);
	}

};

//具体状态B
class ConcreteStateB :public AbsState {
public:
	ConcreteStateB() {
		name = "caseB";
	};
	void Handle(Context context) {
		context.setState(this);
	}

};


//具体状态C
class ConcreteStateC :public AbsState {
public:
	ConcreteStateC() {
		name = "caseC";
	};

	void Handle(Context context) {
		context.setState(this);
	}

};