#include"heads.h" 

/*
* 
* װ��ģʽ
* װ��ģʽ�Ƕ�̬�ؽ�������ӵ���������϶���Ӱ�������������Ӧ����
* ���߻���ķ�����
* ��4����ɽ�ɫ��
* Component�Ƕ���һ������ӿڣ����Ը���Щ����̬�����ְ��
* ConcreteComponent�Ƕ�����һ������Ķ���,���Ը�����������һЩְ��
* Decorator,װ�γ�����,�̳���Component,����������չComponent��Ĺ��ܣ�
  ������Component��˵,������֪��Decorator�Ĵ��ڵġ�
* ConcreteDecorator���Ǿ����װ�ζ����𵽸�Component���ְ��Ĺ���
* ����Ӧ�ó�����
  a.��Ҫ��̬�ظ�һ��������ӹ���,����Щ����Ҳ���Զ�̬�ر�����ʱ��
  b.��ʹ�ü̳в�����ϵͳ��ά������չʱ����ֱ�Ӳ�����ʹ�ü̳еķ�ʽ
  ��ϵͳ������չʱ��
  c.һ��ԭʼ��ͬʱ�����˶�������ڲ�Ӱ�����������ǰ���£�
  �Զ�̬��͸���ķ�ʽΪ������������µ�ְ�𣬶����޸�ԭʼ�ࡣ
	����Ϸ�з���ϵͳΪ��
*/

//����ϵͳ�ӿ�
class AbsComponent
{
	vector<string> clothes;
public:
	virtual ~AbsComponent() {};

	// Ϊ�����ĸ���װ�β����ṩһ��ͳһ�Ľӿ�
	virtual void Operation()=0;

	void setClothes(string s) {
		clothes.push_back(s);
	}

	vector<string> getClothes() {
		return clothes;
	} 
};

//�ƺ�
class ConcreteComponent : public  AbsComponent
{
public:
	void Operation()
	{
		setClothes("Lv.1");
		cout << "Lv.1" << endl;
	}
};

//װ�γ�����
class AbsDecorator : public AbsComponent
{
	AbsComponent* m_com=nullptr;
public:
	AbsDecorator() {}
	AbsDecorator(AbsComponent* ac) {
		m_com = ac;
	}

	void dress(string s) { 
		setClothes(s);
	}

	virtual ~AbsDecorator() {};
	 
	virtual void Operation()=0;

protected: 
};

//ͷ��
class ConcreateDecoratorA : public AbsDecorator
{
public:
	ConcreateDecoratorA(){};

	ConcreateDecoratorA(AbsComponent* ac):AbsDecorator(ac) { 
	}
	void Operation() {
		dress("head");
		cout << "head" << endl;
	}
};


//�ز�
class ConcreateDecoratorB : public AbsDecorator
{
public:
	ConcreateDecoratorB() {};

	ConcreateDecoratorB(AbsComponent* ac) :AbsDecorator(ac) {
	}
	void Operation() {
		dress("body");
		cout << "body" << endl;
	}
};


//�Ȳ�
class ConcreateDecoratorC : public AbsDecorator
{
public:
	void Operation() {
		dress("leg");
		cout << "leg" << endl;
	}
};


//�Ų�
class ConcreateDecoratorD : public AbsDecorator
{
public:
	void Operation() {
		dress("foot");
		cout << "foot" << endl;
	}
};


//�ֱ�
class ConcreateDecoratorE : public AbsDecorator
{
public:
	void Operation() {
		dress("arm");
		cout << "arm" << endl;
	}
};
