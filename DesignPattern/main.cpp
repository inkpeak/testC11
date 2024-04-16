#include"heads.h"
#include"DP01SimpleFactory.cpp" 
#include"DP02Strategy.cpp" 

void testDP01() {
	AbsFactory* fact;
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

}

void testDP04() {

}

void testDP() {

}

int main() {
	testDP02();
	system("pause");
	return 0;
}