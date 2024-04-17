#include"heads.h"
#include"DP01SimpleFactory.cpp" 
#include"DP02Strategy.cpp" 
#include"DP03Decorator.cpp" 
#include"DP04Proxy.cpp" 
#include"DP05FactoryMethod.cpp" 
#include"DP06Prototype.cpp" 
#include"DP08Facade.cpp" 
#include"DP09Builder.cpp" 
#include"DP10PublishSubscribe.cpp" 
#include"DP11AbstractFactory.cpp" 

void testDP01() {
	using namespace DP01;
	DP01::AbsFactory* fact;
	Operations* oper; 
	char ch;
	cin >> ch;

	oper=fact->createOperate(ch);
	oper->set(1,2);
	int num = oper->GetResult(); 
	cout << num << endl;
}

void testDP02() {
	AbsStractgy* as = new ConcreteStrategyA();
	as = new ConcreteStrategyB();
	ConcreteStrategy cs(as);
	int i=cs.GetResult(300);
}

void testDP03() {
	AbsComponent* ac = new ConcreteComponent();
	ac->Operation();

	ac = new ConcreateDecoratorA(ac);
	ac->Operation();

	 ac = new ConcreateDecoratorB(ac);
	 ac->Operation();
	 vector<string> info= ac->getClothes() ;
	 cout << "++++++++++" << endl;
	 for (string i : info) {/*/������*/
		 cout << i << endl;
	 }
}

void testDP04() { 
	RealMan man;
	Proxy pman(man);
	pman.Request();
}

void testDP05() { 
	AbsFactory* factory = new StuentsFactory();
	AbsLeiFeng* person1 = new stuents();
}

void testDP06() { 
	//1. �������������
	ShapeType obj;

	//2. �Ӷ�����л�ö���Ŀ�¡�壨getShape��������ĳ������Ŀ�¡��
	Shape* m_circle = obj.getShape("Բ��");
	Shape* m_Square = obj.getShape("������");
	Shape* m_Rectangle = obj.getShape("����");
	 
	cout << m_circle->getid() << " : " << m_circle->getType() << endl;
	cout << m_Square->getid() << " : " << m_Square->getType() << endl;
	cout << m_Rectangle->getid() << " : " << m_Rectangle->getType() << endl;
	  
}

void testDP07() { 
}

void testDP08() { 
	Facade a;
	a.method1();
}

void testDP09() { 
	PersonBuilder pb;
	Director d(pb);
	d.create();
}

void testDP10() {
	// �������۲���
	Subject* sub = new ConcreteSubject();

	// �����۲���
	Observer* ober =
		new ConcreteObserver(sub, "test");

	Observer* ober1 =
		new ConcreteObserver(sub, "test1");
	Observer* ober2 =
		new ConcreteObserver(sub, "test2");

	// ע��۲���
	sub->attach(ober );
	sub->attach(ober1);
	sub->attach(ober2);
	sub->Notify();
}

void testDP11() {

}

void testDP12() {

}

void testDP() {

}

int main() {
	testDP10();
	system("pause");
	return 0;
}