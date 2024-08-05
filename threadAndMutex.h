#pragma once
#include <thread>
#include <iostream>
#include <functional>
#include <mutex>
#include <future>
#include <condition_variable>
#include <queue>
#include <string>
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

