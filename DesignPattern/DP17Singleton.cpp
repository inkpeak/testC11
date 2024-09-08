#include"heads.h"

/*
* ����ģʽ
* ������ϵͳ���������ڣ���֤һ�������һ��ʵ�������ṩһ����������ȫ�ַ��ʵ�
* 
* ����ģʽ���Է�Ϊ ����ʽ �� ����ʽ ������֮����������ڴ���ʵ����ʱ�䲻ͬ
* ����ʽ
* ϵͳ������,ʵ����������,ֻ�е���Ҫʹ�ø�ʵ��ʱ,�Ż�ȥ������ʹ��ʵ��.
* ���ַ�ʽҪ�����̰߳�ȫ��
* ����ʽ
* ϵͳһ����,�ͳ�ʼ������ʵ��,����Ҫʱ,ֱ�ӵ��ü���.���ַ�ʽ������̰߳�ȫ,
* û�ж��̵߳��̰߳�ȫ����
* 
*/

//  ����������ʽʵ�� 
class Singleton {
public:
	static Singleton* GetInstance() {
		if (instance == nullptr) {
			instance = new Singleton();
		}
		return instance;
	}
	static void deleteInstance() {
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

private:
	Singleton() {}
	~Singleton() {}

	// ���俽������͸�ֵ�����Ϊ˽�к���, ��ֹ�ⲿ�����͸�ֵ
	Singleton(const Singleton& signal) = delete;

	const Singleton& operator=(const Singleton& signal) = delete;
	// Ψһ��ʵ������ָ��
	static Singleton* instance;
	static mutex m_Mutex;
};
Singleton* Singleton::instance = nullptr;


// ����ʵ��
class Singleton1 {
public:
	static Singleton1* GetInstance() {
		if (g_pinstance == nullptr) {
			call_once(singletonFlag, [&] {
				g_pinstance = new Singleton1();
				});
		}
		return g_pinstance;
	}
	static void deleteInstance() {
		if (g_pinstance)
		{
			delete g_pinstance;
			g_pinstance = nullptr;
		}
	}

private:
	Singleton1() {}
	~Singleton1() {}

	// ���俽������͸�ֵ�����Ϊ˽�к���, ��ֹ�ⲿ�����͸�ֵ
	Singleton1(const Singleton1& signal) = delete;

	const Singleton1& operator=(const Singleton1& signal) = delete;
	// Ψһ��ʵ������ָ��
	static Singleton1* g_pinstance  ;
	static once_flag singletonFlag;
};

Singleton1* Singleton1::g_pinstance = nullptr;
once_flag Singleton1::singletonFlag;