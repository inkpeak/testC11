#include"heads.h"

/*
* 单例模式
* 在整个系统生命周期内，保证一个类仅有一个实例，并提供一个访问它的全局访问点
* 
* 单例模式可以分为 懒汉式 和 饿汉式 ，两者之间的区别在于创建实例的时间不同
* 懒汉式
* 系统运行中,实例并不存在,只有当需要使用该实例时,才会去创建并使用实例.
* 这种方式要考虑线程安全。
* 饿汉式
* 系统一运行,就初始化创建实例,当需要时,直接调用即可.这种方式本身就线程安全,
* 没有多线程的线程安全问题
* 
*/

//  加锁的懒汉式实现 
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

	// 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
	Singleton(const Singleton& signal) = delete;

	const Singleton& operator=(const Singleton& signal) = delete;
	// 唯一单实例对象指针
	static Singleton* instance;
	static mutex m_Mutex;
};
Singleton* Singleton::instance = nullptr;


// 饿汉实现
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

	// 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
	Singleton1(const Singleton1& signal) = delete;

	const Singleton1& operator=(const Singleton1& signal) = delete;
	// 唯一单实例对象指针
	static Singleton1* g_pinstance  ;
	static once_flag singletonFlag;
};

Singleton1* Singleton1::g_pinstance = nullptr;
once_flag Singleton1::singletonFlag;