#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <atomic>
#include <future> 
#include<iostream>
#include <queue>
#include <stdexcept> 
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::function;
using std::thread;
using std::queue;
using std::atomic;
using std::mutex;
using std::condition_variable;;
using std::future;;
using std::lock;
using std::lock_guard;
using std::unique_lock;
using std::runtime_error;
//����������
void fun1(int slp)
{
	cout << "  hello, fun1 !  " << std::this_thread::get_id()<<"\n" << endl;
	//printf("  hello, fun1 !  %d\n", std::this_thread::get_id());
	if (slp > 0) {
		cout << "======= fun1 sleep " << slp << " =========  " << std::this_thread::get_id() << endl;
		//printf(" ======= fun1 sleep %d  =========  %d\n", slp, std::this_thread::get_id());
		std::this_thread::sleep_for(std::chrono::milliseconds(slp));
		//Sleep(slp );
	}
}

struct gfun {
	//����()��ʵ�����Ե����ɵ��ö���
	int operator()(int n) {
		cout << n << "  hello, gfun ! " << std::this_thread::get_id() << endl;
		//printf("%d  hello, gfun !  %d\n", n, std::this_thread::get_id());
		return 42;
	}
};

class A {    //���������� static �Ĳ���ʹ���̳߳�
public:
	static int Afun(int n = 0) {
		std::cout << n << "  hello, Afun !  " << std::this_thread::get_id()
			<< "\n" << std::endl;
		return n;
	}

	static std::string Bfun(int n, std::string str, char c) {
		std::cout << n << "  hello, Bfun !  " << str.c_str() << "  " 
			<< (int)c << "  " << std::this_thread::get_id() << "\n" << std::endl;
		return str;
	}
};

namespace std1
{
	//�̳߳��������,Ӧ������Сһ��
#define  THREADPOOL_MAX_NUM 6
//�̳߳��Ƿ�����Զ�����(�����Ҫ,�Ҳ����� THREADPOOL_MAX_NUM)
//#define  THREADPOOL_AUTO_GROW

//�̳߳�,�����ύ��κ�������ķ����ʽ����������ִ��,���Ի�ȡִ�з���ֵ
//��ֱ��֧�����Ա����, ֧���ྲ̬��Ա������ȫ�ֺ���,Opteron()������
	class threadpool
	{
		unsigned short _initSize;       //��ʼ���߳�����
		using Task = function<void()>; //��������
		vector<thread> _pool;          //�̳߳�
		queue<Task> _tasks;            //�������
		mutex _lock;                   //�������ͬ����
#ifdef THREADPOOL_AUTO_GROW
		mutex _lockGrow;               //�̳߳�����ͬ����
#endif // !THREADPOOL_AUTO_GROW
		condition_variable _task_cv;   //��������
		atomic<bool> _run{ true };     //�̳߳��Ƿ�ִ��
		atomic<int>  _idlThrNum{ 0 };  //�����߳�����

	public:
		inline threadpool(unsigned short size = 4) {
			_initSize = size;
			addThread(size);
		}

		inline ~threadpool()
		{
			_run = false;
			_task_cv.notify_all(); // ���������߳�ִ��
			for (thread& thread : _pool) {
				//thread.detach(); // ���̡߳���������
				if (thread.joinable())
					thread.join(); // �ȴ���������� ǰ�᣺�߳�һ����ִ����
			}
		}

	public:

		// �ύһ������
		// ����.get()��ȡ����ֵ��ȴ�����ִ����,��ȡ����ֵ
		// �����ַ�������ʵ�ֵ������Ա��
		// һ����ʹ��   bind�� .commit(std::bind(&Dog::sayHello, &dog));
		// һ������   mem_fn�� .commit(std::mem_fn(&Dog::sayHello), this)
		template<class F, class... Args>
		auto commit(F&& f, Args&&... args) -> future<decltype(f(args...))>
		{
			if (!_run)    // stoped ??
				throw std::runtime_error("commit on ThreadPool is stopped.");

			using RetType = decltype(f(args...)); // typename std::result_of<F(Args...)>::type, ���� f �ķ���ֵ����
			auto task = std::make_shared< std::packaged_task< RetType() > >(
				std::bind(std::forward<F>(f), std::forward<Args>(args)...)
				); // �Ѻ�����ڼ�����,���(��)
			future<RetType> future = task->get_future();

			{    // ������񵽶���
				lock_guard<mutex> lock(_lock);
				//�Ե�ǰ���������  lock_guard �� mutex �� stack ��װ�࣬�����ʱ�� lock()��������ʱ�� unlock()
				_tasks.emplace([task]() { // push(Task{...}) �ŵ����к���
					(*task)();
					});
			}
#ifdef THREADPOOL_AUTO_GROW
			if (_idlThrNum < 1 && _pool.size() < THREADPOOL_MAX_NUM)
				addThread(1);
#endif // !THREADPOOL_AUTO_GROW
			_task_cv.notify_one(); // ����һ���߳�ִ��

			return future;
		}

		// �ύһ���޲�����, ���޷���ֵ
		template <class F>
		void commit2(F&& task)
		{
			if (!_run) return;

			{
				lock_guard<mutex> lock{ _lock };
				_tasks.emplace(std::forward<F>(task));
			}
#ifdef THREADPOOL_AUTO_GROW
			if (_idlThrNum < 1 && _pool.size() < THREADPOOL_MAX_NUM)
				addThread(1);
#endif // !THREADPOOL_AUTO_GROW
			_task_cv.notify_one();
		}

		//�����߳�����
		int idlCount() { return _idlThrNum; }

		//�߳�����
		int thrCount() { return _pool.size(); }

#ifndef THREADPOOL_AUTO_GROW
	private:
#endif // !THREADPOOL_AUTO_GROW
		//���ָ���������߳�
		void addThread(unsigned short size)
		{
#ifdef THREADPOOL_AUTO_GROW
			if (!_run)    // stoped ??
				throw runtime_error("Grow on ThreadPool is stopped.");
			unique_lock<mutex> lockGrow{ _lockGrow }; //�Զ�������
#endif // !THREADPOOL_AUTO_GROW
			for (; _pool.size() < THREADPOOL_MAX_NUM && size > 0; --size)
			{   //�����߳�����,�������� Ԥ�������� THREADPOOL_MAX_NUM
				_pool.emplace_back([this] { //�����̺߳���
					while (true) //��ֹ _run==false ʱ��������,��ʱ������п��ܲ�Ϊ��
					{
						Task task; // ��ȡһ����ִ�е� task
						{
							// unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()
							unique_lock<mutex> lock{ _lock };
							_task_cv.wait(lock, [this] { // wait ֱ���� task, ����Ҫֹͣ
								return !_run || !_tasks.empty();
								});

							if (!_run && _tasks.empty())
								return;
							_idlThrNum--;
							task = move(_tasks.front()); // ���Ƚ��ȳ��Ӷ���ȡһ�� task
							_tasks.pop();
						}

						task();//ִ������
#ifdef THREADPOOL_AUTO_GROW
						if (_idlThrNum > 0 && _pool.size() > _initSize) //֧���Զ��ͷſ����߳�,�����ֵ������������߳�
							return;
#endif // !THREADPOOL_AUTO_GROW
						{
							unique_lock<mutex> lock{ _lock };
							_idlThrNum++;
						}
					}
					});
				{
					unique_lock<mutex> lock{ _lock };
					_idlThrNum++;
				}
			}
		}
	};
}

#endif