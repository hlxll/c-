#include "threadAndMutex.h"

void ThreadAndMutex::createThread() {
	std::thread t1([]() {
		std::cout << "单个线程执行" << std::endl;
	});
	t1.join();
}