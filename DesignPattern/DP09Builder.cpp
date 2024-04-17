#include"heads.h"

/*
* ������ģʽ
* ���󴴽���ģʽ֮һ���������ظ��϶���Ĵ�������.��һ�����Ӷ���Ĺ���
* �����ı�ʾ���룬ʹͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ
* 
* ����������: Ϊ������Ʒ�������֣�ͳһ����ӿ�
* ���彨�����ࣺ����ʵ�ֳ������߸��������Ľӿ�
* ����ѡ�������Ʒ�ࣺΪ��Ʒ�ṩͳһ�ӿ�
* �����Ʒ��:ʵ�ֳ����Ʒ��Ľӿڡ�
* ����Ҫ��ָ���ࣺ�����ź͵��ȸ��Ӷ���ĸ����������
*/


//�������ĳ������
class PersonBuilder
{
public:
	virtual void buildHead() {}
	virtual void buildBody() {}
	virtual void buildLeg() {}
	virtual void buildFoot() {}
};

//�������ľ���ʵ����
class PersonThinBuilder :PersonBuilder
{
	void buildHead() {
		std::cout << "thin" << std::endl;
	}
	void buildBody() {}
	void buildLeg() {}
	void buildFoot() {}
};

//�����û����࣬��������ʲô����
class Director
{
	PersonBuilder pb;
public:
	Director(PersonBuilder p) :pb(p) {}

	void create() {
		pb.buildHead();
		pb.buildBody();
		pb.buildLeg();
		pb.buildFoot();
	}
};