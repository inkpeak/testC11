#include"heads.h"
/*
* 
* 中介者模式
* 中介对象来封装一系列的对象.中介者使各对象不需要显示地相互引用,从而
* 使其耦合松散，而且可以独立地改变它们之间的交互
* 
* a1 定义一个中介者接口类AbsMediator，定义两个接口函数send()和add()，send()转发同事的消息，add()往同事集合增加同事；
a2 定义一个具体中介者类ConcreteMediator，实现接口函数send()和add()；
a3 定义一个同事接口类Colleague，定义两个接口函数send()和notify()，send()往中介者发消息然后通过中介者转发给目标同事，notify()为为该同事要发送的内容；
a4 定义一个具体同事类ConcreteColleague，实现接口函数send()和notify()； 
* 
* 优点
* 1.降低了对象之间的耦合性,增加了它们的独立性和可维护性。
* 2.减少了对象间的直接通信,简化了对象之间的关系，降低了系统的复杂性。
* 3.中介者对象可以为对象之间的通信提供额外的功能，如消息队列和日志记录。
* 
* 缺点
* 1.中介者对象会成为系统的核心,并承担大量的职责,如果这些职责变得过于复杂,
*   就会导致中介者对象变得过于庞大和难以维护。
* 2.可能会降低整体系统的效率，因为所有的通信都需要经过中介者对象
* 
* 
*/
class AbsMediator;

class Colleague {
public:
    Colleague() {}
    Colleague(string s) : _name(s) {};
    virtual void send( string message) = 0;
    virtual void receive( string message) = 0;
    virtual void setMediator(shared_ptr<AbsMediator> mediator) = 0;
     
    string getName() {
        return _name;
    }
protected: 
    string _name;
};
 
//中介者接口类
class AbsMediator {
public:
    virtual void addColleague(shared_ptr<Colleague> colleague) = 0;

    virtual void send(string name, std::string message) = 0;
};


class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(string name) : Colleague(name) { }

    void send(string message) override {
        _mediator->send(_name, message);
    }

    void receive(string message) override {
        cout << _name << " received message: " << message << endl;
    }

    void setMediator(shared_ptr<AbsMediator> mediator) override {
        _mediator = mediator;
    }

private:
    shared_ptr<AbsMediator> _mediator;
};

//ConcreteMediator
class ConcreteMediator : public AbsMediator {
public:
    void addColleague(std::shared_ptr<Colleague> colleague) override {
        _colleagues.push_back(colleague);
    }

    void send(string name, string message) override {
        for (auto& colleague : _colleagues) {
            if (colleague  != nullptr && colleague->getName() != name) {
                colleague->receive(message);
            }
        }
    }

private:
    vector<shared_ptr<Colleague>> _colleagues;
};
