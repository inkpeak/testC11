#include"heads.h"

/*
* 
* 享元模式
* 运用共享技术有效地支持大量细粒度对象的复用,系统只使用少量的对象,
* 而这些对象都很相似,状态变化很小,可以实现对象的多次复用,由于享元模式
* 要求能够共享的对象必须是细粒度对象，因此它又称为轻量级模式
* 
* 结构
* Flyweight（抽象享元类):一个接口或抽象类,声明了具体享元类的公共方法。
* ConcreteFlyweight(具体享元类):实现了抽象享元类，其实例称为享元对象。
* UnsharedConcreteFlyweight(非共享具体享元类):并不是所有的抽象享元类的
*  子类都需要被共享,不能被共享的子类可设计为非共享具体享元类。
* FlyweightFactory（享元工厂类）：用于创建并管理享元对象。 
* 
* 优点：大大减少了内存的占用，提高了程序运行效率
*/

// 享元类
class Flyweight {
public:
    virtual ~Flyweight() {}
    virtual void operation(const string& extrinsicState) const = 0;
};

// 具体享元类
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

// 享元工厂
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