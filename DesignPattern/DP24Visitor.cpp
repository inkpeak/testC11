#include"heads.h"

/*
* 
* 访问者模式
* 表示一个作用于某对象结构中的各元素的操作。它使你可以在
*  不改变各元素的类的前提下定义作用于这些元素的新操作
* 
* 1.定义接口访问者类Visitor,定义两个访问接口函数 
* 2.定义具体访问者类DisplayVisitor，重写接口函数，通过这两个函数去访问
*   具体的对象Array、Linked 
* 3.定义一个原件类DataStructure，定义一个接收函数accept(Visitor* visitor)接口；
* 4.定义两个具体原件类Array、Linked，重写accept()接口  
* 
* 优点
* 增加新的操作很容易。由于 Visitor Pattern 实现了操作与对象的分离,
*  新的操作可以通过增加一个新的具体访问者类来实现。
* 访问者模式将之前分散在各个元素类中的操作集中到访问者类中，使得元素类更加简单和清晰。
* 可以在不修改现有元素类的情况下，增加新的元素类，达到“开闭原则”的要求。
* 
* 缺点
* 增加新的元素类很困难。由于 Visitor Pattern 要求每个元素类都要实现 accept() 函数，所以在增加新的元素类时需要修改所有的具体访问者类，这会增加系统的复杂性。
* Visitor Pattern 需要访问者能够访问元素的私有属性，这破坏了对象的封装性。
* Visitor Pattern 增加了类的数量，增加了系统的复杂性。
* 
*/

class Visitor;
class Array;
class Linked;

class DataStructure {
public:
    virtual void accept(Visitor& visitor) = 0;

    virtual vector<int>& getData() = 0;

    virtual void addData(int data) = 0;
};
 
class Visitor {
public:
    virtual void visit(Array& array) = 0;

    virtual void visit(Linked& linked) = 0;
};
 
class Array : public DataStructure {
public: 
    void accept(Visitor& visitor) {
        visitor.visit(*this);
    }
      
     vector<int>& getData() {
         return data;
     }
      
     void addData(int data) {
         this->data.push_back(data);
     }

private:
     vector<int> data;
};


class Linked : public DataStructure {

public: 
    void addData(int data) {
        this->data.push_back(data);
    }
      
    vector<int>& getData() {
        return data;
    }

    void accept(Visitor& visitor) {
        visitor.visit(*this);
    }

private:
   vector<int> data;
};


class DisplayVisitor : public Visitor {
public: 
    void visit(Array& array) {
        cout << "Displaying Array data: ";

        for (int i = 0; i < array.getData().size(); i++) {
             cout << array.getData()[i] << " ";
        }

        cout << endl;
    }
     
    void visit(Linked& linked) {
        cout << "Displaying Linked data: ";

        for (int i = 0; i < linked.getData().size(); i++) {
             cout << linked.getData()[i] << " ";
        }

         cout << endl;
    } 
};
 

 