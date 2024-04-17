#include"heads.h"

/*
*
* 原型模式 .
* 用原型实例指定创建对象的种类,并通过拷贝这些原型创建新的对象,
* 简单理解就是“克隆指定对象”
* 3种角色
* 抽象原型类：规定了具体原型对象必须实现的接口。
* 多个具体原型类：实现抽象原型类的 clone() 方法，它是可被复制的对象。
* 访问类：使用具体原型类中的 clone() 方法来复制新的对象。
*
* 优点
* 1.简化对象的创建过程，同时也能够提高效率
* 2.避免使用构造函数
*
* 缺点
* 每一个类都必须配备一个克隆方法,对于已有的没有克隆方法的类来说是致命的。
*
*/

//1. 抽象原型类
class Shape
{
public:
	virtual ~Shape() {}
	virtual Shape* clone() = 0;
	virtual int getid() = 0;
	virtual string getType() = 0;
protected:
	string Type;
private:
	int id;
};

//2. 三个形状具体原型
class Circle :public Shape
{
public:
	Circle(string Type, int id) :Type(Type), id(id) {}
	~Circle() {}
	Shape* clone() { return new Circle{ *this }; }
	int getid() { return id; }
	string getType() { return Type; }
protected:
	string Type;
private:
	int id;
};

class vRectangle :public Shape
{
public:
	vRectangle(string Type, int id) :Type(Type), id(id) {}

	~vRectangle() {}

	vRectangle(const vRectangle& lhs) {
		Type = lhs.Type, id = lhs.id;
	}

	Shape* clone() {
		return new vRectangle{ *this };
	}

	int getid() { return id; }
	string getType() { return Type; }
protected:
	string Type;
private:
	int id;
};
class Square :public Shape
{
public:
	Square(string Type, int id) :Type(Type), id(id) {}
	~Square() {}
	Square(const Square& lhs) { Type = lhs.Type, id = lhs.id; }
	Shape* clone() { return new Square{ *this }; }
	int getid() { return id; }
	string getType() { return Type; }
protected:
	string Type;
private:
	int id;
};

//3. 存储对象种类的数据库
class ShapeType
{
public:
	~ShapeType()
	{
		for (auto& x : ShapeMap)
		{
			delete x.second;
			x.second = nullptr;
		}
	}
	//构造原始对象
	ShapeType()
	{
		Circle* circle = new Circle{ "圆形",1 };
		Square* square = new Square{ "正方形",2 };
		vRectangle* rectangle = new vRectangle{ "矩形",3 };
		ShapeMap.emplace(circle->getType(), circle);
		ShapeMap.emplace(square->getType(), square);
		ShapeMap.emplace(rectangle->getType(), rectangle);
	}
	//根据你所需要的种类来获得克隆对象
	Shape* getShape(string Type)
	{
		return ShapeMap[Type]->clone();
	}
private:
	map<string, Shape*> ShapeMap;
};