#include "doubleThread.h"
#include <iostream>
#include <mutex>
#include <msxml.h>
#include <condition_variable>
#include <thread>
std::mutex mtx1;
void DoubleThread::threadFun() {
	//�ź��������ü��������������߳���Ҫ�ȴ�
	mtx1.lock();//����
	std::cout << "���߳�����" << std::endl;
	mtx1.unlock();//����
}
void DoubleThread::threadFunVal(int value) {
	std::cout << "���߳�����:����" << value << std::endl;
}


//������������
//void DoubleThread::variableLock() {
//	//�����̼߳����������ͬ��������һ�������̵߳ȴ������������ٻ���
//	std::condition_variable cv;
//	std::unique_lock<std::mutex> ulock(mtx);
//	bool condition = false;
//	cv.wait(ulock, [&condition] {return condition; });
//
//	Sleep(1);
//
//	std::lock_guard<std::mutex> lock(mtx);
//	condition = true;
//	cv.notify_one();//����һ���ȴ����߳�
//}