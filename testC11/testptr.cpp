
template<typename T>
class testptr1 {
	//sharedptr实现
public:
	//1.构造函数
	//初始化的时候默认引用计数为0
	testptr1() :_ptr((T*)0), _ref(0) {}

	//用普通指针初始化shared_ptr的时候, shared_ptr的引用计数为1
	testptr1(T* obj) :_ptr(obj), _ref(new int(1)) {}

	//2.析构函数
	//析构的时候在指针不为空且引用计数为0的时候释放空间
	~testptr1() {
		if (_ptr && -- * _ref == 0) {
			delete _ptr;
			delete _ref;
		}
	}

	//3.拷贝构造函数
	//在进行拷贝构造时，使用shared_ptr初始化另一个shared_ptr的时候引用计数 + 1
	testptr1(testptr1& other) :_ptr(other._ptr), _ref(&(++* other._ref)) {}

	//4.拷贝赋值函数
	//使用一个shared_ptr给另一个shared_ptr赋值
	testptr1& operator=(testptr1& other) {
		if (this == &other)
			return *this;

		//新指针引用计数要++  
		++* other._ref;

		//原指针引用计数要--，如果为0，则释放空间
		if (-- * _ref == 0) {
			delete _ptr;
			delete _ref;
		}

		//重新进行指向 
		_ptr = other._ptr;
		_ref = other._ref;
		return *this;
	}

	//5.重载解引用 直接返回底层指针的引用，即共享的地址空间内容
	T& operator*()
	{
		if (_ref == 0)
			return (T*)0;

		return *_ptr;
	}

	//6.重载指针运算符
	T* operator->()
	{
		if (_ref == 0)
			return 0;

		return _ptr;
	}

	//7.获得内部包含的普通指针
	T* get() {
		return _ptr;
	}

private:
	T* _ptr;
	int* _ref;//引用计数
};

template<typename T>
class testptr2 {
	//unique_ptr实现
public:
	//1.构造函数
	testptr2() {}
	testptr2(T* obj) :_ptr(obj) {}

	//2.析构函数
	~testptr2() {
		del();
	}

	//3.拷贝构造函数，禁用，不支持
	testptr2(testptr2& other) = delete;

	//4.拷贝赋值函数，禁用，不支持
	testptr2& operator=(const testptr2&) = delete;

	//5.reset()：释放源资源，指向新资源
	// 先释放资源(如果持有), 再持有资源
	void reset(T* obj) {
		del();
		_ptr = obj;
	}

	//6.release()：返回资源，放弃对资源的管理,资源的释放由调用方处理
	T* release()
	{
		T* pTemp = _ptr;
		_ptr = nullptr;
		return pTemp;
	}

	//7.get()：返回资源，只是供外部使用，依然管理资源 
	T* get() {//调用方应该只使用不释放，否则会两次delete资源
		return _ptr;
	}

	//8.operator bool() : 是否持有资源
	operator bool() const {
		return _ptr != nullptr;
	}

	//9.operator * ()
	T& operator*() {
		return _ptr;
	}

	//10.operator -> ()
	T* operator->() {
		return _ptr;
	}

private:
	void del() {
		if (nullptr == _ptr) return;
		delete _ptr;
		_ptr = nullptr;
	}
	T* _ptr;
};