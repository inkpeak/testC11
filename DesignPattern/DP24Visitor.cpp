#include"heads.h"

/*
* 
* ������ģʽ
* ��ʾһ��������ĳ����ṹ�еĸ�Ԫ�صĲ�������ʹ�������
*  ���ı��Ԫ�ص����ǰ���¶�����������ЩԪ�ص��²���
* 
* 1.����ӿڷ�������Visitor,�����������ʽӿں��� 
* 2.��������������DisplayVisitor����д�ӿں�����ͨ������������ȥ����
*   ����Ķ���Array��Linked 
* 3.����һ��ԭ����DataStructure������һ�����պ���accept(Visitor* visitor)�ӿڣ�
* 4.������������ԭ����Array��Linked����дaccept()�ӿ�  
* 
* �ŵ�
* �����µĲ��������ס����� Visitor Pattern ʵ���˲��������ķ���,
*  �µĲ�������ͨ������һ���µľ������������ʵ�֡�
* ������ģʽ��֮ǰ��ɢ�ڸ���Ԫ�����еĲ������е����������У�ʹ��Ԫ������Ӽ򵥺�������
* �����ڲ��޸�����Ԫ���������£������µ�Ԫ���࣬�ﵽ������ԭ�򡱵�Ҫ��
* 
* ȱ��
* �����µ�Ԫ��������ѡ����� Visitor Pattern Ҫ��ÿ��Ԫ���඼Ҫʵ�� accept() �����������������µ�Ԫ����ʱ��Ҫ�޸����еľ���������࣬�������ϵͳ�ĸ����ԡ�
* Visitor Pattern ��Ҫ�������ܹ�����Ԫ�ص�˽�����ԣ����ƻ��˶���ķ�װ�ԡ�
* Visitor Pattern ���������������������ϵͳ�ĸ����ԡ�
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
 

 