#pragma once
class DoubleThread {
public:
	bool condition = false;
	void threadFun();
	void threadFunVal(int value);
	void variableLock();
};