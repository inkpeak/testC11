#include"heads.h"


/*
* ��������ģʽ
* ��������ģʽ�������Ƕ���һ��������Ʒ����Ĺ����ӿ�,
* ��ʵ�ʴ��������Ƴٵ����൱��
* 4�ֽ�ɫ
* ���󹤳�
* ���幤���࣬��Ӧ�����Ʒ
* �����Ʒ��
* �����Ʒ��
* �ŵ㣺
* 1.ʹϵͳ�ڲ��޸ľ��幤����ɫ������������µĲ�Ʒ
*/
class AbsLeiFeng
{
public:
	virtual void doSomething() = 0;
};

class stuents :public AbsLeiFeng
{
public:
	void doSomething() {}
};


class Volunter :public AbsLeiFeng
{
public:
	void doSomething() {}
};


class AbsFactory
{
	virtual AbsLeiFeng* createPerson() = 0;
};

class VolunterFactory : public AbsFactory
{
public:
	AbsLeiFeng* createPerson()
	{
		cout << "Volunter" << endl;
		return  new Volunter;
	}
};

class StuentsFactory : public AbsFactory
{
public:
	AbsLeiFeng* createPerson()
	{
		cout << "stuents" << endl;
		return  new stuents();
	}
};