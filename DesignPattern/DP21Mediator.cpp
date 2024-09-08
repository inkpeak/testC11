#include"heads.h"
/*
* 
* �н���ģʽ
* �н��������װһϵ�еĶ���.�н���ʹ��������Ҫ��ʾ���໥����,�Ӷ�
* ʹ�������ɢ�����ҿ��Զ����ظı�����֮��Ľ���
* 
* a1 ����һ���н��߽ӿ���AbsMediator�����������ӿں���send()��add()��send()ת��ͬ�µ���Ϣ��add()��ͬ�¼�������ͬ�£�
a2 ����һ�������н�����ConcreteMediator��ʵ�ֽӿں���send()��add()��
a3 ����һ��ͬ�½ӿ���Colleague�����������ӿں���send()��notify()��send()���н��߷���ϢȻ��ͨ���н���ת����Ŀ��ͬ�£�notify()ΪΪ��ͬ��Ҫ���͵����ݣ�
a4 ����һ������ͬ����ConcreteColleague��ʵ�ֽӿں���send()��notify()�� 
* 
* �ŵ�
* 1.�����˶���֮��������,���������ǵĶ����ԺͿ�ά���ԡ�
* 2.�����˶�����ֱ��ͨ��,���˶���֮��Ĺ�ϵ��������ϵͳ�ĸ����ԡ�
* 3.�н��߶������Ϊ����֮���ͨ���ṩ����Ĺ��ܣ�����Ϣ���к���־��¼��
* 
* ȱ��
* 1.�н��߶�����Ϊϵͳ�ĺ���,���е�������ְ��,�����Щְ���ù��ڸ���,
*   �ͻᵼ���н��߶����ù����Ӵ������ά����
* 2.���ܻή������ϵͳ��Ч�ʣ���Ϊ���е�ͨ�Ŷ���Ҫ�����н��߶���
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
 
//�н��߽ӿ���
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
