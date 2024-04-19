#include"heads.h"
/*
* 
* 职责链模式
* 为了避免将一个请求的发送者与接受者耦合在一起,让多个对象都有机会处理
* 请求.将接受请求的对象接成一条链,当有请求发生时,可以沿着这条链传递请求,
* 直到有一个对象能够处理它为止
* 
* 抽象处理者(Handler)角色:它定义了一个处理请求的接口,一般设计为抽象类,
*  由于不同的具体处理者处理请求的方式不同,因此在其中定义了抽象请求处理方法.
*  每一个处理者的下家还是一个处理者,故在抽象处理者中定义了一个抽象处理者类型
*  的对象作为其对下家的引用,通过该引用,处理者可以连成一条链.如果需要，
*  接口可以定义出一个方法以设定和返回对下家的引用；
* 具体处理者(ConcreteHandler)角色：它是抽象处理者的子类,可以处理用户请求,
*  实现了抽象处理方法。处理之前要进行判断,看看是否有相应的处理权限,
*  若有则处理请求，若无则转发请求给下家。
* 
*/

//抽象处理类
class AbsHandler
{
protected:
	shared_ptr<AbsHandler> m_pNextHandler;
public:
    AbsHandler() :m_pNextHandler(nullptr) {}
    AbsHandler(shared_ptr<AbsHandler> hander) :m_pNextHandler(hander) {}
	virtual ~AbsHandler() {}

    virtual void SetNextHandler(const shared_ptr<AbsHandler>  succ) {
        m_pNextHandler = succ;
    }
	virtual void HandleRequest(int req) = 0;
};

//具体处理类
class ConcreteHandler1 :public AbsHandler {
public:
    ConcreteHandler1() {}

    ConcreteHandler1(const shared_ptr<AbsHandler> pNextHandler)
        : AbsHandler(pNextHandler) {}

	void SetNextHandler(const shared_ptr<AbsHandler>  succ) {}
	void HandleRequest(int req) {
         cout << "节点1收到请求" <<  endl;

        if (req >= 0 && req < 10)
             cout << "节点1处理请求 " << req <<  endl;

        else if (m_pNextHandler) {
             cout << "我是节点1,这个事情我处理不了,得交给上一级" << endl;
            m_pNextHandler->HandleRequest(req);
        }  
	}
};


class ConcreteHandler2 : public AbsHandler {
public:
    ConcreteHandler2() {}

    ConcreteHandler2(const shared_ptr<AbsHandler> pNextHandler) 
        : AbsHandler(pNextHandler) {}

    void HandleRequest(int req) {
        cout << "节点2收到请求" << endl;

        if (req >= 10 && req < 100)
            cout << "节点2处理请求 " << req << endl;

        else if (m_pNextHandler) {
            cout << "我是节点2,这个事情我处理不了,得交给上一级" << endl;
            m_pNextHandler->HandleRequest(req);
        }
    }
}; 