#include"heads.h" 
/*
* ״̬ģʽ
* �ǰ����е�״̬�����һ�����������,Ȼ��̳�һ������״̬��,��
* ÿһ��״̬���ڷ�װ��Ӧ״̬����Ϊ�����Ͽ��ŷ��ԭ�򣬵�����
* �µ�״̬�����״̬ʱ��ֻ���޸Ĺ������༴��
*/ 
class Context;

//����״̬��  
class AbsState {
public:
	virtual void Handle(Context context) = 0;
	string name;
};
 
//������
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
 

//����״̬A
class ConcreteStateA :public AbsState {
public:
	ConcreteStateA() {
		name = "caseA";
	};

	void Handle(Context context) {
		context.setState(this);
	}

};

//����״̬B
class ConcreteStateB :public AbsState {
public:
	ConcreteStateB() {
		name = "caseB";
	};
	void Handle(Context context) {
		context.setState(this);
	}

};


//����״̬C
class ConcreteStateC :public AbsState {
public:
	ConcreteStateC() {
		name = "caseC";
	};

	void Handle(Context context) {
		context.setState(this);
	}

};