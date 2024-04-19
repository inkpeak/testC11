#include"heads.h"

/*
* 
* ����ģʽ
* ��һ�������װΪһ������ʹ������������κ�ִ����������ηָ.��������֮��
* ͨ�����������й�ͨ���������㽫���������д��桢���ݡ����á����������
* 
* ģʽ�Ľṹ
* ���������ࣨCommand����ɫ������ִ������Ľӿ�,ӵ��ִ������ĳ��󷽷� execute() 
* ���������ɫ��Concrete Command����ɫ���ǳ���������ľ���ʵ����,��ӵ�н����߶���,
* ��ͨ�����ý����ߵĹ������������Ҫִ�еĲ�����
* ʵ����/������(Receiver)��ɫ:ִ������ܵ���ز���,�Ǿ����������ҵ�������ʵ���� 
* ������/�����ߣ�Invoker����ɫ��������ķ�����,��ͨ��ӵ�кܶ���������,��ͨ������
* ���������ִ�������������ֱ�ӷ��ʽ����ߡ�
* 
* �ŵ�
* 1.����ϵͳ����϶ȡ�����ģʽ�ܽ����ò����Ķ�����ʵ�ָò����Ķ�����
* 2.���ӻ�ɾ������ǳ�����.��������ģʽ������ɾ�������Ӱ��������,
*	�����㡰����ԭ��,����չ�Ƚ���
* 3.����ʵ�ֺ�����.����ģʽ���������ģʽ���,���������װ���һ���������,�������� 
*
* ȱ��
* 1.���ܲ����������������ࡣ��Ϊ�ƶ�ÿһ�������������Ҫ���һ������������
*/

//����ʵ����
class Receiver
{
public:
	void action1() {
		cout << "exec ConcreteCmd1" << endl;
	}

	void action2() {
		cout << "exec ConcreteCmd2" << endl;
	}
};
 
//����������
class AbsCommand
{
protected:
	Receiver* m_rece;
public:
	AbsCommand() {}
	virtual ~AbsCommand() {}

	AbsCommand(Receiver* re) :m_rece(re) {}
	virtual void Execute() = 0;
};

//��������
class ConcreteCmd1 :public AbsCommand {
public:
	ConcreteCmd1(Receiver* re) {
		m_rece = re;
	}
	void Execute() {
		m_rece->action1();
	}
};
class ConcreteCmd2 :public AbsCommand {
public:
	ConcreteCmd2(Receiver* re) {
		m_rece = re;
	}
	void Execute() {
		m_rece->action2();
	}
};

