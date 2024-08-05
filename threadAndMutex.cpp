#include "threadAndMutex.h"
void func() {
	std::cout << "�߳�ִ��" << std::endl;
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
	std::cout << "���̼߳���" << std::endl;
	obj->changeNum();
}
void childRecThread(ThreadAndMutex* obj) {
	std::lock_guard<std::recursive_mutex> locker(obj->rec_mutex);
	std::cout << "���̼߳���" << std::endl;
	obj->changeNum();
}
void ThreadAndMutex::recurMutex() {
	/*std::lock_guard<std::mutex> locker(m_mutex);
	ThreadAndMutex* obj = this;*/
	//!��childThread�͵�ǰ�����ж�ʹ��һ������lock_guard���Զ��������������ڵȶԷ���������������ݹ�����������ճ�����
	/*childThread(obj);
	childThread(obj);*/


	//ʹ��recursive_mutex�Ͳ���
	std::lock_guard<std::recursive_mutex> locker(rec_mutex);
	ThreadAndMutex* obj = this;
	childRecThread(obj);
	childRecThread(obj);
	//�߳��в���ʹ�õݹ���join��ȴ��߳���ɣ�����һֱ�ȴ�������ݹ�������������Ȩ��һֱ�ݹ��ջ�����
	/*std::thread t1(childRecThread, obj);
	std::thread t2(childRecThread, obj);
	t1.join();
	t2.join();*/
	
	std::cout << num << std::endl;
}
void ThreadAndMutex::changeNum() {
	num++;
}

//д����
void ThreadAndMutex::putData(int x) {
	std::cout << "putData����";
	std::unique_lock<std::mutex> locker(condiMutex);
	while (queue.size() == m_maxSize) {
		m_write.wait(locker);//д���ݼ���
	}
	//wait������һ��д�����ڶ��������ĺ���ʽ�жϣ�����true������,���Ϊfalse������
	/*m_write.wait(locker, [this]() {
		return queue.size() != m_maxSize;
	});*/
	std::cout << "д��ֵ=" << x << std::endl;
	queue.push_back(x);

	cvarMutex.notify_all();
	m_read.notify_one();//֪ͨ��ȡ���ݽ���
}
void ThreadAndMutex::readData() {
	std::unique_lock<std::mutex> locker(condiMutex);
	while (queue.empty()) {
		m_read.wait(locker);//�����ݼ���
	}
	int x = queue.front();
	queue.pop_front();
	std::cout << "��ȡֵ="<< x << std::endl;
	m_write.notify_one();//֪ͨд���ݽ���
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
//�첽�߳�,���Ժ��߳�ͨ�ţ������첽ִ������
void ThreadAndMutex::AsyncThread() {
	
	std::thread t(doSomething, std::ref(m_promise));
	t.detach();
	std::future<int> pr = m_promise.get_future();
	std::cout << "�߳�ִ������" << pr.get() << std::endl;
	std::cout << std::this_thread::get_id() << std::endl;

	//��package�����п��Բ���Ҫ����value������ֵ��������future��ȡ��ֵ
	std::packaged_task<int(int)> task([](int x) {
		std::cout << "package�߳�" << std::this_thread::get_id() << std::endl;
		return x += 100;
	});
	std::thread t2(std::ref(task), 100);
	std::future<int> f = task.get_future();
	std::cout << "package�߳���Ϣ" << f.get() << std::endl;
	t2.join();

}

//��������������������ʱ���������Ѽ���ִ��
void ThreadAndMutex::ActionMutex() {
	std::cout << "actionMutex ����";
	std::unique_lock<std::mutex> lock(m_mutex);
	//�����Զ���ȡ�Ƿ�������������Ҫ�����߳�ʹ��notify_all��notify_one֪ͨ
	cvarMutex.wait(lock, [this] {return queue.size() > 0; });
	int endData = queue.front();
	std::cout << endData << std::endl;

}

//��Ϣ����
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