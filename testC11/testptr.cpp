
template<typename T>
class testptr1 {
	//sharedptrʵ��
public:
	//1.���캯��
	//��ʼ����ʱ��Ĭ�����ü���Ϊ0
	testptr1() :_ptr((T*)0), _ref(0) {}

	//����ָͨ���ʼ��shared_ptr��ʱ��, shared_ptr�����ü���Ϊ1
	testptr1(T* obj) :_ptr(obj), _ref(new int(1)) {}

	//2.��������
	//������ʱ����ָ�벻Ϊ�������ü���Ϊ0��ʱ���ͷſռ�
	~testptr1() {
		if (_ptr && -- * _ref == 0) {
			delete _ptr;
			delete _ref;
		}
	}

	//3.�������캯��
	//�ڽ��п�������ʱ��ʹ��shared_ptr��ʼ����һ��shared_ptr��ʱ�����ü��� + 1
	testptr1(testptr1& other) :_ptr(other._ptr), _ref(&(++* other._ref)) {}

	//4.������ֵ����
	//ʹ��һ��shared_ptr����һ��shared_ptr��ֵ
	testptr1& operator=(testptr1& other) {
		if (this == &other)
			return *this;

		//��ָ�����ü���Ҫ++  
		++* other._ref;

		//ԭָ�����ü���Ҫ--�����Ϊ0�����ͷſռ�
		if (-- * _ref == 0) {
			delete _ptr;
			delete _ref;
		}

		//���½���ָ�� 
		_ptr = other._ptr;
		_ref = other._ref;
		return *this;
	}

	//5.���ؽ����� ֱ�ӷ��صײ�ָ������ã�������ĵ�ַ�ռ�����
	T& operator*()
	{
		if (_ref == 0)
			return (T*)0;

		return *_ptr;
	}

	//6.����ָ�������
	T* operator->()
	{
		if (_ref == 0)
			return 0;

		return _ptr;
	}

	//7.����ڲ���������ָͨ��
	T* get() {
		return _ptr;
	}

private:
	T* _ptr;
	int* _ref;//���ü���
};

template<typename T>
class testptr2 {
	//unique_ptrʵ��
public:
	//1.���캯��
	testptr2() {}
	testptr2(T* obj) :_ptr(obj) {}

	//2.��������
	~testptr2() {
		del();
	}

	//3.�������캯�������ã���֧��
	testptr2(testptr2& other) = delete;

	//4.������ֵ���������ã���֧��
	testptr2& operator=(const testptr2&) = delete;

	//5.reset()���ͷ�Դ��Դ��ָ������Դ
	// ���ͷ���Դ(�������), �ٳ�����Դ
	void reset(T* obj) {
		del();
		_ptr = obj;
	}

	//6.release()��������Դ����������Դ�Ĺ���,��Դ���ͷ��ɵ��÷�����
	T* release()
	{
		T* pTemp = _ptr;
		_ptr = nullptr;
		return pTemp;
	}

	//7.get()��������Դ��ֻ�ǹ��ⲿʹ�ã���Ȼ������Դ 
	T* get() {//���÷�Ӧ��ֻʹ�ò��ͷţ����������delete��Դ
		return _ptr;
	}

	//8.operator bool() : �Ƿ������Դ
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