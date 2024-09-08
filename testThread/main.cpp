#include <windows.h>
#include"DP07ThreadPool.cpp"


//1��Immutable Objectģʽ�����ɱ����
//
//ͨ���������Ϊֻ������ʽ����֤�̰߳�ȫ���ǱȽϺõ�����ʵ�֡� 
//�޷Ǿ��ǽ����п��Ա�ı�����setterȫ���Է����߹رգ�
// ���ҷ�ֹ�п��޸�����й¶��ȥ��
// 

//2��Guarded Suspensionģʽ���������ݹң�
//
//��ʱ��һЩ�߳���ִ�е�ʱ����Ҫ����һЩ����������û������Ļ����޷�ִ����ȥ��
// ���ʱ������ͨ���ݹң���һ�ܿ�ѭ��֮��ģ������߳���ʱ����
// �ȴ����������ʱ���ټ���ִ�С��ں����Promiseģʽ�У�
// �����ڶ��߳���д�úܶ��Future�;������õ��������û�������
// �ǾͲ�����˼�����һ�����ִ�п���


//3��Two - phase Terminationģʽ�����׶���ֹ��
//
//����ֹ�̵߳�ʱ�����ǻ���ᶪ���ܶණ��������һЩ״̬��
// ���߻���һЩ��Ҫִ�еĶ�����δִ���ꡣ����ֱ���ж��̵߳Ļ�������ܶ����⣬
// ��������ֹ�߳�֮ǰ���ǻ�����Ҫ�ȴ���Щ������
//������Java�ı�׼���У��̳߳ؾͻ�ȴ�Ŀǰ����ִ�е��̣߳�
// ִ����ȫ֮��ͻ���ȫ�ر��̳߳ء������Thread Poolģʽ��Ҳ���õ���


//4��Promiseģʽ����ŵ��
//
//Promiseģʽ�����ǲ���Ҫ�ȴ���ʱ����ֵ������������һ��ƾ֤��
// ���ǿ�����ȥ��Щ��ģ�����ٻ���ȡֵ����Java�е�Future�����õ����˼�롣


//5��Producer - Consumerģʽ�������� - �����ߣ�
//
//�ڶ��̱߳���о�����һ�����������Լ�һ���������ݵ�����ģ�飬
// �����ߵ�����ͨ���ǲ���ȵģ�����Ϊ�˱���ȴ�����ģʽ��������ͨ���ĸ��
//�����߽����������ݷ���һ�����У���������Ӷ����������ݡ�
// ����������������������ȫ����ġ� �Ľ��汾��Ҳ���ö��ͨ���������ѣ�
// ����������������Ҳ�����ù�����ȡ�ķ�ʽ���и��ؾ��⡣


void test05() {

}

//6��Active Objectģʽ����������
//
//��ģʽ�������ĵ�����ִ�н��ʹ����ͨ��ͬ���ķ�ʽ���ã�
// ����̨���첽�ķ�ʽִ�С�������ִ�зֿ��ڲ�ͬ�߳�����߲����ԣ�
// ��ȻҲ�����õ�Promiseģʽ���õ������

//7��Thread Poolģʽ���̳߳أ�
//
//���ģʽ����Ϊ���ٿ�����ر��̴߳����Ŀ�����������ʹ�õ�ʱ������
// �ܶ���Ҫע��ĵط��������������߳�й©֮������⣬���¿����߳�Խ��Խ�١� 
//Java��ֱ���ø���Executer���Ѿ��Ǻܺõ��̳߳��ˣ�Ҳû�б�Ҫ�Լ���ʵ��һ����

//�̳߳����ģʽ
void test07() {
	try {
		std1::threadpool executor{ 4 };
		A a;
		//��������
		std::future<void> ff = executor.commit(fun1, 0);
		std::future<int> fg = executor.commit(gfun{}, 0);
		std::future<int> gg = executor.commit(a.Afun, 9999); //IDE��ʾ����,�����Ա�������
		std::future<std::string> gh = executor.commit(A::Bfun, 9998, "mult args", 123);
		std::future<std::string> fh = executor.commit([]()->std::string { std::cout << "hello, fh !  " << std::this_thread::get_id() << std::endl; return "hello,fh ret !"; });

		std::cout << " =======  sleep ========= " << std::this_thread::get_id()
			<< std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(900));

		for (int i = 0; i < 5; i++) {
			executor.commit(fun1, i * 100);
		}
		std::cout << " =======  commit all ========= " << std::this_thread::get_id()
			<< " idlsize=" << executor.idlCount() << std::endl;

		std::cout << " =======  sleep ========= " << std::this_thread::get_id()
			<< std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));

		ff.get(); //����.get()��ȡ����ֵ��ȴ��߳�ִ����,��ȡ����ֵ
		std::cout << fg.get() << "  " << fh.get().c_str() << "  "
			<< std::this_thread::get_id() << std::endl;

		std::cout << " =======  sleep ========= " << std::this_thread::get_id()
			<< std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));

		std::cout << " =======  fun1,55 ========= " << std::this_thread::get_id()
			<< std::endl;
		executor.commit(fun1, 55).get();    //����.get()��ȡ����ֵ��ȴ��߳�ִ����

		std::cout << "end... " << std::this_thread::get_id()
			<< std::endl;


		/*	std::threadpool pool(4);
			std::vector< std::future<int> > results;

			for (int i = 0; i < 8; ++i) {
				results.emplace_back(
					pool.commit([i] {
						std::cout << "hello " << i << std::endl;
						std::this_thread::sleep_for(std::chrono::seconds(1));
						std::cout << "world " << i << std::endl;
						return i * i;
						})
				);
			}
			std::cout << " =======  commit all2 ========= " << std::this_thread::get_id() << std::endl;

			for (auto&& result : results)
				std::cout << result.get() << ' ';
			std::cout << std::endl;*/

	}
	catch (std::exception& e) {
		std::cout << "some unhappy happened...  " << std::this_thread::get_id() << e.what() << std::endl;
	}
}


//8��Thread Specific Storageģʽ���߳����д洢�� 
//ͨ��ÿ���̶߳����������������⾺����Ҳ��һ�ֺܺõ������̰߳�ȫʵ�ַ�ʽ��
// ����Ҫע���ڴ�й©�����߳�����֮�󣬱�֤����Ҳ�ܹ�����ʱ���١� 
//��Java����ֱ��ʹ��ThreadLocal��Ӧ�ø�ģʽ��


//9��Serial Thread Confinementģʽ�������̷߳��ģʽ��
//
//���������漰�����̰߳�ȫ����ʱ������ʱ���ֲ�ϣ��ʹ������
// �����ǾͿ���ʹ�ø�ģʽ. ����ÿ��ֻ��һ���߳�ȥ���ʸ÷ǰ�ȫ������������
// �����̲߳���ȫ.�䱾���ǽ������Ϊ������С����������ʵ���Կ�����Ϊ���У�


//10��Master - Slaveģʽ�����ͣ�
//
//��������Ϊ��С������С��������ܲ��ɸ�С������Ȼ����Щ����
// ������ͬ�Ĺ����߳̽���ִ�С� �����Щ������кϲ����Դ�������������
// ��Ŀ�ġ��ڹ����߳���������Ҫͨ�����ؾ����Լ�������ȡ��������Ч�ʡ�
// ��Ȼ��ģʽҲ�����������ɿ�����ƣ���������ֻȡһ����ȷ��ɵĽ����
// ֻ��Ҫȷ����������������һ��������ɾͿ����ˡ� ��ֹͣ�����ʱ��
// ����Ҳ��Ҫ�õ����׶�ֹͣ��˼�룬��������ִ����֮���Զ�ֹͣ��
// 
//11��Pipelineģʽ����ˮ�ߣ�
//
//��ִ�������ʱ������ͨ�����Խ�����ֽ�ɲ�ͬ�Ľ׶Σ���һЩ�׶ε���
// ����ֻ��һ���̲߳��룬������һЩ�׶������ж���߳̽��в��롣
// ���ǿ���ͨ�������ļ��ķ�ʽ���������ǵ��Զ�����ˮ�ߡ� ��Ҫע����ǣ�
// ��ˮ�����ڶ������ܶ���Դ������һ�����ж���Ŀ���������Ҫע����ߵ���ȣ�
// ��֤��Ҫ�ò���ʧ.��ʼ��ֻ��һ���̲߳��������£�
// Ҳ���Խ�Pipeline������Serial Thread Confinementģʽ��
// 
//12��Half - sync / Half - asyncģʽ����ͬ�� / ���첽�� 
// 
//�ڶ��̱߳�̵������ǻᷢ�֣�ͬ��ģʽ������⣬���첽ģʽ��IO���Ӹ�Ч�� 
//����������һģʽ����ģ��ֳ����㣬ͬ���㡢�м�㡢�첽�㣬ͬ����
// ����һЩͬ����д�����첽�������IO������������ɺ����ݷ����м�㣬
// ��ͬ������м��ȡ�����ݡ� ��Ҫע��ͬ����ĸ߼������������ݿ⡢��������
// ִ�й�����ʱ����ʹ�÷�����IO��


int main() {
	test07();

}