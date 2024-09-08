#include"heads.h"

/*
* 
* ���ģʽ
* ͨ����Ϲ�ϵ�������Ĺ�����ϵ,ʵ���˽�������ϳ����νṹ,����ʵ����ĸ���
* 
* �ŵ�
* 1.�������븴�Ͻṹ�ж��󽻻��Ŀͻ��˴��롣
* 2.��ʹ���򸴺Ͻṹ����¹��ܱ�����ס�
* 3.��ʹ�ñ�ʾ�ֲ����ݽṹ������ס�
* 
* ȱ��
* 1.�����ܻ�ʹ���϶���Ĵ���ȼ򵥶���Ĵ�������ӡ�
* 2.������Ͻṹ�����������Ӷ��������ܻή�͸��Ͻṹ������
* 
*/

//��϶��������ӿ�
class Component {

public:
	virtual void Add(Component* c) = 0;
	virtual void Remove(Component* c) = 0;
	virtual void Display() = 0;
	string GetName() {
		return m_name;
	}
protected:
	string m_name;
};

class Leaf :public Component {
public:
	Leaf(string str) {
		m_name = str;
	}
	void Add(Component* c) {}
	void Remove(Component* c) {}
	void Display() {
		cout << m_name << endl;
	}
};

class Composite :public Component {
	list<Component*> children;
public:
	Composite(string str) {
		m_name = str;
	}

	void Add(Component* c) {
		children.push_back(c);
	}
	void Remove(Component* c) {
		children.remove(c);
	}
	void Display() {
		cout << m_name << endl;
		for (Component* c : children) {
			cout << c->GetName() << endl;
		}
	}
};