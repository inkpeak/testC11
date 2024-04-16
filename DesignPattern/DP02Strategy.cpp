#include"heads.h" 
/*
* 策略模式
* 定义:该模式定义了一系列算法,并将每个算法封装起来,使它们可以相互替换，
* 且算法的变化不会影响使用算法的客户。策略模式属于对象行为模式,它通过
* 对算法进行封装,把使用算法的责任和算法的实现分割开来,并委派给
* 不同的对象对这些算法进行管理。
* 策略模式有三个组成角色：
* 抽象策略(Strategy)类
* 具体策略(Concrete Strategy)类
* 环境(Context)类
* 
* 优点：
* 1.多重条件语句不易维护，而使用策略模式可以避免使用多重条件语句 
* 2.策略模式提供了一系列的可供重用的算法族，恰当使用继承可以把
*	算法族的公共代码转移到父类里面，从而避免重复的代码  
* 3.算法的使用放到环境类中,而算法的实现移到具体策略类中,实现了二者的分离
* 缺点：
* 1.造成很多的策略类，增加维护难度
* 2.客户端必须理解所有策略算法的区别，以便适时选择恰当的算法类。 
*/


//算法抽象类
class AbsStractgy
{
public:
    virtual double AlgorithmInterface(double e) { return 0; };
};

//算法维护管理类
class ConcreteStrategy
{
    AbsStractgy* as;
public:
    ConcreteStrategy(AbsStractgy* a)
    {
        as = a;
    }

    double GetResult(double money)
    {
        return as->AlgorithmInterface(money);
    }
};

//具体算法A 满100减10
class ConcreteStrategyA :public  AbsStractgy
{
public:
    //算法A实现方法 
    double algoA(double e) {
        cout << "算法A实现方法" << endl;
        return e - (e / 100) * 10;
    }
    double AlgorithmInterface(double e)
    {  
        return algoA(e);
    }
};

//具体算法B 8折
class ConcreteStrategyB :public  AbsStractgy
{
public:
    //算法B实现方法
    double algoB(double e) {
        cout << "算法B实现方法" << endl;
        return e * 0.8;
    }
    double AlgorithmInterface(double e)
    { 
        return algoB(e);
    }
};

//具体算法C 原价
class ConcreteStrategyC :public  AbsStractgy
{
public:
    //算法C实现方法
    double AlgorithmInterface(double e)
    {
        cout << "算法C实现方法" << endl;
        return e;
    }
};