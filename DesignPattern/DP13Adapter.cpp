#include"heads.h"

/*
* 
* ������ģʽ
* ��һ����Ľӿ�ת���ɿͻ�ϣ������һ���ӿ�.Adapter ģʽʹ��ԭ�����ڽӿڲ�����
* ��������һ��������Щ�����һ������
* 
* ��ҪӦ����ϣ������һЩ�ִ���࣬���ǽӿ����븴�û���Ҫ��һ�µ����  
*/

//�����û��Ľӿ���
class AbsTarget {

public:
	virtual void Request() = 0;
};

//������Ķ���
class Adaptee {
public:
	void method() {
		std::cout << "me" << std::endl;
	}
};
 
//������
class Adapter :public AbsTarget {

	Adaptee adaptee;
public:

	Adapter(Adaptee ada) :adaptee(ada) {
		adaptee = ada;
	}

	void Request() {
		adaptee.method();
	}
};
