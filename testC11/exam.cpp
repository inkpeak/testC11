#include<string>
using std::string;

#include<vector>
using std::vector;

#include<deque>
using std::deque;

#include<list>
using std::list;

#include<array> 
//容器头文件
//关联容器
#include<utility>
using std::pair;

#include<map>
using std::map;
using std::multimap;

//无序关联容器
#include<unordered_map>
using std::unordered_map;

#include<set>
using std::set;
using std::multiset;

#include<unordered_set>
using std::unordered_set;

#include<memory>
using std::shared_ptr;
using   std::weak_ptr;
using std::unique_ptr;

// 算法头文件
#include <algorithm>
#include<numeric>
#include<iterator>
#include<functional>
//IO流
#include<iostream>
using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::endl;
#include<fstream>
#include<sstream>
//根据c++ primer 第五版 练习内容


class Person {
	std::string m_name;
	std::string m_address;

public:
	Person() {}
	Person(std::string  name, std::string  address) {
		m_name = name;
		m_address = address;
	}
	void SetName(std::string const& name) {
		m_name = name;
	}

	void SetAddress(std::string const& address) {
		m_address = address;
	}

	std::string getName() {
		return m_name;
	}

	std::string getaddress() {
		return m_address;
	}
};

class Sales_data
{
	friend Sales_data add(const Sales_data&, const Sales_data&) {
		Sales_data a;
		return a;
	}

	friend std::istream& read() {
		Sales_data a;
		return std::cin;
	}

	friend std::ostream& print(std::ostream&, const Sales_data&) {
		return cout;
	}

public:
	Sales_data() = default;
	Sales_data(const std::string& s, unsigned n, double p) {}
	Sales_data(const std::string& s) :bookNo(s) {}
	Sales_data(std::istream&) {}
	std::string isbn() const {
		return bookNo;
	}
	Sales_data& combine(const Sales_data&) {}
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0;
};
//Sales_data add(const Sales_data&, const Sales_data&);
//std::istream& read();
//std::ostream& print(std::ostream&, const Sales_data&);

class Screen {
	friend class Window_mgr;
public:
	// 下面两种方式等价
	// using pos = std::string::size_type;
	typedef std::string::size_type pos;
	Screen() = default;
	Screen(pos ht, pos wd) {
		contents = ht * wd;
	}

	Screen(pos ht, pos wd, char c) :height(ht), width(wd),
		contents(ht* width + wd, c) {}

	inline char get(pos r, pos c) const {

		return contents[r * width + c];
	}

	Screen& move(pos r, pos c) {
		cursor = r * width + c;
		return *this;
	}

	inline Screen& set(char c) {
		contents[cursor] = c;
		return *this;
	}
	inline Screen& set(pos r, pos col, char ch) {
		contents[r * width + col] = ch;
		return *this;
	}

	Screen& display(std::ostream& os) {
		do_display(os);
		return *this;
	}
	const Screen& display(std::ostream& os)const {
		do_display(os);
		return *this;
	}

private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	void do_display(std::ostream& os) const {
		os << contents;
	}
};

class Window_mgr {
public:
	using ScreenIndex = std::vector<Screen>::size_type;
	void clear(ScreenIndex i) {
		Screen& s = screens[i];
		s.contents = std::string(s.height * s.width, ' ');
	}
	ScreenIndex addScreen(const Screen& s) {
		screens.push_back(s);
		return screens.size() - 1;
	}
private:
	std::vector<Screen> screens{ Screen(24,80,' ') };
};

class testClass {
public:
	testClass() = default;//使用默认构造
	testClass(const testClass&) = delete;//阻止拷贝
	testClass& operator=(const testClass&) = delete;//阻止赋值
};

//测试复杂容器实现时对对象的操作
class testDemo {
public:
	testDemo() { num = 0; }
	testDemo(int num) :num(num) {
		std::cout << "调用构造函数" << endl;
	}
	//在拷贝过程中，优先调用移动构造
	testDemo(const testDemo& other) :num(other.num) {
		std::cout << "调用拷贝构造函数" << endl;
	}

	testDemo& operator=(testDemo& other) {
		num = other.num;
		std::cout << "调用拷贝赋值函数" << endl;
		return *this;
	}

	//如果一个类由拷贝构造但没有移动构造，编译器不会合成移动构造
	testDemo(const testDemo&& other) :num(other.num) {
		std::cout << "调用移动构造函数" << endl;
	}
	//noexcept关键字承诺不抛出异常
	testDemo& operator=(testDemo&& other) noexcept {
		if (this != &other) {
			num = other.num;//内置类型自动移动赋值
			std::cout << "调用移动赋值函数" << endl;
		}
		return *this;
	}

	~testDemo() {
		std::cout << "调用析构函数" << endl;
	}
private:
	int num;
};

// 顺序容器包括 vector deque list forward_list array std::string
// 此处以vector为例
class testvector {
	std::vector<int>* pveci;
	std::vector<double>* pvecdou;
	std::vector<char>* pvecchar;
	//无应用意义，不如bitset，且迭代器易出错
	std::vector<bool> vecbool;
	std::vector<std::string> vecstr;
	std::vector<std::vector<int>> vvecint;
public:
	testvector() {
		init();
	}

	void init() {
		pveci = new std::vector<int>(2, 1);//2个1
		pvecdou = new std::vector<double>{ 1.2 ,2.3 ,3.4 };
		pveci = new std::vector<int>(*pveci);//拷贝赋值
		pvecchar = new std::vector<char>{ 3 };//3个默认初始化值
	}

	void add() {
		// push_back() 向容器尾部添加元素时，首先会创建这个
		// 元素，然后再将这个元素拷贝或者移动到容器中
		// （如果是拷贝的话，事后会自行销毁先前创建的这个元素） 
		//forward_list array 不支持此操作
		pveci->push_back(1);

		// emplace_back()在实现时，则是直接在容器尾部
		// 创建这个元素，省去了拷贝或移动元素的过程。
		pveci->emplace_back(2);


		//头插 部分容器支持 在迭代器指向的元素之前插入一个元素
		//vector不支持此操作，list支持
		//pveci.push_front();
		std::list<int> li1;
		li1.push_front(1);
		li1.emplace_front(1);

	}

	void inset() {
		std::vector<int>::iterator it;
		it = pveci->begin(); //索引为0的位置
		it = pveci->begin() + 2; //索引为2的位置

		//第一种格式用法
		// 在迭代器 pos 指定的位置之前插入一个新元素elem，
		// 并返回表示新插入元素位置的迭代器。
		pveci->insert(it, 2);

		//第二种格式用法
		// 在迭代器 pos 指定的位置之前插入3个元素2，
		// 并返回表示第一个新插入元素位置的迭代器。
		pveci->insert(it, 3, 2);

		//第三种格式用法
		//在迭代器 pos 指定的位置之前，插入其他容器
		//（不仅限于vector）中位于[first, last) 区域的
		//所有元素，并返回表示第一个新插入元素位置的迭代器。
		std::array<int, 3> test{ 7,8,9 };
		pveci->insert(pveci->end(), test.begin(), test.end());
		//{1,3,2,5,5,7,8,9}

		//第四种格式用法
		//在迭代器 pos 指定的位置之前，插入初始化列表（用大括号{}
		//括起来的多个元素，中间有逗号隔开）中所有的元素，
		// 并返回表示第一个新插入元素位置的迭代器
		pveci->insert(pveci->end(), { 10,11 });//{1,3,2,5,5,7,8,9,10,11}
	}

	void del() {
		//删除 vector 容器中最后一个元素，该容器的大小（size）会减 1，
		//但容量（capacity）不会发生改变
		pveci->pop_back();

		//删除 vector 容器中 pos 迭代器指定位置处的元素，并返回
		//指向被删除元素下一个位置元素的迭代器。该容器的大小（size）
		//会减 1，但容量（capacity）不会发生改变。
		pveci->erase(pveci->end());

		//删除 vector 容器中位于迭代器[beg, end)指定区域内的所有元素，
		//并返回指向被删除区域下一个位置元素的迭代器。该容器的大小(size)
		//会减小，但容量（capacity）不会发生改变。
		pveci->erase(pveci->begin(), pveci->end());

		//删除容器中所有和指定元素值相等的元素，并返回指向最后一个元素
		//下一个位置的迭代器。调用该函数不会改变容器的大小和容量。
		std::remove(pveci->begin(), pveci->end(), 0);

		//删除 vector 容器中所有的元素，使其变成空的 vector 容器。
		//该函数会改变 vector 的大小（变为 0），但不是改变其容量。
		pveci->clear();
	}

	void iter() {
		auto it1 = pveci->begin();//vector<int>::iterator
		auto it2 = pveci->rbegin();//vector<int>::reverse_iterator
		auto it3 = pveci->cbegin();//vector<int>::const_iterator
		auto it4 = pveci->crbegin();//vector<int>::const_reverse_iterator
	}

	void copy() {
		std::vector<int> vi1, vi2;
		vi1 = vi2;
		//swap不会导致指向该容器的迭代器、引用和指针失效
		swap(vi1, vi2);
		vi1.swap(vi2);

		//assign不适用于关联容器和array
		//vi1中的元素替换为迭代器范围内元素,迭代器元素不能指向vi1
		vi1.assign(vi2.begin(), vi2.end());
	}

	void deal() {
		//容器元素个数为0返回true
		pveci->empty();

		//返回容器中元素个数 forward_list不支持该函数
		pveci->size();

		//返回容器的大小
		pveci->capacity();

		//该容器不扩张内存能容纳最多元素数
		pveci->max_size();

		// 将容量减少为和size大小一致
		pveci->shrink_to_fit();

		// 分配能容纳10个元素的内存空间
		pveci->reserve(10);

	}
};

//关联容器 map set 
// multimap(关键字可重复出现的map),nultiset(关键字可重复出现的set)
// unordered_map(哈希函数组织的map),unordered_multimap()
class testmap {
public:
	//赋值
	void init() {
		//map中每个元素是pair对象
		map< string, size_t> mstr;
		mstr["one"] = 1;

		string words;
		while (cin >> words)
		{
			++mstr[words];
		}
		for (auto& w : mstr) {
			cout << w.first << "|" << w.second
				<< ((w.second > 1) ? "1s" : "2") << endl;
		}
		//pair类型赋值
		pair<int, string> p1;
		pair<int, string> p2(0, "zero");
		pair<int, string> p3 = std::make_pair(1, "one");

		//set类型的元素都是const
		set<int> iset = { 0,1,2,3,4 };
	}

	void iter() {
		map< string, size_t> mstr;
		mstr["one"] = 1;
		//*map_it是指向pair<string,size_t> 对象的引用
		auto map_it = mstr.begin();
		cout << "[" << map_it->first << "]=" << map_it->second << endl;

		//set容器的迭代器都是只读的
		set<int> iset = { 0,1,2,3,4 };
		auto set_it = iset.begin();
		cout << *set_it << endl;
	}

	void add() {
		vector<int> veci = { 0,1,2,3 };
		map<int, string> map1;
		//利用下标添加元素
		map1[6] = "six";
		//由于map的元素为pair，因此添加的实际上是pair对象
		map1.insert({ 0,"zero" });
		map1.insert(std::make_pair(0, "zero"));
		map1.insert(pair<int, string>(1, "one"));
		map1.insert(map<int, string>::value_type(2, "two"));
		//emplace 不同于insert在于inert是将对象复制一份再添加
		//emplace是直接在容器的内存空间中直接构造一个新的对象
		map1.emplace(pair<int, string>(3, "three"));

		set<int> seti;

		//直接添加字面值
		seti.insert(2);
		//通过迭代器添加
		seti.insert(veci.begin(), veci.end());
	}

	void del() {
		map<int, string> map1;
		map1.insert({ 0,"zero" });
		map1.insert(std::make_pair(0, "zero"));
		map1.insert(pair<int, string>(1, "one"));
		map1.insert(map<int, string>::value_type(2, "two"));

		//根据key删除value，返回删除的数量
		auto cnt = map1.erase(1);
		map1.insert(pair<int, string>(1, "one"));
		//删除迭代器指向的元素，返回指向该元素后的迭代器
		auto cnt1 = map1.erase(map1.begin());
		//删除迭代器之间的元素，并返回第二个参数
		auto cnt2 = map1.erase(map1.begin(), map1.end());

		map1.clear();//清空容器
	}

	void find() {
		set<int> seti = { 0,1,2,3,4,5 };
		//返回一个指向key=1的迭代器
		auto it1 = seti.find(1);
		//查找失败，返回一个指向seti.end的迭代器
		auto it2 = seti.find(11);
		//返回一个迭代器，指向第一个关键字不小于3的元素
		auto it3 = seti.lower_bound(3);
		//返回一个迭代器，指向第一个关键字大于3的元素
		auto it4 = seti.upper_bound(3);
		//返回一个迭代器pair，表示关键字等于3的范围，
	//若不存在，pair的两个成员均为end()
		auto it5 = seti.equal_range(3);

		auto count = seti.count(1);//count=1
		count = seti.count(11);//count=0

		map<int, string> map1;
		map1[0] = "zero";

	}

};


//无序关联容器，在存储上组织为桶，使用哈希函数映射来索引
class testunordered_map {
public:
	void init() {
		unordered_map<int, string> umap1;
		unordered_set<int> uset1;
	}

	void add() {//与有序类似
		unordered_map<int, string> umap1;
		umap1.insert({ 0,"zero" });
		umap1.insert(std::make_pair(1, "one"));
		umap1.emplace(std::make_pair(2, "two"));

		unordered_set<int> uset1;
		uset1.insert(1);
	}

	void bucket_deal() {
		unordered_map<int, string> umap1;
		umap1.insert({ 0,"zero" });
		umap1.insert(std::make_pair(1, "one"));
		umap1.emplace(std::make_pair(2, "two"));

		//使用中的桶的数量
		auto bcount = umap1.bucket_count();
		//容器能容纳的最多的桶的数量
		auto bmax = umap1.max_bucket_count();
		//关键字为1的元素在哪个桶
		auto bu = umap1.bucket(1);
		//每个桶的平均元素数量
		float f = umap1.load_factor();
		//维护桶的平均大小
		float fmax = umap1.max_load_factor();
		//重组存储，bcount >=rehash参数，且bcount> size /fmax
		umap1.rehash(bcount + 1);
		//重组存储，使umap1保存5个元素且不必rehash
		umap1.reserve(5);
	}
};

//测试STL常用算法函数
class testalgo {
public:
	void test() {
		vector<int> vi1{ 1,2,3,4,5,6 };
		find(vi1.begin(), vi1.end(), 3);
		find_if(vi1.begin(), vi1.end(),
			[](int a) {return a % 2 == 0 ? true : false; });
	}

	//accumulate主要用来对指定范围内元素求和，但也自行指定
	//一些其他操作，如范围内所有元素相乘、相除等。
	//accumulate(起始迭代器, 结束迭代器, 初始值, 自定义操作函数)
	// 原型 
	//template<class _InIt, class _Ty, class _Fn2>
	//inline _Ty _Accumulate(_InIt _First, _InIt _Last, _Ty _Val, _Fn2 _Func)
	//{   // return sum of _Val and all in [_First, _Last), using _Func  
	//	for (; _First != _Last; ++_First)
	//		_Val = _Func(_Val, *_First);
	//	return (_Val);
	//} 
	void test1() {
		vector<int> vi1{ 1,2,3 };
		deque<int> di{ 1,2,3 };
		list<int> li{ 1,2,3 };
		vector<string> str{ "123" ,"45","987" };
		// 对迭代器范围内元素求和
		int sum = accumulate(vi1.begin(), vi1.end(), 0);
		cout << sum << endl;//6

		sum = accumulate(di.begin(), di.end(), 0);
		cout << sum << endl;//6

		sum = accumulate(li.begin(), li.end(), 0);
		cout << sum << endl;//6 

		// 对迭代器范围内元素进行自定义运算
		sum = accumulate(vi1.begin(), vi1.end(), 0,
			[](int a, int b) {return a + b * 2; });
		cout << sum << endl;//12

		//拼接字符串
		string str_sum, init = "QA";
		str_sum = accumulate(str.begin(), str.end(), init);
		cout << str_sum << endl;//QA12345987 
	}

	//填充容器
	void test2() {
		vector<int> vi1{ 1,2,3 };
		//fill----前向迭代器
		fill(vi1.begin(), vi1.end(), 0);//每个元素置0
		fill(vi1.begin(), vi1.begin() + 1, 0);//第一个元素置0

		//fill_n-----输出迭代器
		fill_n(vi1.begin(), 3, 0);//将[beg,beg+3)区间的元素改为9
		fill_n(back_inserter(vi1), 6, 1);  //向vi1尾部添加6个1

		//插入迭代器,向容器添加元素。
		//以back_inserter为例,容器的末尾自动插入新元素

		vector<int> vi2;
		auto it = back_inserter(vi2);
		*it = 2;
		//算法不改变它所操纵的容器的大小，为什么使用
		//back_inserter也没有突破这个限制？
		//back_inserter效果相当于在容器上调用push_back 
	}

	//复制
	void test3() {
		//copy只负责复制，不负责申请空间，
		//所以复制前必须有足够的空间
		vector<int> vi1{ 1,2,3 }, vi2{ 4,5,6 };
		copy(vi1.begin(), vi1.end(), vi2.begin());
	}

	//排序
	void test4() {
		//当你需要按照某种特定方式进行排序时，你需要给sort
		//指定比较函数，否则程序会默认为less<T>()。

		vector < int > vect;

		sort(vect.begin(), vect.end());
		//此时相当于调用
		sort(vect.begin(), vect.end(), std::less<int>());
		sort(vect.begin(), vect.end(),
			[](int& a, int& b) {return b < a; });

		//stable_sort函数保证相等元素的原本相对次序在排序后保持不变
		//对于复杂类型如string ，元素相等不代表元素相同
		stable_sort(vect.begin(), vect.end(), [](int a, int b) {return (b < a); });

		//unique消除重复项，并返回一个消除后的末尾迭代器
		//消除是指临近元素覆盖了重复元素导致末尾迭代器之后的值不可靠
		auto v = unique(vect.begin(), vect.end());
	}
};

class testIter {
public:
	//插入迭代器
	void test1() {
		vector<int>* pvi = new vector<int>;
		//只有容器支持push_front和push_back才能使用back_inserter,front_inserter
		auto back_iter = back_inserter(*pvi);
		auto front_iter = front_inserter(*pvi);

		auto inerst_iter = inserter(*pvi, pvi->begin());
	}

	//流迭代器
	void test2() {
		int flag = 2;
		switch (flag)
		{
		case 0: {
			int c;
			//cin >> c;
			std::istream_iterator<int> int_it(cin);  //从cin读取int
			std::istream_iterator<int> int_eof;//尾后迭代器
			vector<int> vec;
			while (int_it != int_eof)//当有数据可供读取时
			{
				//后置递增运算符，返回迭代器的旧值
				//解引用迭代器，获得从流读取的前一个值
				vec.push_back(*int_it++);
			}
			break;
		}

		case 1: {
			//使用算法对迭代器进行操作
			//终止输入需要CTRL +z ，再按回车
			std::istream_iterator<int> int_it(cin), eof;
			cout << accumulate(int_it, eof, 0) << endl;
			break;
		}
		case 2: {
			//out将int值写入输出流cout中 
			vector<int> vec(10, 1);
			std::ostream_iterator<int> out_iter(cout, " ");
			for (auto e : vec)
				*out_iter++ = e;
			cout << endl;
			break;
		}
		case 3: {
			//利用copy函数和迭代器打印
			vector<int> vec(10, 1);
			std::ostream_iterator<int> out_iter(cout, " ");
			copy(vec.begin(), vec.end(), out_iter);
			break;
		}
		}
	}

	//反向迭代器 从尾元素向首元素移动
	void test3() {
		//除了forward_list以外，其他容器都支持反向迭代器
		vector<int>* vei = new vector<int>{ 1,2,3,4,5 };
		auto r_iter = vei->rbegin();
		for (auto i = vei->crbegin(); i != vei->crend(); ++i) {
			cout << *i << endl;//5 4 3 2 1
		}
	}

	//算法迭代器分类
	void test4() {
		//1. 输入迭代器
		//只读，不写，单遍扫描，只能递增
		// 如find accumulate istream_iterator
		//  必须支持 == 、!=、++、-> 运算符

		//2. 输出迭代器
		//只写，不读，单遍扫描，只能递增
		// 如ostream_iterator copy的第三个参数 
		//  必须支持 * 、++、  运算符

		//3. 前向迭代器 
		//可读写，多遍扫描，只能递增
		// 如算法replace要求前向迭代器，forward_list的迭代器

		//4. 双向迭代器
		//可读写，多遍扫描，可递增递减
		// 支持前置迭代器的操作，还支持 --
		// 如reverse要求双向迭代器

		//5. 随机访问迭代器
		//可读写，多遍扫描，支持全部迭代器运算
		//支持 < 、<= 、>、 >= += -= 
		//下标运算符，两个迭代器上的减法迭代器- ,得到迭代器的距离
	}
};

//智能指针
class tsetptr {
public:
	//shared_ptr允许多个指针指向同一个对象
	void testshared_ptr() {
		//init 
		//way1 shared_ptr独有操作
		auto sp1 = std::make_shared<int>(5);
		//way2
		int* p1 = new int[0];
		shared_ptr<int> sp2(p1);
		//way3
		shared_ptr<int> sp3(new int[2]);
		//way4 增加引用计数
		shared_ptr<int> sp4(sp3);

		//为了避免代码错误发生在指针初始化后，指针删除之间
		//导致指针对象无法释放，导致内存泄露或资源锁死
		//在初始化时，使用删除器函数代替delete。完成对指针进行释放的操作
		int i = 9;
		shared_ptr<int> sp5(&i, [](int* p) { delete p; });

		//deal
		//获取原指针
		int* p2 = sp1.get();
		auto num = sp4.use_count();//2
		{
			//1.不要让一个裸指针初始化多个 shared_ptr  
			{
				int* p1 = new int[2];

				shared_ptr<int> sp6(p1);
				shared_ptr<int> sp7(p1);
			}

			//2.不要主动删除 shared_ptr 所管理的裸指针
			{
				testDemo* tmp = new testDemo(1);
				shared_ptr<testDemo> sp6(tmp);
				long num1 = sp6.use_count();//1
				delete   tmp;
				long num2 = sp6.use_count();//1
				sp6 = nullptr;//error
			}
			//3 保护好裸指针
			{
				shared_ptr<int> p(new int[1]);
				int* q = p.get();
				{
					shared_ptr<int>(q);
				}
				int foo = *p;
			}
		}

	}

	void tsetunique_ptr() {
		int* pi = new int(2);
		unique_ptr<int> p1;
		unique_ptr<int> p2(new int(3));
		//unique_ptr拥有所指向的对象,因此不支持普通的拷贝和赋值
		//unique_ptr<int> p3(p2);//error
		//p3 = p2;//error

		//release将p2置空，并返回保存的对象指针
		unique_ptr<int> p3(p2.release());//ok

		 //带删除器的初始化
		auto testEnd = [](int* i) {delete i; };
		unique_ptr<int, decltype(testEnd)> p4(new int(3), testEnd);

		//释放p3指向的对象
		p3.reset();

		//令p3指向pi
		p3.reset(pi);


	}

	void testweak_ptr() {
		//weak_ptr是一种不控制所指向对象生存期的智能指针
		//指向一个由shared_ptr管理的对象
		weak_ptr<int> wp1;

		shared_ptr<int> sp1;
		weak_ptr<int>wp2(sp1);
		weak_ptr<int> wp3;
		wp3 = wp2;

		{
			wp3.reset();
			//wp1共享对象的shared_ptr的数量
			wp1.use_count();
			//若wp1.use_count()为0，返回true ,否则为false
			wp1.expired();
			//若expired()为true，返回一个空shared_ptr,
			//否则为一个指向wp1对象的shared_ptr
			wp1.lock();
		}
	}
};

namespace exam {
	void test1(std::istream& is) {
		auto old_state = is.rdstate();
		std::string ss;
		while (is >> ss)
		{
			cout << ss << endl;
		}
		is.flags();
		is.setstate(old_state);
	}

	//文件IO流
	void test2() {
		std::ifstream input1(
			"C:\\Users\\maker\\Desktop\\Untitled1.cpp"
			, std::ifstream::in);

		std::ifstream input2;

		input2.open(
			" C:\\Users\\maker\\Desktop\\Untitled1.cpp"
			, std::ifstream::in);

		std::string s;
		std::vector<std::string> vecs;
		while (!input1.eof())
		{
			std::getline(input1, s);
			vecs.push_back(s);
			cout << s << endl;
		}
	}

	static void output1(int x, int y) {
		std::cout << x << " " << y << std::endl;
	}

	void test3() {
		std::bind(output1, 1, 2)(); // 输出 : 1 2

		//使用plcaeholders作为占位符，重排默认参数顺序
		std::bind(output1, std::placeholders::_1, 2)(1); // 输出 : 1 2
		std::bind(output1, 2, std::placeholders::_1)(1); // 输出 : 2 1

		// error: 调用时没有第二个参数
		//std::bind(output, 2, std::placeholders::_2)(1);
		std::bind(output1, 2, std::placeholders::_2)(1, 2); // 输出 : 2 2

		// 调用时的第一个参数被吞掉了
		std::bind(output1, std::placeholders::_1,
			std::placeholders::_2)(1, 2); // 输出 : 1 2
		std::bind(output1, std::placeholders::_2,
			std::placeholders::_1)(1, 2); // 输出 : 2 1

		//使用ref和cref传入引用，避免对参数的拷贝 
		int a = 1, b = 2;
		//参数为&a ，const &b
		std::bind(output1, std::ref(a), std::cref(b))(); // 输出 : 1 2
	}

	//测试allocator类
	void test4() {
		//allocator将内存分配与对象初始化进行分离，
		//避免了定义时的浪费
		std::allocator<int> ai1;
		//分配了一段未构造的内存，可以保存3个int类型对象 ,并返回指针
		int* pi1 = ai1.allocate(3);

		//对指针按照其类型构造一个对象，可添加参数作为传递给构造参数
		auto end = pi1;
		ai1.construct(end++, 1);
		ai1.construct(end++, 2);
		ai1.construct(end, 3);
		//cout << *pi1 << endl;//1
		//cout << *(pi1 + 1) << endl;//2
		//cout << *(pi1 + 2) << endl;//2

		//对指针指向的对象执行析构函数
		ai1.destroy(pi1);

		//释放指针种地址开始的内存，这块内存保存了3个int类型对象
		//指针必须是allocate返回的指针，第二个参数且必须和创造时大小一致
		//必须先对此内存中的每个对象调用destroy
		ai1.deallocate(pi1, 3);

		//对容器进行操作
		vector<int> vi{ 0,1,2,3,4,5 };
		//std::allocator<int> ai2;
		int* pi2 = ai1.allocate(vi.size());
		//将迭代器范围之间的元素拷贝到未构造的原始内存中
		std::uninitialized_copy(vi.begin(), vi.end(), pi2);
		for (int i = 0; i < vi.size(); i++) {
			//cout << *(pi2+i) << endl;//0 1 2 3 4 5
		}


		//std::allocator<int> ai1;
		int* pi3 = ai1.allocate(3);
		//将迭代器指向的元素开始，拷贝3个元素到未构造的原始内存中
		std::uninitialized_copy_n(vi.begin(), 3, pi3);
		for (int i = 0; i < 3; i++) {
			cout << *(pi3 + i) << endl;//0 1 2  
		}

		int* pi4 = ai1.allocate(4);
		//在迭代器指定的原始内存范围内创建对象，对象均为3的拷贝
		std::uninitialized_fill(pi4, pi4 + 4, 3);
		for (int i = 0; i < 4; i++) {
			cout << *(pi4 + i) << endl;//3 3 3 3  
		}

		int* pi5 = ai1.allocate(5);
		//从迭代器指向的内存地址开始，创建5个元素，值为2
		std::uninitialized_fill_n(pi5, 5, 2);
		for (int i = 0; i < 5; i++) {
			cout << *(pi5 + i) << endl;//2 2 2 2 2
		}
	}

	//测试rand
	void test5() {

	}

	//测试regex
	void test6() {

	}
}

//左值和右值使用辨析实例
namespace test_class {
	class ctest1 {
	public:
		ctest1() {}
		ctest1(int i) {
			str = std::to_string(i);
		}

		ctest1(string s) {
			cout << "const" << endl;
			str = s;
		}
		//test1& operator=(const test1& other) {}
		//采取引用限定符&或&&，分别指出this可以指向左值或右值
		ctest1& operator=(const ctest1& other)& {
			str = other.str;
			return *this;
		}

		ctest1& operator=(const ctest1& other)&& {
			str = other.str;
			return *this;
		}
		ctest1& operator+(const ctest1& other) {
			str += other.str;
			return *this;
		}

		int find(char c) {
			return str.find(c);
		}

		//重载io操作符的两种方式，一种是友元类，一种是全局函数形式
		 //cout<< ctest1 等价于 cout << ctest1.str
		friend ostream& operator<<(ostream& os, ctest1& other) {
			os << other.str;
			return os;
		}
		friend istream& operator>>(istream& is, ctest1& other) {
			is >> other.str;
			return is;
		}

		//重载前置和后置运算符
	   //前置
		ctest1& operator++() {
			str += "0";
			return *this;
		}

		//后置运算符重载接收一个额外的int类型的形参，
			//调用时，为形参提供一个值为0的实参 
		ctest1& operator++(int) {
			str += "1";
			return *this;
		}

		//重载下标运算符
		char operator[](int  i) {
			return str[i];
		}

		//重载成员访问运算符
		const string& operator*() const {
			return  str;
		}
		//箭头运算符不能改变成员访问这一基本含义，
		//但可以改变箭头从哪个对象获取成员
		string& operator->() {
			return str;
		}

		//函数调用运算符
		string& operator()(string s) {
			str = s;
			cout << " ()" << endl;
			return s;
		}

		//类型转换运算符
		//编译器一次只能执行一个用户定义的类型转换，
		//但隐式的用户定义的类型转换置于标准 类型转换之前或之后
		operator int() {
			return str.size();
		}
	private:
		string str;
	};

	class ctest2 {
	public:
		explicit ctest2(int i) {
			str = std::to_string(i);
		}
		//通过关键字限制，不允许隐式类型转换
		//但当表达式被用做判断语句的条件，显式会转为隐式执行
		explicit operator int() const {
			return str.size();
		}
	private:
		string str;
	};

	class Quote {
	public:
		Quote() = default;
		Quote(const string& book, double sales_price) :
			bookNo(book), price(sales_price) {}
		virtual double net_price(std::size_t n) const {
			return n * price;
		}
		virtual ~Quote() = default;
	protected:
		double price = 0;
	private:
		string bookNo;
	};


	class Bulk_quote :public Quote {
	public:
		Bulk_quote() = default;

		Bulk_quote(const string& book, double sales_price,
			std::size_t, double) :
			bookNo(book), price(sales_price) {}

		double net_price(std::size_t n) const  override {}

		~Bulk_quote() = default;
	protected:
		double price = 0;
	private:
		string bookNo;
	};

	void test1() {
		//如何避免右值调用函数和对右值赋值
		//对类增加引用限定符
		ctest1 s1("value"), s2("s2");
		auto n = (s1 + s2).find('a');//n=1,s1=values2

		auto n1 = s1++;//values21
		auto n2 = ++s1;//values210
		auto n3 = s1[2];
		auto n4 = s1("123");
	}

	void tset2() {
		ctest1 cs1(3.14);//double 自动转为 int
		auto n = cs1 * 8; //cs1 自动转为 int

		ctest2 cs2(3.14);
		//auto n1 = cs2 * 2;//error
		auto n2 = static_cast<int>(cs2) + 3;
	}

	//左值 右值绑定的两种特殊情况
	template <typename T> void f1(T&& t) {}
	void test3() {
		//第一种情况
		int i = 0;
		int& i1 = i;
		f1(i);
		//将左值作为右值引用，模板类型参数T推断为左值引用类型int&
		// 将函数参数变成了int&类型的右值引用 即 (int& && t)
		//引出了第二种情况，间接创建了引用的引用，形成了折叠
		 //X& & / X& && / X&& & 都折叠成 X&
		//X&& && 折叠成 X&&
		f1(i1);// int& && 
	}
}

namespace testTemplate {
	//类模板
	template <typename T>
	class Blob {
	public:
		typedef T value_type;
		typedef typename vector<T>::size_type size_type;
		Blob() {}
		//Blob() :m_data(std::make_shared<vector<T>>()){}
		//initializer_list是是C++11提供的一种模板类型
		Blob(std::initializer_list<T> il) {}
		~Blob() {}

		size_type size() const { return m_data->size(); }

		bool empty() const { return m_data->empty(); }

		void push_back(const T& t) { m_data->push_back(t); }
		void push_back(T&& t) { m_data->push_back(std::move(t)); }

		void pop_back() {
			check(0, "pop_back error");
			m_data->pop_back();
		}

		T& back() {
			check(0, "back error");
			return m_data->back();
		}

		T& operator[](size_type i) {
			check(0, "out of range error");
			return m_data[i];
		}

	private:
		shared_ptr<vector<T>> m_data;
		void check(size_type i, const string& msg)const {
			if (i >= m_data->size())
				throw std::out_of_range(msg);
		}
	};

	//成员模板
	template<typename T>
	T& add(T& a, T& b) {
		return a + b;
	}

	//指定显示模板实参
	template<typename T1, typename T2, typename T3>
	T1 sum(T2 t2, T3 t3) {
		return t2 + t3;
	}

	//尾置返回类型
	template<typename T>
	auto multi(T& a, T& b)->decltype(a) {
		return a * b;
	}

	int sum(int t2, int t3) {
		cout << "sum" << endl;
		return t2 + t3;
	}


	template<typename T>
	void print(T t) {
		cout << t << endl;
	}
	//可变参数模板 
	//标准c++规定，非类型模板形参包只能为整型、指针和引用
	template<typename... Args>
	void sum(Args ... args) {
		int num = sizeof...(args);
		cout << num << endl;
		//int arr[] = { (std::cout << args<<"",args)...};
		//可变参数模板的使用方式有两种，递归展开和参数包展开(c17支持)

		//print(args...);

	}

	//模板特例化
	template<>//空<>指出将为原模板所有模板参数提供实参
	int sum(string s1, string s2) {
		return s1.size() + s2.size();
	}


	void test1() {
		int i1 = 1;
		long i2 = 2;
		//调用时指定模板类型
		auto n1 = sum<long long int>(i1, i2);//long sum(long,long)

		//正常类型应用 会将实参隐式转换为模板类型
		auto n2 = sum<int long long>(i1, i2);//int sum(long ,long)
	}

	void test2() {
		//函数指针
		int (*pf1)(int& a, int& b) = sum;

		void  func(int(*)(int&, int&));
		void  func(int(*)(string&, string&));
		//func(sum);//error 有多个重载函数参数列表匹配
	}

	void test3() {
		// 模板和非模板函数同时存在时，优先调用非模板
		//sum(1, 2);//sum
		sum(1, 2, 3, 4);//4
	}
}

//测试多重继承、虚继承
namespace testoverride {
	struct Base1
	{
		Base1() {
			cout << "Base1 构造" << endl;
		}

		Base1(int num) :m_num(num) {}

		Base1(Base1& b) {
			cout << "Base1 拷贝构造" << endl;
			m_num = b.m_num;
		}

		Base1& operator=(Base1& b) {
			cout << "Base1 拷贝赋值" << endl;
			m_num = b.m_num;
			return *this;
		}

		~Base1() {
			cout << "Base1 析构" << endl;
		}
	private:
		int m_num;
	};

	class A1 :public Base1 {
	public:
		A1() {
			cout << "A1 构造" << endl;
		}

		A1(int num) :m_num1(num) {}

		A1(A1& a) {
			m_num1 = a.m_num1;
			cout << "A1 拷贝构造" << endl;
		}

		A1& operator=(A1& b) {
			cout << "A1 拷贝赋值" << endl;
			m_num1 = b.m_num1;
			return *this;
		}

		~A1() {
			cout << "A1 析构" << endl;
		}
	private:
		int m_num1;
	};

	class B1 :public Base1 {
	public:
		B1() {
			cout << "B1 构造" << endl;
		}

		B1(int num) :b_num1(num) {}

		B1(B1& a) {
			b_num1 = a.b_num1;
			cout << "B1 拷贝构造" << endl;
		}

		B1& operator=(B1& b) {
			cout << "B1 拷贝赋值" << endl;
			b_num1 = b.b_num1;
			return *this;
		}

		~B1() {
			cout << "B1 析构" << endl;
		}
	private:
		int b_num1;

	};
}