#include"heads.h"

/*
* 
* 组合模式
* 通过组合关系定义类间的关联关系,实现了将对象组合成树形结构,最终实现类的复用
* 
* 优点
* 1.它简化了与复合结构中对象交互的客户端代码。
* 2.它使得向复合结构添加新功能变得容易。
* 3.它使得表示分层数据结构变得容易。
* 
* 缺点
* 1.它可能会使复合对象的代码比简单对象的代码更复杂。
* 2.如果复合结构包含大量的子对象，它可能会降低复合结构的性能
* 
*/

//组合对象声明接口
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