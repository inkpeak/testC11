#include"heads.h"

/*
* 
* ���󹤳�ģʽ
* �ṩһ���ӿڣ����Դ���һϵ����صĶ��������ָ�����ǵ��� 
* ��������ģʽ����չ������
* 
* �ŵ㣺
* 1.��Ʒ��һ����:���󹤳�ģʽ����ȷ��һ���Դ���һ������صĲ�Ʒ,
*   ��֤����Щ��Ʒ֮���һ���ԣ�����������ȡ�
* 2.�����滻��Ʒϵ��:���ڳ��󹤳�ģʽ����Ʒ�Ĵ�����װ�ڹ�������,
*   ��˿��������滻������Ʒϵ�У�������Ҫ�޸Ŀͻ��˴��롣
* 3.���ؾ����Ʒ��ʵ��:�ͻ���ֻ��Ҫ֪�������Ʒ�Ľӿ�,������Ҫ����
*   �����Ʒ��ʵ��ϸ��.�������Խ��Ϳͻ��˺;����Ʒ��֮�����϶�.
* 4.���Ͽ���ԭ��:���󹤳�ģʽ�������ɵ�����µĲ�Ʒ��,������Ҫ
*   �޸����еĴ��룬���Ͽ���ԭ��
* 5.�ṩһ�µĽӿ�:���󹤳�ģʽ�ṩ��һ�µĽӿ���������Ʒ,��������
*   �ÿͻ��˴�����Ӽ�������ά����
* 
* ���󹤳�ģʽȱ�㣺
* 1.������չ��Ʒ�ȼ��ṹ:�����Ҫ����µĲ�Ʒ�ȼ��ṹ,���������µ�
*   ��ť����,��Ҫ�޸ĳ��󹤳��ӿں����еľ��幤����,����ܻ�Ӱ�����еĴ��� 
* 2.��Ʒ�仯Ƶ�ʸ�:�����Ʒ�ı仯Ƶ�ʽϸ�,���󹤳�ģʽ���ܻᵼ��ϵͳ
*   ��ø���,��Ϊÿ������²�Ʒ����Ҫ�޸ĳ��󹤳��ӿں����еľ��幤����.
* 3.������ϵͳ�ĳ����Ժ�����Ѷȣ����󹤳�ģʽ�����˶���ĳ����Σ�
*   ���ܻ�����ϵͳ�ĸ����Ժ�����Ѷ�
*/


namespace DP11 {

	//�γ�
	class AbsProductA
	{
	public:
		AbsProductA() {}
		~AbsProductA() {}
	};

	//SUV
	class AbsProductB
	{
	public:
		AbsProductB() {}
		~AbsProductB() {}
	};

	//���ڽγ�
	class ProductA1 :public AbsProductA
	{
	public:
		ProductA1() {}
		~ProductA1() {}
	};

	//С�׽γ�
	class ProductA2 :public AbsProductA
	{
	public:
		ProductA2() {}
		~ProductA2() {}
	};

	//����SUV
	class ProductB1 :public AbsProductB
	{
	public:
		ProductB1() {}
		~ProductB1() {}

	};

	//С��SUV
	class ProductB2 :public AbsProductB
	{
	public:
		ProductB2() {}
		~ProductB2() {}

	};

	//������ 
	class AbsFactory {
	public:
		AbsFactory() {}
		~AbsFactory() {}

		virtual AbsProductA CreateProductA() {
			AbsProductA a;
			return   a;
		}

		virtual AbsProductB CreateProductB() {
			AbsProductB a;
			return   a;
		}
	};

	//����������
	class ConcreteFactory1 :public AbsFactory
	{
	public:
		ConcreteFactory1() {}
		~ConcreteFactory1() {}
		AbsProductA CreateProductA() {
			ProductA1 a;
			return   a;
		}

		AbsProductB CreateProductB() {
			ProductB1 a;
			return   a;
		}
	};

	//�Ͼ�������
	class ConcreteFactory2 :public AbsFactory
	{
	public:
		ConcreteFactory2() {}
		~ConcreteFactory2() {}
		AbsProductA CreateProductA() {
			ProductA2 a;
			return   a;
		}

		AbsProductB CreateProductB() {
			ProductB2 a;
			return   a;
		}
	};

}