#include "doubleThread.h"
#include <iostream>
#include <mutex>
#include <msxml.h>
#include <condition_variable>
#include <thread>
std::mutex mtx1;
void DoubleThread::threadFun() {
	//信号量，设置计数量，超过的线程需要等待
	mtx1.lock();//加锁
	std::cout << "多线程运行" << std::endl;
	mtx1.unlock();//解锁
}
void DoubleThread::threadFunVal(int value) {
	std::cout << "多线程运行:参数" << value << std::endl;
}


//锁和条件变量
//void DoubleThread::variableLock() {
//	//用于线程间的条件变量同步，允许一个或多个线程等待条件发生，再唤醒
//	std::condition_variable cv;
//	std::unique_lock<std::mutex> ulock(mtx);
//	bool condition = false;
//	cv.wait(ulock, [&condition] {return condition; });
//
//	Sleep(1);
//
//	std::lock_guard<std::mutex> lock(mtx);
//	condition = true;
//	cv.notify_one();//唤醒一个等待的线程
//}