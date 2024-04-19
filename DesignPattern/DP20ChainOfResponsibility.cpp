#include"heads.h"
/*
* 
* ְ����ģʽ
* Ϊ�˱��⽫һ������ķ�����������������һ��,�ö�������л��ᴦ��
* ����.����������Ķ���ӳ�һ����,����������ʱ,����������������������,
* ֱ����һ�������ܹ�������Ϊֹ
* 
* ��������(Handler)��ɫ:��������һ����������Ľӿ�,һ�����Ϊ������,
*  ���ڲ�ͬ�ľ��崦���ߴ�������ķ�ʽ��ͬ,��������ж����˳�����������.
*  ÿһ�������ߵ��¼һ���һ��������,���ڳ��������ж�����һ��������������
*  �Ķ�����Ϊ����¼ҵ�����,ͨ��������,�����߿�������һ����.�����Ҫ��
*  �ӿڿ��Զ����һ���������趨�ͷ��ض��¼ҵ����ã�
* ���崦����(ConcreteHandler)��ɫ�����ǳ������ߵ�����,���Դ����û�����,
*  ʵ���˳�������������֮ǰҪ�����ж�,�����Ƿ�����Ӧ�Ĵ���Ȩ��,
*  ������������������ת��������¼ҡ�
* 
*/

//��������
class AbsHandler
{
protected:
	shared_ptr<AbsHandler> m_pNextHandler;
public:
    AbsHandler() :m_pNextHandler(nullptr) {}
    AbsHandler(shared_ptr<AbsHandler> hander) :m_pNextHandler(hander) {}
	virtual ~AbsHandler() {}

    virtual void SetNextHandler(const shared_ptr<AbsHandler>  succ) {
        m_pNextHandler = succ;
    }
	virtual void HandleRequest(int req) = 0;
};

//���崦����
class ConcreteHandler1 :public AbsHandler {
public:
    ConcreteHandler1() {}

    ConcreteHandler1(const shared_ptr<AbsHandler> pNextHandler)
        : AbsHandler(pNextHandler) {}

	void SetNextHandler(const shared_ptr<AbsHandler>  succ) {}
	void HandleRequest(int req) {
         cout << "�ڵ�1�յ�����" <<  endl;

        if (req >= 0 && req < 10)
             cout << "�ڵ�1�������� " << req <<  endl;

        else if (m_pNextHandler) {
             cout << "���ǽڵ�1,��������Ҵ�����,�ý�����һ��" << endl;
            m_pNextHandler->HandleRequest(req);
        }  
	}
};


class ConcreteHandler2 : public AbsHandler {
public:
    ConcreteHandler2() {}

    ConcreteHandler2(const shared_ptr<AbsHandler> pNextHandler) 
        : AbsHandler(pNextHandler) {}

    void HandleRequest(int req) {
        cout << "�ڵ�2�յ�����" << endl;

        if (req >= 10 && req < 100)
            cout << "�ڵ�2�������� " << req << endl;

        else if (m_pNextHandler) {
            cout << "���ǽڵ�2,��������Ҵ�����,�ý�����һ��" << endl;
            m_pNextHandler->HandleRequest(req);
        }
    }
}; 