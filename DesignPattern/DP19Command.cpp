#include"heads.h"

/*
* 
* 命令模式
* 将一个请求封装为一个对象，使发出请求的责任和执行请求的责任分割开.这样两者之间
* 通过命令对象进行沟通，这样方便将命令对象进行储存、传递、调用、增加与管理
* 
* 模式的结构
* 抽象命令类（Command）角色：声明执行命令的接口,拥有执行命令的抽象方法 execute() 
* 具体命令角色（Concrete Command）角色：是抽象命令类的具体实现类,它拥有接收者对象,
* 并通过调用接收者的功能来完成命令要执行的操作。
* 实现者/接收者(Receiver)角色:执行命令功能的相关操作,是具体命令对象业务的真正实现者 
* 调用者/请求者（Invoker）角色：是请求的发送者,它通常拥有很多的命令对象,并通过访问
* 命令对象来执行相关请求，它不直接访问接收者。
* 
* 优点
* 1.降低系统的耦合度。命令模式能将调用操作的对象与实现该操作的对象解耦。
* 2.增加或删除命令非常方便.采用命令模式增加与删除命令不会影响其他类,
*	它满足“开闭原则”,对扩展比较灵活。
* 3.可以实现宏命令.命令模式可以与组合模式结合,将多个命令装配成一个组合命令,即宏命令 
*
* 缺点
* 1.可能产生大量具体命令类。因为计对每一个具体操作都需要设计一个具体命令类
*/

//命令实现类
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
 
//抽象命令类
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

//具体命令
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

