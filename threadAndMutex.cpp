#include "threadAndMutex.h"

void ThreadAndMutex::createThread() {
	std::thread t1([]() {
		std::cout << "�����߳�ִ��" << std::endl;
	});
	t1.join();
}