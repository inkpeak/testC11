#include <windows.h>
#include"DP07ThreadPool.cpp"


//1、Immutable Object模式（不可变对象）
//
//通过将对象变为只读的形式来保证线程安全，是比较好的无锁实现。 
//无非就是将所有可以变的变量的setter全部对访问者关闭，
// 并且防止有可修改引用泄露出去。
// 

//2、Guarded Suspension模式（保护性暂挂）
//
//有时候一些线程在执行的时候需要满足一些条件，倘若没有满足的话便无法执行下去，
// 这个时候我们通过暂挂（跑一跑空循环之类的）来让线程暂时挂起，
// 等待条件满足的时候再继续执行。在后面的Promise模式中，
// 比如在多线程中写得很多的Future就经常会用到，结果还没算出来，
// 那就不好意思，请等一会儿再执行咯。


//3、Two - phase Termination模式（两阶段终止）
//
//在终止线程的时候我们或许会丢掉很多东西，比如一些状态，
// 或者还有一些必要执行的东西还未执行完。倘若直接中断线程的话会引起很多问题，
// 所以在终止线程之前我们或许需要等待这些操作。
//例如在Java的标准库中，线程池就会等待目前仍在执行的线程，
// 执行完全之后就会完全关闭线程池。后面的Thread Pool模式中也会用到。


//4、Promise模式（承诺）
//
//Promise模式帮我们不需要等待耗时的求值操作，而是拿一个凭证。
// 我们可以先去做些别的，最后再回来取值。在Java中的Future就是用的这个思想。


//5、Producer - Consumer模式（生产者 - 消费者）
//
//在多线程编程中经常有一个生成数据以及一个消费数据的两个模块，
// 这两者的速率通常是不相等的，所以为了避免等待，该模式中引入了通道的概念。
//生产者将产生的数据放入一个队列，消费者则从队列中拿数据。
// 并且生产者与消费者是完全解耦的。 改进版本中也有用多个通道进行消费，
// 减少锁竞争，再者也可以用工作窃取的方式进行负载均衡。


void test05() {

}

//6、Active Object模式（主动对象）
//
//该模式将方法的调用与执行解耦。使用者通过同步的方式调用，
// 而后台以异步的方式执行。调用与执行分开在不同线程以提高并发性，
// 当然也可以用到Promise模式来得到结果。

//7、Thread Pool模式（线程池）
//
//这个模式就是为减少开启与关闭线程带来的开销。但是在使用的时候还是有
// 很多需要注意的地方，例如死锁、线程泄漏之类的问题，导致可用线程越来越少。 
//Java中直接用各种Executer，已经是很好的线程池了，也没有必要自己再实现一个。

//线程池设计模式
void test07() {
	try {
		std1::threadpool executor{ 4 };
		A a;
		//创建任务
		std::future<void> ff = executor.commit(fun1, 0);
		std::future<int> fg = executor.commit(gfun{}, 0);
		std::future<int> gg = executor.commit(a.Afun, 9999); //IDE提示错误,但可以编译运行
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

		ff.get(); //调用.get()获取返回值会等待线程执行完,获取返回值
		std::cout << fg.get() << "  " << fh.get().c_str() << "  "
			<< std::this_thread::get_id() << std::endl;

		std::cout << " =======  sleep ========= " << std::this_thread::get_id()
			<< std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));

		std::cout << " =======  fun1,55 ========= " << std::this_thread::get_id()
			<< std::endl;
		executor.commit(fun1, 55).get();    //调用.get()获取返回值会等待线程执行完

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


//8、Thread Specific Storage模式（线程特有存储） 
//通过每个线程独立储存数据来避免竞争。也是一种很好的无锁线程安全实现方式，
// 但是要注意内存泄漏，当线程销毁之后，保证数据也能够被及时销毁。 
//在Java当中直接使用ThreadLocal来应用该模式。


//9、Serial Thread Confinement模式（串行线程封闭模式）
//
//并发任务涉及到非线程安全对象时我们有时候又不希望使用锁，
// 那我们就可以使用该模式. 由于每次只有一个线程去访问该非安全对象，所以无需
// 担心线程不安全.其本质是将锁替代为开销更小的锁。（其实可以看做行为队列）


//10、Master - Slave模式（主仆）
//
//将任务拆解为更小的任务，小任务或许还能拆解成更小的任务，然后这些任务
// 交给不同的工作线程进行执行。 最后将这些任务进行合并，以达成完成所有任务
// 的目的。在工作线程中我们需要通过负载均衡以及工作窃取来达成最高效率。
// 当然该模式也可以用来做可靠性设计，子任务中只取一个正确完成的结果，
// 只需要确保所有子任务中有一个任务完成就可以了。 在停止任务的时候
// 我们也需要用到两阶段停止的思想，将子任务执行完之后自动停止。
// 
//11、Pipeline模式（流水线）
//
//在执行任务的时候，我们通常可以将任务分解成不同的阶段，在一些阶段当中
// 或许只有一个线程参与，而在另一些阶段中则有多个线程进行参与。
// 我们可以通过配置文件的方式来配置我们的自定义流水线。 需要注意的是，
// 流水线由于独立出很多资源，所以一定会有额外的开销，所以要注意管线的深度，
// 保证不要得不偿失.在始终只有一个线程参与的情况下，
// 也可以将Pipeline看做是Serial Thread Confinement模式。
// 
//12、Half - sync / Half - async模式（半同步 / 半异步） 
// 
//在多线程编程当中我们会发现，同步模式易于理解，而异步模式对IO更加高效。 
//所以引入这一模式，将模块分成三层，同步层、中间层、异步层，同步层
// 进行一些同步编写，而异步层则进行IO操作，操作完成后将数据放入中间层，
// 而同步层从中间层取得数据。 需要注意同步层的高级任务，例如数据库、网络任务
// 执行过慢的时候考虑使用非阻塞IO。


int main() {
	test07();

}