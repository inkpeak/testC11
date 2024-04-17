#include"heads.h"

/*
* 观察者模式 by 行为型模式
* 观察者模式（Observer）,又叫发布-订阅模式（Publish/Subscribe）,
* 定义对象间一种一对多的依赖关系,使得每当一个对象改变状态,则所有
* 依赖于它的对象都会得到通知并自动更新。
*
* 抽象主题/抽象被观察者(Subject)角色:将所有观察者对象保存在一个集合中,
* 可以有任意数量的观察者.抽象主题提供一个接口，可以增加和删除观察者对象
* 具体主题/具体被观察者(ConcreteSubject)角色：该角色将有关状态存入具体观察者对象，在具体主题的内部状态发生改变时，给所有注册过的观察者发送通知
* 抽象观察者(Observer)角色：它定义了一个更新接口，使得在得到主题/被观察者更新时通知自己
* 具体观察者(ConcrereObserver)角色:实现抽象观察者定义的更新接口，以便在得到主题/被观察者更新时通知自己更新自身状态
* 
* 优点
* 1.观察者和被观察者是抽象耦合的
* 2.建立了一套触发机制
* 
* 缺点
* 1.如果一个被观察者对象有很多的直接和间接的观察者的话,将所有的观察者
*   都通知到会花费很多时间
* 2.如果观察者和观察目标间有循环依赖,观察目标会触发它们之间进行循环调用,
*   可能导致系统崩溃
* 3.观察者模式没有相应的机制让观察者知道所观察的目标对象是怎么发生变化的,
*   而仅仅只是知道观察目标发生了变化
*/
 
class Subject;

//观察者抽象类
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

//被观察者抽象类
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


//被观察者实现类
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

//观察者实现类
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

