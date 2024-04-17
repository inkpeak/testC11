#include"heads.h"

/*
* �򵥹���ģʽ
* ����һ�������࣬�����Ը��ݲ����Ĳ�ͬ���ز�ͬ��Ʒ��ʵ����
* ��������ʵ��ͨ�������й�ͬ�ĸ���.
* ��������Ĺ������������û�����,�Զ�new��һ��������󲢷����丸���ָ��
* �������ø����ָ��ִ�и�����麯��,�Ϳ��Զ�̬���������д����,
* �Ӷ�ʵ�ֶ�̬.
* �ŵ㣺
* ͨ��һ�����εĹ������������ǿ���ʵ�����κβ�Ʒ�� 
* ���Լ򵥹�����һ���������ϵ��ࡣ
* ȱ�㣺
* �κΡ������������඼���Ա�����������̫�ء�����Ҫ������Ʒ����
* �ǳ���ʱ�����������Ĵ��������ܻ���Ӵ�����ѭ����ԭ��
* ������չ���ţ����޸Ĺرգ��������£��򵥹������������µĲ�Ʒ��
* ����Ϊ������Ϊ�����²�Ʒֻ��ͨ���޸Ĺ���������ʵ�֡� 
* 
*/

namespace DP01 {
	//���������
	class Operations
	{
	public:
		double _numberA = 0;
		double _numberB = 0;

		void set(double a, double b)
		{
			_numberA = a;
			_numberB = b;
		}
		virtual double GetResult() { return 0; }
	};

	//�ӷ���
	class OperationAdd : public Operations
	{
	public:
		double GetResult()
		{
			return _numberA + _numberB;
		}
	};

	//������
	class OperationSub : public Operations
	{
	public:
		double GetResult()
		{
			return _numberA - _numberB;
		}
	};

	//�˷���
	class OperationMul : public Operations
	{
	public:
		double GetResult()
		{
			return _numberA * _numberB;
		}
	};

	//������
	class OperationDiv : public Operations
	{
	public:
		double GetResult()
		{
			if (_numberB == 0)
				throw std::exception("����Ϊ0");
			else
			{
				return _numberA / _numberB;
			}
		}
	};


	class AbsFactory
	{
	public:
		static Operations* createOperate(char operate)
		{
			Operations* oper = nullptr;

			if ('+' == operate) oper = new OperationAdd();
			if ('-' == operate) oper = new OperationSub();
			if ('*' == operate) oper = new OperationMul();
			if ('/' == operate) oper = new OperationDiv();

			return oper;
		}
	};

}
