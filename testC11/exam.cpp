#include<string>
using std::string;

#include<vector>
using std::vector;

#include<deque>
using std::deque;

#include<list>
using std::list;

#include<array> 
//����ͷ�ļ�
//��������
#include<utility>
using std::pair;

#include<map>
using std::map;
using std::multimap;

//�����������
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

// �㷨ͷ�ļ�
#include <algorithm>
#include<numeric>
#include<iterator>
#include<functional>
//IO��
#include<iostream>
using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::endl;
#include<fstream>
#include<sstream>
//����c++ primer ����� ��ϰ����


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
	// �������ַ�ʽ�ȼ�
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
	testClass() = default;//ʹ��Ĭ�Ϲ���
	testClass(const testClass&) = delete;//��ֹ����
	testClass& operator=(const testClass&) = delete;//��ֹ��ֵ
};

//���Ը�������ʵ��ʱ�Զ���Ĳ���
class testDemo {
public:
	testDemo() { num = 0; }
	testDemo(int num) :num(num) {
		std::cout << "���ù��캯��" << endl;
	}
	//�ڿ��������У����ȵ����ƶ�����
	testDemo(const testDemo& other) :num(other.num) {
		std::cout << "���ÿ������캯��" << endl;
	}

	testDemo& operator=(testDemo& other) {
		num = other.num;
		std::cout << "���ÿ�����ֵ����" << endl;
		return *this;
	}

	//���һ�����ɿ������쵫û���ƶ����죬����������ϳ��ƶ�����
	testDemo(const testDemo&& other) :num(other.num) {
		std::cout << "�����ƶ����캯��" << endl;
	}
	//noexcept�ؼ��ֳ�ŵ���׳��쳣
	testDemo& operator=(testDemo&& other) noexcept {
		if (this != &other) {
			num = other.num;//���������Զ��ƶ���ֵ
			std::cout << "�����ƶ���ֵ����" << endl;
		}
		return *this;
	}

	~testDemo() {
		std::cout << "������������" << endl;
	}
private:
	int num;
};

// ˳���������� vector deque list forward_list array std::string
// �˴���vectorΪ��
class testvector {
	std::vector<int>* pveci;
	std::vector<double>* pvecdou;
	std::vector<char>* pvecchar;
	//��Ӧ�����壬����bitset���ҵ������׳���
	std::vector<bool> vecbool;
	std::vector<std::string> vecstr;
	std::vector<std::vector<int>> vvecint;
public:
	testvector() {
		init();
	}

	void init() {
		pveci = new std::vector<int>(2, 1);//2��1
		pvecdou = new std::vector<double>{ 1.2 ,2.3 ,3.4 };
		pveci = new std::vector<int>(*pveci);//������ֵ
		pvecchar = new std::vector<char>{ 3 };//3��Ĭ�ϳ�ʼ��ֵ
	}

	void add() {
		// push_back() ������β�����Ԫ��ʱ�����Ȼᴴ�����
		// Ԫ�أ�Ȼ���ٽ����Ԫ�ؿ��������ƶ���������
		// ������ǿ����Ļ����º������������ǰ���������Ԫ�أ� 
		//forward_list array ��֧�ִ˲���
		pveci->push_back(1);

		// emplace_back()��ʵ��ʱ������ֱ��������β��
		// �������Ԫ�أ�ʡȥ�˿������ƶ�Ԫ�صĹ��̡�
		pveci->emplace_back(2);


		//ͷ�� ��������֧�� �ڵ�����ָ���Ԫ��֮ǰ����һ��Ԫ��
		//vector��֧�ִ˲�����list֧��
		//pveci.push_front();
		std::list<int> li1;
		li1.push_front(1);
		li1.emplace_front(1);

	}

	void inset() {
		std::vector<int>::iterator it;
		it = pveci->begin(); //����Ϊ0��λ��
		it = pveci->begin() + 2; //����Ϊ2��λ��

		//��һ�ָ�ʽ�÷�
		// �ڵ����� pos ָ����λ��֮ǰ����һ����Ԫ��elem��
		// �����ر�ʾ�²���Ԫ��λ�õĵ�������
		pveci->insert(it, 2);

		//�ڶ��ָ�ʽ�÷�
		// �ڵ����� pos ָ����λ��֮ǰ����3��Ԫ��2��
		// �����ر�ʾ��һ���²���Ԫ��λ�õĵ�������
		pveci->insert(it, 3, 2);

		//�����ָ�ʽ�÷�
		//�ڵ����� pos ָ����λ��֮ǰ��������������
		//����������vector����λ��[first, last) �����
		//����Ԫ�أ������ر�ʾ��һ���²���Ԫ��λ�õĵ�������
		std::array<int, 3> test{ 7,8,9 };
		pveci->insert(pveci->end(), test.begin(), test.end());
		//{1,3,2,5,5,7,8,9}

		//�����ָ�ʽ�÷�
		//�ڵ����� pos ָ����λ��֮ǰ�������ʼ���б��ô�����{}
		//�������Ķ��Ԫ�أ��м��ж��Ÿ����������е�Ԫ�أ�
		// �����ر�ʾ��һ���²���Ԫ��λ�õĵ�����
		pveci->insert(pveci->end(), { 10,11 });//{1,3,2,5,5,7,8,9,10,11}
	}

	void del() {
		//ɾ�� vector ���������һ��Ԫ�أ��������Ĵ�С��size����� 1��
		//��������capacity�����ᷢ���ı�
		pveci->pop_back();

		//ɾ�� vector ������ pos ������ָ��λ�ô���Ԫ�أ�������
		//ָ��ɾ��Ԫ����һ��λ��Ԫ�صĵ��������������Ĵ�С��size��
		//��� 1����������capacity�����ᷢ���ı䡣
		pveci->erase(pveci->end());

		//ɾ�� vector ������λ�ڵ�����[beg, end)ָ�������ڵ�����Ԫ�أ�
		//������ָ��ɾ��������һ��λ��Ԫ�صĵ��������������Ĵ�С(size)
		//���С����������capacity�����ᷢ���ı䡣
		pveci->erase(pveci->begin(), pveci->end());

		//ɾ�����������к�ָ��Ԫ��ֵ��ȵ�Ԫ�أ�������ָ�����һ��Ԫ��
		//��һ��λ�õĵ����������øú�������ı������Ĵ�С��������
		std::remove(pveci->begin(), pveci->end(), 0);

		//ɾ�� vector ���������е�Ԫ�أ�ʹ���ɿյ� vector ������
		//�ú�����ı� vector �Ĵ�С����Ϊ 0���������Ǹı���������
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
		//swap���ᵼ��ָ��������ĵ����������ú�ָ��ʧЧ
		swap(vi1, vi2);
		vi1.swap(vi2);

		//assign�������ڹ���������array
		//vi1�е�Ԫ���滻Ϊ��������Χ��Ԫ��,������Ԫ�ز���ָ��vi1
		vi1.assign(vi2.begin(), vi2.end());
	}

	void deal() {
		//����Ԫ�ظ���Ϊ0����true
		pveci->empty();

		//����������Ԫ�ظ��� forward_list��֧�ָú���
		pveci->size();

		//���������Ĵ�С
		pveci->capacity();

		//�������������ڴ����������Ԫ����
		pveci->max_size();

		// ����������Ϊ��size��Сһ��
		pveci->shrink_to_fit();

		// ����������10��Ԫ�ص��ڴ�ռ�
		pveci->reserve(10);

	}
};

//�������� map set 
// multimap(�ؼ��ֿ��ظ����ֵ�map),nultiset(�ؼ��ֿ��ظ����ֵ�set)
// unordered_map(��ϣ������֯��map),unordered_multimap()
class testmap {
public:
	//��ֵ
	void init() {
		//map��ÿ��Ԫ����pair����
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
		//pair���͸�ֵ
		pair<int, string> p1;
		pair<int, string> p2(0, "zero");
		pair<int, string> p3 = std::make_pair(1, "one");

		//set���͵�Ԫ�ض���const
		set<int> iset = { 0,1,2,3,4 };
	}

	void iter() {
		map< string, size_t> mstr;
		mstr["one"] = 1;
		//*map_it��ָ��pair<string,size_t> ���������
		auto map_it = mstr.begin();
		cout << "[" << map_it->first << "]=" << map_it->second << endl;

		//set�����ĵ���������ֻ����
		set<int> iset = { 0,1,2,3,4 };
		auto set_it = iset.begin();
		cout << *set_it << endl;
	}

	void add() {
		vector<int> veci = { 0,1,2,3 };
		map<int, string> map1;
		//�����±����Ԫ��
		map1[6] = "six";
		//����map��Ԫ��Ϊpair�������ӵ�ʵ������pair����
		map1.insert({ 0,"zero" });
		map1.insert(std::make_pair(0, "zero"));
		map1.insert(pair<int, string>(1, "one"));
		map1.insert(map<int, string>::value_type(2, "two"));
		//emplace ��ͬ��insert����inert�ǽ�������һ�������
		//emplace��ֱ�����������ڴ�ռ���ֱ�ӹ���һ���µĶ���
		map1.emplace(pair<int, string>(3, "three"));

		set<int> seti;

		//ֱ���������ֵ
		seti.insert(2);
		//ͨ�����������
		seti.insert(veci.begin(), veci.end());
	}

	void del() {
		map<int, string> map1;
		map1.insert({ 0,"zero" });
		map1.insert(std::make_pair(0, "zero"));
		map1.insert(pair<int, string>(1, "one"));
		map1.insert(map<int, string>::value_type(2, "two"));

		//����keyɾ��value������ɾ��������
		auto cnt = map1.erase(1);
		map1.insert(pair<int, string>(1, "one"));
		//ɾ��������ָ���Ԫ�أ�����ָ���Ԫ�غ�ĵ�����
		auto cnt1 = map1.erase(map1.begin());
		//ɾ��������֮���Ԫ�أ������صڶ�������
		auto cnt2 = map1.erase(map1.begin(), map1.end());

		map1.clear();//�������
	}

	void find() {
		set<int> seti = { 0,1,2,3,4,5 };
		//����һ��ָ��key=1�ĵ�����
		auto it1 = seti.find(1);
		//����ʧ�ܣ�����һ��ָ��seti.end�ĵ�����
		auto it2 = seti.find(11);
		//����һ����������ָ���һ���ؼ��ֲ�С��3��Ԫ��
		auto it3 = seti.lower_bound(3);
		//����һ����������ָ���һ���ؼ��ִ���3��Ԫ��
		auto it4 = seti.upper_bound(3);
		//����һ��������pair����ʾ�ؼ��ֵ���3�ķ�Χ��
	//�������ڣ�pair��������Ա��Ϊend()
		auto it5 = seti.equal_range(3);

		auto count = seti.count(1);//count=1
		count = seti.count(11);//count=0

		map<int, string> map1;
		map1[0] = "zero";

	}

};


//��������������ڴ洢����֯ΪͰ��ʹ�ù�ϣ����ӳ��������
class testunordered_map {
public:
	void init() {
		unordered_map<int, string> umap1;
		unordered_set<int> uset1;
	}

	void add() {//����������
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

		//ʹ���е�Ͱ������
		auto bcount = umap1.bucket_count();
		//���������ɵ�����Ͱ������
		auto bmax = umap1.max_bucket_count();
		//�ؼ���Ϊ1��Ԫ�����ĸ�Ͱ
		auto bu = umap1.bucket(1);
		//ÿ��Ͱ��ƽ��Ԫ������
		float f = umap1.load_factor();
		//ά��Ͱ��ƽ����С
		float fmax = umap1.max_load_factor();
		//����洢��bcount >=rehash��������bcount> size /fmax
		umap1.rehash(bcount + 1);
		//����洢��ʹumap1����5��Ԫ���Ҳ���rehash
		umap1.reserve(5);
	}
};

//����STL�����㷨����
class testalgo {
public:
	void test() {
		vector<int> vi1{ 1,2,3,4,5,6 };
		find(vi1.begin(), vi1.end(), 3);
		find_if(vi1.begin(), vi1.end(),
			[](int a) {return a % 2 == 0 ? true : false; });
	}

	//accumulate��Ҫ������ָ����Χ��Ԫ����ͣ���Ҳ����ָ��
	//һЩ�����������緶Χ������Ԫ����ˡ�����ȡ�
	//accumulate(��ʼ������, ����������, ��ʼֵ, �Զ����������)
	// ԭ�� 
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
		// �Ե�������Χ��Ԫ�����
		int sum = accumulate(vi1.begin(), vi1.end(), 0);
		cout << sum << endl;//6

		sum = accumulate(di.begin(), di.end(), 0);
		cout << sum << endl;//6

		sum = accumulate(li.begin(), li.end(), 0);
		cout << sum << endl;//6 

		// �Ե�������Χ��Ԫ�ؽ����Զ�������
		sum = accumulate(vi1.begin(), vi1.end(), 0,
			[](int a, int b) {return a + b * 2; });
		cout << sum << endl;//12

		//ƴ���ַ���
		string str_sum, init = "QA";
		str_sum = accumulate(str.begin(), str.end(), init);
		cout << str_sum << endl;//QA12345987 
	}

	//�������
	void test2() {
		vector<int> vi1{ 1,2,3 };
		//fill----ǰ�������
		fill(vi1.begin(), vi1.end(), 0);//ÿ��Ԫ����0
		fill(vi1.begin(), vi1.begin() + 1, 0);//��һ��Ԫ����0

		//fill_n-----���������
		fill_n(vi1.begin(), 3, 0);//��[beg,beg+3)�����Ԫ�ظ�Ϊ9
		fill_n(back_inserter(vi1), 6, 1);  //��vi1β�����6��1

		//���������,���������Ԫ�ء�
		//��back_inserterΪ��,������ĩβ�Զ�������Ԫ��

		vector<int> vi2;
		auto it = back_inserter(vi2);
		*it = 2;
		//�㷨���ı��������ݵ������Ĵ�С��Ϊʲôʹ��
		//back_inserterҲû��ͻ��������ƣ�
		//back_inserterЧ���൱���������ϵ���push_back 
	}

	//����
	void test3() {
		//copyֻ�����ƣ�����������ռ䣬
		//���Ը���ǰ�������㹻�Ŀռ�
		vector<int> vi1{ 1,2,3 }, vi2{ 4,5,6 };
		copy(vi1.begin(), vi1.end(), vi2.begin());
	}

	//����
	void test4() {
		//������Ҫ����ĳ���ض���ʽ��������ʱ������Ҫ��sort
		//ָ���ȽϺ�������������Ĭ��Ϊless<T>()��

		vector < int > vect;

		sort(vect.begin(), vect.end());
		//��ʱ�൱�ڵ���
		sort(vect.begin(), vect.end(), std::less<int>());
		sort(vect.begin(), vect.end(),
			[](int& a, int& b) {return b < a; });

		//stable_sort������֤���Ԫ�ص�ԭ����Դ���������󱣳ֲ���
		//���ڸ���������string ��Ԫ����Ȳ�����Ԫ����ͬ
		stable_sort(vect.begin(), vect.end(), [](int a, int b) {return (b < a); });

		//unique�����ظ��������һ���������ĩβ������
		//������ָ�ٽ�Ԫ�ظ������ظ�Ԫ�ص���ĩβ������֮���ֵ���ɿ�
		auto v = unique(vect.begin(), vect.end());
	}
};

class testIter {
public:
	//���������
	void test1() {
		vector<int>* pvi = new vector<int>;
		//ֻ������֧��push_front��push_back����ʹ��back_inserter,front_inserter
		auto back_iter = back_inserter(*pvi);
		auto front_iter = front_inserter(*pvi);

		auto inerst_iter = inserter(*pvi, pvi->begin());
	}

	//��������
	void test2() {
		int flag = 2;
		switch (flag)
		{
		case 0: {
			int c;
			//cin >> c;
			std::istream_iterator<int> int_it(cin);  //��cin��ȡint
			std::istream_iterator<int> int_eof;//β�������
			vector<int> vec;
			while (int_it != int_eof)//�������ݿɹ���ȡʱ
			{
				//���õ�������������ص������ľ�ֵ
				//�����õ���������ô�����ȡ��ǰһ��ֵ
				vec.push_back(*int_it++);
			}
			break;
		}

		case 1: {
			//ʹ���㷨�Ե��������в���
			//��ֹ������ҪCTRL +z ���ٰ��س�
			std::istream_iterator<int> int_it(cin), eof;
			cout << accumulate(int_it, eof, 0) << endl;
			break;
		}
		case 2: {
			//out��intֵд�������cout�� 
			vector<int> vec(10, 1);
			std::ostream_iterator<int> out_iter(cout, " ");
			for (auto e : vec)
				*out_iter++ = e;
			cout << endl;
			break;
		}
		case 3: {
			//����copy�����͵�������ӡ
			vector<int> vec(10, 1);
			std::ostream_iterator<int> out_iter(cout, " ");
			copy(vec.begin(), vec.end(), out_iter);
			break;
		}
		}
	}

	//��������� ��βԪ������Ԫ���ƶ�
	void test3() {
		//����forward_list���⣬����������֧�ַ��������
		vector<int>* vei = new vector<int>{ 1,2,3,4,5 };
		auto r_iter = vei->rbegin();
		for (auto i = vei->crbegin(); i != vei->crend(); ++i) {
			cout << *i << endl;//5 4 3 2 1
		}
	}

	//�㷨����������
	void test4() {
		//1. ���������
		//ֻ������д������ɨ�裬ֻ�ܵ���
		// ��find accumulate istream_iterator
		//  ����֧�� == ��!=��++��-> �����

		//2. ���������
		//ֻд������������ɨ�裬ֻ�ܵ���
		// ��ostream_iterator copy�ĵ��������� 
		//  ����֧�� * ��++��  �����

		//3. ǰ������� 
		//�ɶ�д�����ɨ�裬ֻ�ܵ���
		// ���㷨replaceҪ��ǰ���������forward_list�ĵ�����

		//4. ˫�������
		//�ɶ�д�����ɨ�裬�ɵ����ݼ�
		// ֧��ǰ�õ������Ĳ�������֧�� --
		// ��reverseҪ��˫�������

		//5. ������ʵ�����
		//�ɶ�д�����ɨ�裬֧��ȫ������������
		//֧�� < ��<= ��>�� >= += -= 
		//�±�������������������ϵļ���������- ,�õ��������ľ���
	}
};

//����ָ��
class tsetptr {
public:
	//shared_ptr������ָ��ָ��ͬһ������
	void testshared_ptr() {
		//init 
		//way1 shared_ptr���в���
		auto sp1 = std::make_shared<int>(5);
		//way2
		int* p1 = new int[0];
		shared_ptr<int> sp2(p1);
		//way3
		shared_ptr<int> sp3(new int[2]);
		//way4 �������ü���
		shared_ptr<int> sp4(sp3);

		//Ϊ�˱�������������ָ���ʼ����ָ��ɾ��֮��
		//����ָ������޷��ͷţ������ڴ�й¶����Դ����
		//�ڳ�ʼ��ʱ��ʹ��ɾ������������delete����ɶ�ָ������ͷŵĲ���
		int i = 9;
		shared_ptr<int> sp5(&i, [](int* p) { delete p; });

		//deal
		//��ȡԭָ��
		int* p2 = sp1.get();
		auto num = sp4.use_count();//2
		{
			//1.��Ҫ��һ����ָ���ʼ����� shared_ptr  
			{
				int* p1 = new int[2];

				shared_ptr<int> sp6(p1);
				shared_ptr<int> sp7(p1);
			}

			//2.��Ҫ����ɾ�� shared_ptr ���������ָ��
			{
				testDemo* tmp = new testDemo(1);
				shared_ptr<testDemo> sp6(tmp);
				long num1 = sp6.use_count();//1
				delete   tmp;
				long num2 = sp6.use_count();//1
				sp6 = nullptr;//error
			}
			//3 ��������ָ��
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
		//unique_ptrӵ����ָ��Ķ���,��˲�֧����ͨ�Ŀ����͸�ֵ
		//unique_ptr<int> p3(p2);//error
		//p3 = p2;//error

		//release��p2�ÿգ������ر���Ķ���ָ��
		unique_ptr<int> p3(p2.release());//ok

		 //��ɾ�����ĳ�ʼ��
		auto testEnd = [](int* i) {delete i; };
		unique_ptr<int, decltype(testEnd)> p4(new int(3), testEnd);

		//�ͷ�p3ָ��Ķ���
		p3.reset();

		//��p3ָ��pi
		p3.reset(pi);


	}

	void testweak_ptr() {
		//weak_ptr��һ�ֲ�������ָ����������ڵ�����ָ��
		//ָ��һ����shared_ptr����Ķ���
		weak_ptr<int> wp1;

		shared_ptr<int> sp1;
		weak_ptr<int>wp2(sp1);
		weak_ptr<int> wp3;
		wp3 = wp2;

		{
			wp3.reset();
			//wp1��������shared_ptr������
			wp1.use_count();
			//��wp1.use_count()Ϊ0������true ,����Ϊfalse
			wp1.expired();
			//��expired()Ϊtrue������һ����shared_ptr,
			//����Ϊһ��ָ��wp1�����shared_ptr
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

	//�ļ�IO��
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
		std::bind(output1, 1, 2)(); // ��� : 1 2

		//ʹ��plcaeholders��Ϊռλ��������Ĭ�ϲ���˳��
		std::bind(output1, std::placeholders::_1, 2)(1); // ��� : 1 2
		std::bind(output1, 2, std::placeholders::_1)(1); // ��� : 2 1

		// error: ����ʱû�еڶ�������
		//std::bind(output, 2, std::placeholders::_2)(1);
		std::bind(output1, 2, std::placeholders::_2)(1, 2); // ��� : 2 2

		// ����ʱ�ĵ�һ���������̵���
		std::bind(output1, std::placeholders::_1,
			std::placeholders::_2)(1, 2); // ��� : 1 2
		std::bind(output1, std::placeholders::_2,
			std::placeholders::_1)(1, 2); // ��� : 2 1

		//ʹ��ref��cref�������ã�����Բ����Ŀ��� 
		int a = 1, b = 2;
		//����Ϊ&a ��const &b
		std::bind(output1, std::ref(a), std::cref(b))(); // ��� : 1 2
	}

	//����allocator��
	void test4() {
		//allocator���ڴ����������ʼ�����з��룬
		//�����˶���ʱ���˷�
		std::allocator<int> ai1;
		//������һ��δ������ڴ棬���Ա���3��int���Ͷ��� ,������ָ��
		int* pi1 = ai1.allocate(3);

		//��ָ�밴�������͹���һ�����󣬿���Ӳ�����Ϊ���ݸ��������
		auto end = pi1;
		ai1.construct(end++, 1);
		ai1.construct(end++, 2);
		ai1.construct(end, 3);
		//cout << *pi1 << endl;//1
		//cout << *(pi1 + 1) << endl;//2
		//cout << *(pi1 + 2) << endl;//2

		//��ָ��ָ��Ķ���ִ����������
		ai1.destroy(pi1);

		//�ͷ�ָ���ֵ�ַ��ʼ���ڴ棬����ڴ汣����3��int���Ͷ���
		//ָ�������allocate���ص�ָ�룬�ڶ��������ұ���ʹ���ʱ��Сһ��
		//�����ȶԴ��ڴ��е�ÿ���������destroy
		ai1.deallocate(pi1, 3);

		//���������в���
		vector<int> vi{ 0,1,2,3,4,5 };
		//std::allocator<int> ai2;
		int* pi2 = ai1.allocate(vi.size());
		//����������Χ֮���Ԫ�ؿ�����δ�����ԭʼ�ڴ���
		std::uninitialized_copy(vi.begin(), vi.end(), pi2);
		for (int i = 0; i < vi.size(); i++) {
			//cout << *(pi2+i) << endl;//0 1 2 3 4 5
		}


		//std::allocator<int> ai1;
		int* pi3 = ai1.allocate(3);
		//��������ָ���Ԫ�ؿ�ʼ������3��Ԫ�ص�δ�����ԭʼ�ڴ���
		std::uninitialized_copy_n(vi.begin(), 3, pi3);
		for (int i = 0; i < 3; i++) {
			cout << *(pi3 + i) << endl;//0 1 2  
		}

		int* pi4 = ai1.allocate(4);
		//�ڵ�����ָ����ԭʼ�ڴ淶Χ�ڴ������󣬶����Ϊ3�Ŀ���
		std::uninitialized_fill(pi4, pi4 + 4, 3);
		for (int i = 0; i < 4; i++) {
			cout << *(pi4 + i) << endl;//3 3 3 3  
		}

		int* pi5 = ai1.allocate(5);
		//�ӵ�����ָ����ڴ��ַ��ʼ������5��Ԫ�أ�ֵΪ2
		std::uninitialized_fill_n(pi5, 5, 2);
		for (int i = 0; i < 5; i++) {
			cout << *(pi5 + i) << endl;//2 2 2 2 2
		}
	}

	//����rand
	void test5() {

	}

	//����regex
	void test6() {

	}
}

//��ֵ����ֵʹ�ñ���ʵ��
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
		//��ȡ�����޶���&��&&���ֱ�ָ��this����ָ����ֵ����ֵ
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

		//����io�����������ַ�ʽ��һ������Ԫ�࣬һ����ȫ�ֺ�����ʽ
		 //cout<< ctest1 �ȼ��� cout << ctest1.str
		friend ostream& operator<<(ostream& os, ctest1& other) {
			os << other.str;
			return os;
		}
		friend istream& operator>>(istream& is, ctest1& other) {
			is >> other.str;
			return is;
		}

		//����ǰ�úͺ��������
	   //ǰ��
		ctest1& operator++() {
			str += "0";
			return *this;
		}

		//������������ؽ���һ�������int���͵��βΣ�
			//����ʱ��Ϊ�β��ṩһ��ֵΪ0��ʵ�� 
		ctest1& operator++(int) {
			str += "1";
			return *this;
		}

		//�����±������
		char operator[](int  i) {
			return str[i];
		}

		//���س�Ա���������
		const string& operator*() const {
			return  str;
		}
		//��ͷ��������ܸı��Ա������һ�������壬
		//�����Ըı��ͷ���ĸ������ȡ��Ա
		string& operator->() {
			return str;
		}

		//�������������
		string& operator()(string s) {
			str = s;
			cout << " ()" << endl;
			return s;
		}

		//����ת�������
		//������һ��ֻ��ִ��һ���û����������ת����
		//����ʽ���û����������ת�����ڱ�׼ ����ת��֮ǰ��֮��
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
		//ͨ���ؼ������ƣ���������ʽ����ת��
		//�������ʽ�������ж�������������ʽ��תΪ��ʽִ��
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
		//��α�����ֵ���ú����Ͷ���ֵ��ֵ
		//�������������޶���
		ctest1 s1("value"), s2("s2");
		auto n = (s1 + s2).find('a');//n=1,s1=values2

		auto n1 = s1++;//values21
		auto n2 = ++s1;//values210
		auto n3 = s1[2];
		auto n4 = s1("123");
	}

	void tset2() {
		ctest1 cs1(3.14);//double �Զ�תΪ int
		auto n = cs1 * 8; //cs1 �Զ�תΪ int

		ctest2 cs2(3.14);
		//auto n1 = cs2 * 2;//error
		auto n2 = static_cast<int>(cs2) + 3;
	}

	//��ֵ ��ֵ�󶨵������������
	template <typename T> void f1(T&& t) {}
	void test3() {
		//��һ�����
		int i = 0;
		int& i1 = i;
		f1(i);
		//����ֵ��Ϊ��ֵ���ã�ģ�����Ͳ���T�ƶ�Ϊ��ֵ��������int&
		// ���������������int&���͵���ֵ���� �� (int& && t)
		//�����˵ڶ����������Ӵ��������õ����ã��γ����۵�
		 //X& & / X& && / X&& & ���۵��� X&
		//X&& && �۵��� X&&
		f1(i1);// int& && 
	}
}

namespace testTemplate {
	//��ģ��
	template <typename T>
	class Blob {
	public:
		typedef T value_type;
		typedef typename vector<T>::size_type size_type;
		Blob() {}
		//Blob() :m_data(std::make_shared<vector<T>>()){}
		//initializer_list����C++11�ṩ��һ��ģ������
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

	//��Աģ��
	template<typename T>
	T& add(T& a, T& b) {
		return a + b;
	}

	//ָ����ʾģ��ʵ��
	template<typename T1, typename T2, typename T3>
	T1 sum(T2 t2, T3 t3) {
		return t2 + t3;
	}

	//β�÷�������
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
	//�ɱ����ģ�� 
	//��׼c++�涨��������ģ���βΰ�ֻ��Ϊ���͡�ָ�������
	template<typename... Args>
	void sum(Args ... args) {
		int num = sizeof...(args);
		cout << num << endl;
		//int arr[] = { (std::cout << args<<"",args)...};
		//�ɱ����ģ���ʹ�÷�ʽ�����֣��ݹ�չ���Ͳ�����չ��(c17֧��)

		//print(args...);

	}

	//ģ��������
	template<>//��<>ָ����Ϊԭģ������ģ������ṩʵ��
	int sum(string s1, string s2) {
		return s1.size() + s2.size();
	}


	void test1() {
		int i1 = 1;
		long i2 = 2;
		//����ʱָ��ģ������
		auto n1 = sum<long long int>(i1, i2);//long sum(long,long)

		//��������Ӧ�� �Ὣʵ����ʽת��Ϊģ������
		auto n2 = sum<int long long>(i1, i2);//int sum(long ,long)
	}

	void test2() {
		//����ָ��
		int (*pf1)(int& a, int& b) = sum;

		void  func(int(*)(int&, int&));
		void  func(int(*)(string&, string&));
		//func(sum);//error �ж�����غ��������б�ƥ��
	}

	void test3() {
		// ģ��ͷ�ģ�庯��ͬʱ����ʱ�����ȵ��÷�ģ��
		//sum(1, 2);//sum
		sum(1, 2, 3, 4);//4
	}
}

//���Զ��ؼ̳С���̳�
namespace testoverride {
	struct Base1
	{
		Base1() {
			cout << "Base1 ����" << endl;
		}

		Base1(int num) :m_num(num) {}

		Base1(Base1& b) {
			cout << "Base1 ��������" << endl;
			m_num = b.m_num;
		}

		Base1& operator=(Base1& b) {
			cout << "Base1 ������ֵ" << endl;
			m_num = b.m_num;
			return *this;
		}

		~Base1() {
			cout << "Base1 ����" << endl;
		}
	private:
		int m_num;
	};

	class A1 :public Base1 {
	public:
		A1() {
			cout << "A1 ����" << endl;
		}

		A1(int num) :m_num1(num) {}

		A1(A1& a) {
			m_num1 = a.m_num1;
			cout << "A1 ��������" << endl;
		}

		A1& operator=(A1& b) {
			cout << "A1 ������ֵ" << endl;
			m_num1 = b.m_num1;
			return *this;
		}

		~A1() {
			cout << "A1 ����" << endl;
		}
	private:
		int m_num1;
	};

	class B1 :public Base1 {
	public:
		B1() {
			cout << "B1 ����" << endl;
		}

		B1(int num) :b_num1(num) {}

		B1(B1& a) {
			b_num1 = a.b_num1;
			cout << "B1 ��������" << endl;
		}

		B1& operator=(B1& b) {
			cout << "B1 ������ֵ" << endl;
			b_num1 = b.b_num1;
			return *this;
		}

		~B1() {
			cout << "B1 ����" << endl;
		}
	private:
		int b_num1;

	};
}