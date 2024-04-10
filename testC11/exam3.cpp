#include<iostream>
#include<windows.h>
#include<thread>
#include<string>
using std::endl;
using std::cout;
using std::cin;

namespace exam3 {

	//依次输出两个字符串值
	void out(std::string key, std::string value) {
		std::cout << key << value << std::endl;
	}

	int test() {
		double d = 3.1;
		const int& i = d;
		//等价于以下两行 引用绑定失败
		// const int temp =dval;
		// const int &i=temp;
		return 0;
	}

	//计算50-100的总和
	void test1() {
		int i = 50, sum = 0;
		while (i < 100)
		{
			sum += i++;
		}
		cout << sum << endl;
	}

	//打印一段字符串
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



	//线程睡眠num秒
	void timepp(int num)
	{
		Sleep(num * 1000);
		out("sleep/s", std::to_string(num));
	}

}