#pragma once
#include <thread>
#include <iostream>
#include <functional>
#include <mutex>
#include <future>
#include <condition_variable>
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

	std::mutex m_mutex;
	std::recursive_mutex rec_mutex;

	std::list<int> queue;
	std::condition_variable m_write;
	std::condition_variable m_read;
	std::mutex condiMutex;
	std::promise<int> m_promise;
	std::condition_variable cvarMutex;
private:
	int num = 0;
	int m_maxSize = 5;

};

