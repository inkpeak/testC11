#include"heads.h"

/*
* 外观模式
* 很多人也把它叫做门面模式,在GOF的《设计模式:可复用面向对象软件的基础》
* 一书中对外观模式是这样说的：将子系统中的一组接口提供一个一致的界面，
* 外观模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。
*
* 优点
* 1.它对客户屏蔽了子系统组件,减少了客户处理的对象的数目,使得子系统
* 使用起来更加方便；
* 2.它实现了子系统与客户之间的松耦合关系,而子系统内部的功能组件往往是
* 紧耦合的；松耦合系统使得子系统的组件变化不会影响到它的客户.有助于建立
* 层次结构系统,也有助于对对象之间的依赖关系分层.可以消除复杂的循环依赖关系.
* 这一点在客户程序与子系统是分别实现的时候尤为重要。
* 
*/
 

class SubSystemOne
{
public:
    void MethodOne()
    {
        std::cout << "子系统方法一" << std::endl;
    }
};
class SubSystemTwo
{
public:
    void MethodTwo()
    {
        std::cout << "子系统方法二" << std::endl;
    }
};

class SubSystemThree
{
public:
    void MethodThree()
    {
        std::cout << "子系统方法三" << std::endl;
    }
};

class SubSystemFour
{
public:
    void MethodFour()
    {
        std::cout << "子系统方法四" << std::endl;
    }
};


class Facade
{
    SubSystemOne one;
    SubSystemTwo two;
    SubSystemThree three;
    SubSystemFour four;
public:
    void method1() {
        std::cout << " 方法组：4123" << std::endl;
        four.MethodFour();
        one.MethodOne();
        two.MethodTwo();
        three.MethodThree();
    }
};