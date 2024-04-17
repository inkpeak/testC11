#include"heads.h"

/*
* �۲���ģʽ by ��Ϊ��ģʽ
* �۲���ģʽ��Observer��,�ֽз���-����ģʽ��Publish/Subscribe��,
* ��������һ��һ�Զ��������ϵ,ʹ��ÿ��һ������ı�״̬,������
* ���������Ķ��󶼻�õ�֪ͨ���Զ����¡�
*
* ��������/���󱻹۲���(Subject)��ɫ:�����й۲��߶��󱣴���һ��������,
* ���������������Ĺ۲���.���������ṩһ���ӿڣ��������Ӻ�ɾ���۲��߶���
* ��������/���屻�۲���(ConcreteSubject)��ɫ���ý�ɫ���й�״̬�������۲��߶����ھ���������ڲ�״̬�����ı�ʱ��������ע����Ĺ۲��߷���֪ͨ
* ����۲���(Observer)��ɫ����������һ�����½ӿڣ�ʹ���ڵõ�����/���۲��߸���ʱ֪ͨ�Լ�
* ����۲���(ConcrereObserver)��ɫ:ʵ�ֳ���۲��߶���ĸ��½ӿڣ��Ա��ڵõ�����/���۲��߸���ʱ֪ͨ�Լ���������״̬
* 
* �ŵ�
* 1.�۲��ߺͱ��۲����ǳ�����ϵ�
* 2.������һ�״�������
* 
* ȱ��
* 1.���һ�����۲��߶����кܶ��ֱ�Ӻͼ�ӵĹ۲��ߵĻ�,�����еĹ۲���
*   ��֪ͨ���Ứ�Ѻܶ�ʱ��
* 2.����۲��ߺ͹۲�Ŀ�����ѭ������,�۲�Ŀ��ᴥ������֮�����ѭ������,
*   ���ܵ���ϵͳ����
* 3.�۲���ģʽû����Ӧ�Ļ����ù۲���֪�����۲��Ŀ���������ô�����仯��,
*   ������ֻ��֪���۲�Ŀ�귢���˱仯
*/
 
class Subject;

//�۲��߳�����
class Observer {
public:
	Observer() {}
	Observer(Subject* sub, string name): m_subject(sub), m_name(name) {}

	virtual ~Observer() = default;

	virtual void  Update()=0;

	Subject *m_subject= nullptr ;
	string m_state, m_name;

	bool operator==(const Observer &tmp) const{
		return m_name == tmp.m_name ? true : false;
	}
};

//���۲��߳�����
class Subject
{ 
	string state;
	list<Observer*> m_observers;
public:
	Subject() {}
	virtual ~Subject() {}
	virtual void attach(Observer *observer) {
		m_observers.push_back(observer);
	}

	virtual void Detach(Observer *observer) {
		m_observers.remove(observer);
	}

	virtual void Notify() = 0;

	list<Observer*> getObservers() {
		return m_observers;
	}

	string getState() {
		return state;
	}
};


//���۲���ʵ����
class ConcreteSubject :public Subject {
public:
	ConcreteSubject() {}
	  void Notify() {
		for (Observer* var : getObservers())
		{
			var->Update();
		}
	}
};

//�۲���ʵ����
class ConcreteObserver :public Observer
{
public:
	ConcreteObserver(Subject*sub, string name)
		:Observer( sub, name) {}

	void Update() {
		m_state = m_subject->getState();
		std::cout << m_name << std::endl;
	}
private:
};

