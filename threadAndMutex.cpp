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
}
//�첽�߳�
void ThreadAndMutex::AsyncThread() {
	std::thread t(doSomething, std::ref(m_promise));
	t.detach();
	std::future<int> pr = m_promise.get_future();
	std::cout << "�߳�ִ������" << pr.get() << std::endl;
}