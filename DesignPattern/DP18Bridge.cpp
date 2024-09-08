#include"heads.h"

#define DELETE_OBJECT(p) {if(NULL != (p)){delete (p); (p) = NULL;}}
/*
* 
* �Ž�ģʽ
* ���󲿷�������ʵ�ֲ��ַ���,ʹ���Ƕ����Զ����ر仯.��Ϊ
*  ����(Handle and Body)ģʽ��ӿ�(Interface)ģʽ��
* 
* Abstraction(���󻯽�ɫ)���������ӿ�,ά��һ����Implementor��������á�
* RefinedAbstraction(������󻯽�ɫ)����Abstraction��һ������,
    ��Abstraction�ӿڽ���һЩ���䡣
* Implementor(ʵ�ֻ���ɫ)������ʵ�ֻ���ɫ�Ľӿ�,�κ�Abstraction��ɫ���Ե��á�
* ConcreteImplementor(����ʵ�ֻ���ɫ)��Implementor�ӿڵľ���ʵ�֡� 
* 
* ���󻯽�ɫ����ʵ�ֻ���ɫ�����ã���ֻ��Ҫ������ͻ��˵Ľӿڲ�ί�и�ʵ�ֻ���ɫ
* ��ִ��.���廯��ɫ�̳г��󻯽�ɫ��ʵ���Լ���ҵ���߼���ͬʱ����ʱ������Ӧ��ʵ��
* ����ɫ��
*/

//����Ĳ���ϵͳ��
class OS
{
public:
    virtual std::string GetOS() = 0;
};

//IOS���ʵ��
class IOS : public OS
{
public:
    virtual std::string GetOS()
    {
        return "IOS Operator System";
    }
};

//�������ʵ��
class SaiBian : public OS
{
public:
    virtual std::string GetOS()
    {
        return "SaiBian Operator System";
    }
};

//IOSĳ���汾��ʵ��
class IOSSubSystem1 : public IOS
{
public:
    virtual std::string GetOS()
    {
        return "IOS 5.1.1 Operator System";
    }
};

//IOSĳ���汾��ʵ��
class IOSSubSystem2 : public IOS
{
public:
    virtual std::string GetOS()
    {
        return "IOS 10.1.1 Operator System";
    }
};

//����ϵͳĳ�����ʵ��
class SaiBianSubSystem1 : public SaiBian
{
public:
    virtual std::string GetOS()
    {
        return "SaiBian 1.1.0 Operator System";
    }
};

//����ϵͳĳ�����ʵ��
class SaiBianSubSystem2 : public SaiBian
{
public:
    virtual std::string GetOS()
    {
        return "SaiBian 1.1.1 Operator System";
    }
};
 
//������ֻ���
class Phone
{
public:
    virtual void SetOS() = 0;
};

//ƻ���ֻ���,��������Ĳ���ϵͳ
class iPhone : public Phone
{
public:
    iPhone(OS* os)
    {
        m_pOS = os;
    }
    ~iPhone()
    {
        DELETE_OBJECT(m_pOS);
    }
    virtual void SetOS()
    {
        cout << "Set The OS: " << m_pOS->GetOS().c_str() << endl;
    }
private:
    OS* m_pOS;
};

//ŵ�����ֻ���,��������Ĳ���ϵͳ
class Nokia : public Phone
{
public:
    Nokia(OS* os)
    {
        m_pOS = os;
    }
    ~Nokia()
    {
        DELETE_OBJECT(m_pOS);
    }

    virtual void SetOS()
    {
        cout << "Set The OS: " << m_pOS->GetOS().c_str() << endl;
    }
private:
    OS* m_pOS;
}; 