#include"heads.h"

/*
* ���ģʽ
* �ܶ���Ҳ������������ģʽ,��GOF�ġ����ģʽ:�ɸ��������������Ļ�����
* һ���ж����ģʽ������˵�ģ�����ϵͳ�е�һ��ӿ��ṩһ��һ�µĽ��棬
* ���ģʽ������һ���߲�ӿڣ�����ӿ�ʹ����һ��ϵͳ��������ʹ�á�
*
* �ŵ�
* 1.���Կͻ���������ϵͳ���,�����˿ͻ�����Ķ������Ŀ,ʹ����ϵͳ
* ʹ���������ӷ��㣻
* 2.��ʵ������ϵͳ��ͻ�֮�������Ϲ�ϵ,����ϵͳ�ڲ��Ĺ������������
* ����ϵģ������ϵͳʹ����ϵͳ������仯����Ӱ�쵽���Ŀͻ�.�����ڽ���
* ��νṹϵͳ,Ҳ�����ڶԶ���֮���������ϵ�ֲ�.�����������ӵ�ѭ��������ϵ.
* ��һ���ڿͻ���������ϵͳ�Ƿֱ�ʵ�ֵ�ʱ����Ϊ��Ҫ��
* 
*/
 

class SubSystemOne
{
public:
    void MethodOne()
    {
        std::cout << "��ϵͳ����һ" << std::endl;
    }
};
class SubSystemTwo
{
public:
    void MethodTwo()
    {
        std::cout << "��ϵͳ������" << std::endl;
    }
};

class SubSystemThree
{
public:
    void MethodThree()
    {
        std::cout << "��ϵͳ������" << std::endl;
    }
};

class SubSystemFour
{
public:
    void MethodFour()
    {
        std::cout << "��ϵͳ������" << std::endl;
    }
};


class Facade
{
    SubSystemOne one;
    SubSystemTwo two;
    SubSystemThree three;
    SubSystemFour four;
public:
    void method1() {
        std::cout << " �����飺4123" << std::endl;
        four.MethodFour();
        one.MethodOne();
        two.MethodTwo();
        three.MethodThree();
    }
};