#include"heads.h"

#define DELETE_OBJECT(p) {if(NULL != (p)){delete (p); (p) = NULL;}}
/*
* 
* 桥接模式
* 抽象部分与它的实现部分分离,使它们都可以独立地变化.称为
*  柄体(Handle and Body)模式或接口(Interface)模式。
* 
* Abstraction(抽象化角色)：定义抽象接口,维护一个对Implementor对象的引用。
* RefinedAbstraction(具体抽象化角色)：是Abstraction的一个子类,
    对Abstraction接口进行一些补充。
* Implementor(实现化角色)：定义实现化角色的接口,任何Abstraction角色可以调用。
* ConcreteImplementor(具体实现化角色)：Implementor接口的具体实现。 
* 
* 抽象化角色持有实现化角色的引用，它只需要定义与客户端的接口并委托给实现化角色
* 来执行.具体化角色继承抽象化角色并实现自己的业务逻辑，同时构造时关联相应的实现
* 化角色。
*/

//抽象的操作系统类
class OS
{
public:
    virtual std::string GetOS() = 0;
};

//IOS类的实现
class IOS : public OS
{
public:
    virtual std::string GetOS()
    {
        return "IOS Operator System";
    }
};

//塞班类的实现
class SaiBian : public OS
{
public:
    virtual std::string GetOS()
    {
        return "SaiBian Operator System";
    }
};

//IOS某个版本的实现
class IOSSubSystem1 : public IOS
{
public:
    virtual std::string GetOS()
    {
        return "IOS 5.1.1 Operator System";
    }
};

//IOS某个版本的实现
class IOSSubSystem2 : public IOS
{
public:
    virtual std::string GetOS()
    {
        return "IOS 10.1.1 Operator System";
    }
};

//塞班系统某个类的实现
class SaiBianSubSystem1 : public SaiBian
{
public:
    virtual std::string GetOS()
    {
        return "SaiBian 1.1.0 Operator System";
    }
};

//塞班系统某个类的实现
class SaiBianSubSystem2 : public SaiBian
{
public:
    virtual std::string GetOS()
    {
        return "SaiBian 1.1.1 Operator System";
    }
};
 
//抽象的手机类
class Phone
{
public:
    virtual void SetOS() = 0;
};

//苹果手机类,依赖抽象的操作系统
class iPhone : public Phone
{
public:
    iPhone(OS* os)
    {
        m_pOS = os;
    }
    ~iPhone()
    {
        DELETE_OBJECT(m_pOS);
    }
    virtual void SetOS()
    {
        cout << "Set The OS: " << m_pOS->GetOS().c_str() << endl;
    }
private:
    OS* m_pOS;
};

//诺基亚手机类,以来抽象的操作系统
class Nokia : public Phone
{
public:
    Nokia(OS* os)
    {
        m_pOS = os;
    }
    ~Nokia()
    {
        DELETE_OBJECT(m_pOS);
    }

    virtual void SetOS()
    {
        cout << "Set The OS: " << m_pOS->GetOS().c_str() << endl;
    }
private:
    OS* m_pOS;
}; 