#pragma once
#include <thread>
#include <iostream>
#include <functional>
#include <mutex>
#include <future>
#include <condition_variable>
#include <queue>
#include <string>
#include <cstring>
class ThreadAndMutex
{
public:
	void createThread();
	void recurMutex();
	void changeNum();
	void putData(int i);
	void readData();
	void readWriteData();
	void AsyncThread();
	void ActionMutex();

	//消息队列
	void PushMsgQueue(std::string param);
	void WaitMsgQueue();
	void readMsgQueue() {
		ThreadAndMutex threadMsg;
		auto producer = [&threadMsg]() {
			for (int i = 0; i < 10; i++) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				std::cout << "production" << i << std::endl;
				threadMsg.PushMsgQueue(std::to_string(i));
			}
		};
		auto consumer = [&threadMsg]() {
			for (int i = 0; i < 10; i++) {
				threadMsg.WaitMsgQueue();
			}
		};
		std::thread t1(producer);
		std::thread t2(consumer);

		t1.join();
		t2.join();
	}
	std::mutex m_mutex;
	std::recursive_mutex rec_mutex;

	std::list<int> queue;
	std::condition_variable m_write;
	std::condition_variable m_read;
	std::mutex condiMutex;
	std::promise<int> m_promise;
	std::condition_variable cvarMutex;

	//消息队列
	std::queue<std::string> queueMsg;
	std::mutex queMsgLock;
	std::condition_variable queueVariable;
private:
	int num = 0;
	int m_maxSize = 5;

};

