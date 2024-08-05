#include "threadAndMutex.h"
void func() {
	std::cout << "线程执行" << std::endl;
}
void ThreadAndMutex::createThread() {
	/*std::thread t1(std::bind(&ThreadAndMutex::changeNum, this));
	t1.join();
	std::thread t2(func);
	t2.join();*/

	for (size_t i = 0; i < 10; i++)
	{
		std::mutex m;
		m.lock();
		std::thread t1(std::bind(&ThreadAndMutex::changeNum, this));
		t1.join();
		m.unlock();
	}
	std::cout << num << std::endl;
}

void childThread(ThreadAndMutex* obj){
	std::lock_guard<std::mutex> locker(obj->m_mutex);
	std::cout << "子线程加锁" << std::endl;
	obj->changeNum();
}
void childRecThread(ThreadAndMutex* obj) {
	std::lock_guard<std::recursive_mutex> locker(obj->rec_mutex);
	std::cout << "子线程加锁" << std::endl;
	obj->changeNum();
}
void ThreadAndMutex::recurMutex() {
	/*std::lock_guard<std::mutex> locker(m_mutex);
	ThreadAndMutex* obj = this;*/
	//!在childThread和当前函数中都使用一个锁，lock_guard是自动加锁解锁，都在等对方解锁，所以这里递归调用两个，照成死锁
	/*childThread(obj);
	childThread(obj);*/


	//使用recursive_mutex就不会
	std::lock_guard<std::recursive_mutex> locker(rec_mutex);
	ThreadAndMutex* obj = this;
	childRecThread(obj);
	childRecThread(obj);
	//线程中不能使用递归锁join会等待线程完成，导致一直等待。如果递归请求锁的所有权，一直递归会栈溢出。
	/*std::thread t1(childRecThread, obj);
	std::thread t2(childRecThread, obj);
	t1.join();
	t2.join();*/
	
	std::cout << num << std::endl;
}
void ThreadAndMutex::changeNum() {
	num++;
}

//写数据
void ThreadAndMutex::putData(int x) {
	std::cout << "putData函数";
	std::unique_lock<std::mutex> locker(condiMutex);
	while (queue.size() == m_maxSize) {
		m_write.wait(locker);//写数据加锁
	}
	//wait的另外一种写法，第二个参数的函数式判断，返回true不阻塞,如果为false阻塞。
	/*m_write.wait(locker, [this]() {
		return queue.size() != m_maxSize;
	});*/
	std::cout << "写入值=" << x << std::endl;
	queue.push_back(x);

	cvarMutex.notify_all();
	m_read.notify_one();//通知读取数据解锁
}
void ThreadAndMutex::readData() {
	std::unique_lock<std::mutex> locker(condiMutex);
	while (queue.empty()) {
		m_read.wait(locker);//读数据加锁
	}
	int x = queue.front();
	queue.pop_front();
	std::cout << "读取值="<< x << std::endl;
	m_write.notify_one();//通知写数据解锁
}
void ThreadAndMutex::readWriteData() {
	std::thread t1[8];
	std::thread t2[8];
	for (size_t i = 0; i < 8; i++)
	{
		t1[i] = std::thread(std::bind(&ThreadAndMutex::putData, this, i));
		t2[i] = std::thread(std::bind(&ThreadAndMutex::readData, this));
	}
	for (size_t i = 0; i < 8; i++)
	{
		t1[i].join();
		t2[i].join();
	}
}


void doSomething(std::promise<int> &p){
	int result = 4;
	p.set_value(result);
	std::cout << std::this_thread::get_id() << std::endl;

}
//异步线程,可以和线程通信，还是异步执行任务。
void ThreadAndMutex::AsyncThread() {
	
	std::thread t(doSomething, std::ref(m_promise));
	t.detach();
	std::future<int> pr = m_promise.get_future();
	std::cout << "线程执行内容" << pr.get() << std::endl;
	std::cout << std::this_thread::get_id() << std::endl;

	//在package方法中可以不需要设置value，返回值就是外面future获取的值
	std::packaged_task<int(int)> task([](int x) {
		std::cout << "package线程" << std::this_thread::get_id() << std::endl;
		return x += 100;
	});
	std::thread t2(std::ref(task), 100);
	std::future<int> f = task.get_future();
	std::cout << "package线程信息" << f.get() << std::endl;
	t2.join();

}

//条件变量，在条件满足时被继续唤醒继续执行
void ThreadAndMutex::ActionMutex() {
	std::cout << "actionMutex 函数";
	std::unique_lock<std::mutex> lock(m_mutex);
	//这种自动获取是否阻塞，还是需要其他线程使用notify_all或notify_one通知
	cvarMutex.wait(lock, [this] {return queue.size() > 0; });
	int endData = queue.front();
	std::cout << endData << std::endl;

}

//消息队列
void ThreadAndMutex::PushMsgQueue(std::string param) {
	std::unique_lock<std::mutex> lock(queMsgLock);
	queueMsg.push(param);
	queueVariable.notify_all();
}
void ThreadAndMutex::WaitMsgQueue() {
	std::unique_lock<std::mutex> lock(queMsgLock);
	queueVariable.wait(lock, [this] {return queueMsg.size() > 0; });
	std::string param = queueMsg.front();
	std::cout << param << std::endl;
	queueMsg.pop();
}