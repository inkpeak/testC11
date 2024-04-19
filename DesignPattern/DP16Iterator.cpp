#include"heads.h"

/*
* 
* ������ģʽ
* �ṩһ��������˳����ʾۺ϶����е�һϵ�����ݣ�������¶�ۺ϶�����ڲ���ʾ
* 
* �ŵ�
* 1.����һ���ۺ϶�������ݶ����뱩¶�����ڲ���ʾ��
* 2.���������ɵ�������ɣ�����˾ۺ��ࡣ
* 3.��֧���Բ�ͬ��ʽ����һ���ۺϣ����������Զ����������������֧���µı�����
* 4.�����µľۺ���͵������඼�ܷ��㣬�����޸�ԭ�д��롣
* 5.��װ�����ã�Ϊ������ͬ�ľۺϽṹ�ṩһ��ͳһ�Ľӿڡ�
* 
*/


//����������
class AbsIterator {
public:
	AbsIterator(){}
	virtual ~AbsIterator() {}

	virtual string first() = 0;
	virtual string next() = 0;
	virtual string current() = 0;
	virtual bool isEnd() = 0;
};

//�������
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


//�ۼ�������
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