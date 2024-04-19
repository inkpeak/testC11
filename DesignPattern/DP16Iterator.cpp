#include"heads.h"

/*
* 
* 迭代器模式
* 提供一个对象来顺序访问聚合对象中的一系列数据，而不暴露聚合对象的内部表示
* 
* 优点
* 1.访问一个聚合对象的内容而无须暴露它的内部表示。
* 2.遍历任务交由迭代器完成，这简化了聚合类。
* 3.它支持以不同方式遍历一个聚合，甚至可以自定义迭代器的子类以支持新的遍历。
* 4.增加新的聚合类和迭代器类都很方便，无须修改原有代码。
* 5.封装性良好，为遍历不同的聚合结构提供一个统一的接口。
* 
*/


//迭代抽象类
class AbsIterator {
public:
	AbsIterator(){}
	virtual ~AbsIterator() {}

	virtual string first() = 0;
	virtual string next() = 0;
	virtual string current() = 0;
	virtual bool isEnd() = 0;
};

//对象基类
class Object
{
public:
	Object() {}
	~Object() {}

	virtual AbsIterator* CreateIterator() = 0;
	virtual int Count() = 0;
	virtual void Push(std::string) = 0;
	virtual string Pop(int) = 0;
};


class SubIterator : public AbsIterator
{
public:
	SubIterator() {}

	SubIterator(Object* obj) :AbsIterator(), m_pObj(obj), m_Cur(0) {}
	~SubIterator() {}

	std::string first()
	{
		return m_pObj->Pop(0);
	}

	std::string next()
	{
		std::string str;
		if (m_Cur < m_pObj->Count() - 1)
		{
			m_Cur++;
			str = m_pObj->Pop(m_Cur);
		}
		return str;
	}

	std::string current()
	{
		return m_pObj->Pop(m_Cur);
	}

	bool isEnd()
	{
		return (m_Cur == m_pObj->Count() - 1);
	}

private:
	Object* m_pObj;
	int m_Cur;
};


//聚集抽象类
//class AbsAggregate {
//	AbsIterator* CreateIterator() {
//		AbsIterator* ai = new SubIterator();
//		return ai;
//	}
//};

class Children : public Object
{
public:
	Children() : Object(), m_pIterator(NULL) {}
	~Children() {}

	AbsIterator* CreateIterator()
	{
		if (m_pIterator == NULL)
			m_pIterator = new SubIterator(this);
		return m_pIterator;
	}

	int Count()
	{
		return vec_str.size();
	}

	void Push(std::string s)
	{
		vec_str.push_back(s);
	}

	std::string Pop(int i)
	{
		std::string str;
		if (i >= 0 && i < vec_str.size())
		{
			str = vec_str[i];
		}
		return str;
	}

private:
	std::vector<std::string> vec_str;
	AbsIterator* m_pIterator;
};