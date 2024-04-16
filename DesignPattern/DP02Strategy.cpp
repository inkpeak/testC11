#include"heads.h" 
/*
* ����ģʽ
* ����:��ģʽ������һϵ���㷨,����ÿ���㷨��װ����,ʹ���ǿ����໥�滻��
* ���㷨�ı仯����Ӱ��ʹ���㷨�Ŀͻ�������ģʽ���ڶ�����Ϊģʽ,��ͨ��
* ���㷨���з�װ,��ʹ���㷨�����κ��㷨��ʵ�ַָ��,��ί�ɸ�
* ��ͬ�Ķ������Щ�㷨���й���
* ����ģʽ��������ɽ�ɫ��
* �������(Strategy)��
* �������(Concrete Strategy)��
* ����(Context)��
* 
* �ŵ㣺
* 1.����������䲻��ά������ʹ�ò���ģʽ���Ա���ʹ�ö���������� 
* 2.����ģʽ�ṩ��һϵ�еĿɹ����õ��㷨�壬ǡ��ʹ�ü̳п��԰�
*	�㷨��Ĺ�������ת�Ƶ��������棬�Ӷ������ظ��Ĵ���  
* 3.�㷨��ʹ�÷ŵ���������,���㷨��ʵ���Ƶ������������,ʵ���˶��ߵķ���
* ȱ�㣺
* 1.��ɺܶ�Ĳ����࣬����ά���Ѷ�
* 2.�ͻ��˱���������в����㷨�������Ա���ʱѡ��ǡ�����㷨�ࡣ 
*/


//�㷨������
class AbsStractgy
{
public:
    virtual double AlgorithmInterface(double e) { return 0; };
};

//�㷨ά��������
class ConcreteStrategy
{
    AbsStractgy* as;
public:
    ConcreteStrategy(AbsStractgy* a)
    {
        as = a;
    }

    double GetResult(double money)
    {
        return as->AlgorithmInterface(money);
    }
};

//�����㷨A ��100��10
class ConcreteStrategyA :public  AbsStractgy
{
public:
    //�㷨Aʵ�ַ��� 
    double algoA(double e) {
        cout << "�㷨Aʵ�ַ���" << endl;
        return e - (e / 100) * 10;
    }
    double AlgorithmInterface(double e)
    {  
        return algoA(e);
    }
};

//�����㷨B 8��
class ConcreteStrategyB :public  AbsStractgy
{
public:
    //�㷨Bʵ�ַ���
    double algoB(double e) {
        cout << "�㷨Bʵ�ַ���" << endl;
        return e * 0.8;
    }
    double AlgorithmInterface(double e)
    { 
        return algoB(e);
    }
};

//�����㷨C ԭ��
class ConcreteStrategyC :public  AbsStractgy
{
public:
    //�㷨Cʵ�ַ���
    double AlgorithmInterface(double e)
    {
        cout << "�㷨Cʵ�ַ���" << endl;
        return e;
    }
};