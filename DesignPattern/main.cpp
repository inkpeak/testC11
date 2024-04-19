#include"heads.h" 
#include"DP01SimpleFactory.cpp" 
#include"DP02Strategy.cpp" 
#include"DP03Decorator.cpp" 
#include"DP04Proxy.cpp" 
#include"DP05FactoryMethod.cpp" 
#include"DP06Prototype.cpp"  
#include"DP07TemplateMethod.cpp" 
#include"DP08Facade.cpp" 
#include"DP09Builder.cpp" 
#include"DP10PublishSubscribe.cpp" 
#include"DP11AbstractFactory.cpp" 
#include"DP12State.cpp" 
#include"DP13Adapter.cpp" 
#include"DP14Memento.cpp" 
#include"DP15Composite.cpp" 
#include"DP16Iterator.cpp" 
#include"DP17Singleton.cpp" 
#include"DP18Bridge.cpp" 
#include"DP19Command.cpp" 
#include"DP20ChainOfResponsibility.cpp" 
#include"DP21Mediator.cpp" 
#include"DP22Flyweight.cpp" 
#include"DP23Interpreter.cpp" 
#include"DP24Visitor.cpp" 

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

//��Ϊ��ģʽ
void testDP07() {
	AbsClass* a = new ConcreteClass1();
	a->display();
	AbsClass* b = new ConcreteClass2();
	b->display();
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
	DP11::AbsFactory* af1 = new DP11::ConcreteFactory1();
	DP11::AbsFactory* af2 = new DP11::ConcreteFactory2();
	DP11::AbsProductA ada = af1->CreateProductA();
}

void testDP12() {
	Context ct;
	AbsState* as1 = new ConcreteStateA();
	AbsState* as2 = new ConcreteStateB();
	AbsState* as3 = new ConcreteStateA();
	ct.setState(as1);
	ct.setState(as2);
	ct.setState(as3);
}

void testDP13() {
	Adaptee adee;
	Adapter ader(adee);
	ader.Request();
}

void testDP14() { 
	//�������������
	Originator o;
	o.SetMemento(0);
	//�����������
	CareTaker c;
	c.setMemento(o.CreateMemento());
	//�ı����״̬
	o.SetMemento(1);
	//�ָ�״̬
	o.SetMemento(c.getMemento());
}

//��Ϊ�����ģʽ
void testDP15() {
	Component* root = new Composite("root");
	Component* l1 = new Composite("L1");
	Component* p = new Leaf("A");
	root->Add(p);
	root->Add(l1);
	root->Display();
}

//������Ϊ��ģʽ
void testDP16() {
	Children child;
	child.Push("Tom");
	child.Push("John");
	child.Push("Json");

	AbsIterator* itr = child.CreateIterator();
	std::cout << "First man:" << itr->first() << std::endl;
}

void testDP17() {
	try
	{ 
		Singleton* si = Singleton::GetInstance();
		Singleton1* s2 = Singleton1::GetInstance();
	}
	catch (const std::exception&e)
	{
		e.what();
	}
}

//����ṹ��ģʽ
void testDP18() {
	OS* pIOS1 = new IOSSubSystem1(); //����һ������ϵͳ
	Phone* iPhone4 = new iPhone(pIOS1);//Ӧ�õ����ֻ���
	iPhone4->SetOS();

	OS* pIOS2 = new IOSSubSystem2();//����һ������ϵͳ
	Phone* iPhone6 = new iPhone(pIOS2);//Ӧ�õ����ֻ���
	iPhone6->SetOS();

	OS* pSaiBian1 = new SaiBianSubSystem1();//����һ������ϵͳ
	Phone* Nokia1 = new Nokia(pSaiBian1);//Ӧ�õ����ֻ���
	Nokia1->SetOS();

	OS* pSaiBian2 = new SaiBianSubSystem2();//����һ������ϵͳ
	Phone* Nokia2 = new Nokia(pSaiBian2);//Ӧ�õ����ֻ���
	Nokia2->SetOS();

	DELETE_OBJECT(iPhone4);
	DELETE_OBJECT(iPhone6);
	DELETE_OBJECT(Nokia1);
	DELETE_OBJECT(Nokia2);
}

void testDP19() {
	Receiver* rece = new Receiver();

	AbsCommand* com1 = new ConcreteCmd1(rece);
	AbsCommand* com2 = new ConcreteCmd2(rece);
	com1->Execute();
	com2->Execute();
}

void testDP20() { 
	shared_ptr<AbsHandler> pHandle_2 = make_shared<ConcreteHandler2>();
	shared_ptr<AbsHandler> pHandle_1 = make_shared<ConcreteHandler1>(pHandle_2);
	pHandle_1->HandleRequest(99);
}

void testDP21() {
	shared_ptr<AbsMediator> mediator = make_shared<ConcreteMediator>();

	shared_ptr<Colleague> colleague1 = make_shared<ConcreteColleague>("Alice");
	shared_ptr<Colleague> colleague2 = make_shared<ConcreteColleague>("Bob");
	shared_ptr<Colleague> colleague3 = make_shared<ConcreteColleague>("Charlie");

	mediator->addColleague(colleague1);
	mediator->addColleague(colleague2);
	mediator->addColleague(colleague3);

	colleague1->setMediator(mediator);
	colleague2->setMediator(mediator);
	colleague3->setMediator(mediator);

	colleague1->send("Hello everyone!");
}

//�ṹ��ģʽ
void testDP22() {
	FlyweightFactory factory;
	shared_ptr<Flyweight> flyweight1 = factory.getConcreteFlyweight("A");
	shared_ptr<Flyweight> flyweight2 = factory.getConcreteFlyweight("B");
	shared_ptr<Flyweight> flyweight3 = factory.getUnsharedConcreteFlyweight("C");
	flyweight1->operation("oper1");
	flyweight2->operation("oper2");
	flyweight3->operation("oper3");
}

void testDP23() {
	string expStr = "a+b-c+d";
	map<char, int> var;
	var.insert({ 'a', 5 });
	var.insert({ 'b', 2 });
	var.insert({ 'c', 1 });
	var.insert({ 'd', 6 });

	Expression* expression = analyse(expStr);
	int result = expression->interpreter(var);
	cout << result << endl;//12
	release(expression); 
}

//��Ϊ�����ģʽ
void testDP24() {
	Array array;
	array.addData(1);
	array.addData(2);

	Linked linked;
	linked.addData(3);
	linked.addData(4);

	DisplayVisitor displayVisitor;

	array.accept(displayVisitor);
	linked.accept(displayVisitor);
}

int main() {
	testDP18();
	system("pause");
	return 0;
}