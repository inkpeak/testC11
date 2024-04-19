#include"heads.h"

/*
* 
* ��Ԫģʽ
* ���ù�������Ч��֧�ִ���ϸ���ȶ���ĸ���,ϵͳֻʹ�������Ķ���,
* ����Щ���󶼺�����,״̬�仯��С,����ʵ�ֶ���Ķ�θ���,������Ԫģʽ
* Ҫ���ܹ�����Ķ��������ϸ���ȶ���������ֳ�Ϊ������ģʽ
* 
* �ṹ
* Flyweight��������Ԫ��):һ���ӿڻ������,�����˾�����Ԫ��Ĺ���������
* ConcreteFlyweight(������Ԫ��):ʵ���˳�����Ԫ�࣬��ʵ����Ϊ��Ԫ����
* UnsharedConcreteFlyweight(�ǹ��������Ԫ��):���������еĳ�����Ԫ���
*  ���඼��Ҫ������,���ܱ��������������Ϊ�ǹ��������Ԫ�ࡣ
* FlyweightFactory����Ԫ�����ࣩ�����ڴ�����������Ԫ���� 
* 
* �ŵ㣺���������ڴ��ռ�ã�����˳�������Ч��
*/

// ��Ԫ��
class Flyweight {
public:
    virtual ~Flyweight() {}
    virtual void operation(const string& extrinsicState) const = 0;
};

// ������Ԫ��
class ConcreteFlyweight : public Flyweight {
public:
    ConcreteFlyweight(const string& intrinsicState) : intrinsicState_(intrinsicState) {}

    void operation(const string& extrinsicState) const override {
         cout << "ConcreteFlyweight: intrinsicState = " << intrinsicState_
            << ", extrinsicState = " << extrinsicState << endl;
    }

private:
     string intrinsicState_;
};

class UnsharedConcreteFlyweight : public Flyweight {
public:
    UnsharedConcreteFlyweight(const string& intrinsicState)
        : intrinsicState_(intrinsicState) {}

    void operation(const string& extrinsicState) const override {
        cout << "UnsharedConcreteFlyweight: intrinsicState = " <<
            intrinsicState_ << ", extrinsicState = " << extrinsicState << endl;
    }

private:
    string intrinsicState_;
};

// ��Ԫ����
class FlyweightFactory {
public:
    shared_ptr<Flyweight> getConcreteFlyweight(const string& key) {
        if (flyweights_.find(key) == flyweights_.end()) {
            flyweights_[key] = make_shared<ConcreteFlyweight>(key);
        }
        return flyweights_[key];
    }
    shared_ptr<Flyweight> getUnsharedConcreteFlyweight(const string& key) {
        if (flyweights_.find(key) == flyweights_.end()) {
            flyweights_[key] = make_shared<UnsharedConcreteFlyweight>(key);
        }
        return flyweights_[key];
    }

private:
    map<string,shared_ptr<Flyweight>> flyweights_;
};