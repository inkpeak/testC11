#include<iostream>
#include<windows.h>
#include<thread>
#include<string>
using std::endl;
using std::cout;
using std::cin;

namespace exam3 {

	//������������ַ���ֵ
	void out(std::string key, std::string value) {
		std::cout << key << value << std::endl;
	}

	int test() {
		double d = 3.1;
		const int& i = d;
		//�ȼ����������� ���ð�ʧ��
		// const int temp =dval;
		// const int &i=temp;
		return 0;
	}

	//����50-100���ܺ�
	void test1() {
		int i = 50, sum = 0;
		while (i < 100)
		{
			sum += i++;
		}
		cout << sum << endl;
	}

	//��ӡһ���ַ���
	void test2()
	{
		std::string head, end;
		end = "</blockquote>";
		out("", end);
	}


	void init(int num)
	{
		out("id:", std::to_string(num));
	}



	//�߳�˯��num��
	void timepp(int num)
	{
		Sleep(num * 1000);
		out("sleep/s", std::to_string(num));
	}

}