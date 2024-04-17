#include"heads.h"

/*
*
* ԭ��ģʽ .
* ��ԭ��ʵ��ָ���������������,��ͨ��������Щԭ�ʹ����µĶ���,
* �������ǡ���¡ָ������
* 3�ֽ�ɫ
* ����ԭ���ࣺ�涨�˾���ԭ�Ͷ������ʵ�ֵĽӿڡ�
* �������ԭ���ࣺʵ�ֳ���ԭ����� clone() ���������ǿɱ����ƵĶ���
* �����ࣺʹ�þ���ԭ�����е� clone() �����������µĶ���
*
* �ŵ�
* 1.�򻯶���Ĵ������̣�ͬʱҲ�ܹ����Ч��
* 2.����ʹ�ù��캯��
*
* ȱ��
* ÿһ���඼�����䱸һ����¡����,�������е�û�п�¡����������˵�������ġ�
*
*/

//1. ����ԭ����
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

//2. ������״����ԭ��
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

//3. �洢������������ݿ�
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
	//����ԭʼ����
	ShapeType()
	{
		Circle* circle = new Circle{ "Բ��",1 };
		Square* square = new Square{ "������",2 };
		vRectangle* rectangle = new vRectangle{ "����",3 };
		ShapeMap.emplace(circle->getType(), circle);
		ShapeMap.emplace(square->getType(), square);
		ShapeMap.emplace(rectangle->getType(), rectangle);
	}
	//����������Ҫ����������ÿ�¡����
	Shape* getShape(string Type)
	{
		return ShapeMap[Type]->clone();
	}
private:
	map<string, Shape*> ShapeMap;
};