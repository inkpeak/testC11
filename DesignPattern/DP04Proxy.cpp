#include"heads.h"

/*
*  代理模式
* 给某一个对象提供一个代理或占位符，并由代理对象来控制对原对象的访问
*
* 有3个组成角色：
* Subject(抽象主题角色):声明了真实主题和代理主题的共同接口,这样一来
* 在任何使用真实主题的地方都可以使用代理主题,客户端通常需要针对
* 抽象主题角色进行编程
* Proxy(代理主题角色):代理主题角色通过关联关系引用真实主题角色,因此
* 可以控制和操纵真实主题对象,代理主题角色中提供一个与真实主题角色相同的接口
* (以在需要时代替真实主题角色),同时还可以在调用对真实主题对象的操作
* 之前或之后增加新的服务和功能；
* RealSubject(真实主题角色):定义了代理角色所代表的真实对象,在真实主题角色
* 中实现了真实的业务操作

*/

//抽象主题角色
class Man
{

public:
	virtual void Request() = 0;
};

//真实主题角色
class RealMan : public Man
{
public:
	void Request() {}
};

//代理主题角色
class Proxy
{
	RealMan m_rm;
public:
	Proxy(RealMan rm) {
		m_rm = rm;
	}
	void Request()
	{
		m_rm.Request();
	}
};
