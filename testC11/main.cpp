#include"exam3.cpp" 
#include"exam.cpp"
#include"testptr.cpp"
using std::vector; 

//测试仿照sharedptr实现的智能指针
void test2() {
	string* one = new string();
	testptr1<string> p1(one);
}

int main()
{
	try
	{
		tsetptr a;
		//a.testshared_ptr();
		//exam::test4();
		//test_class::tset2();
		//testTemplate::test3();
		testoverride::A1* a1 = new testoverride::A1();
		cout << "******" << endl;
		delete a1;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	system("pause");
	return 0;
}