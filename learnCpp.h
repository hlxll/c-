#pragma once
#include <string>
#include <iostream>
#include <list>
#include <stack>
using namespace std;
class learnCpp
{
protected:
	std::string name;
public:
	//快速初始化
	learnCpp(std::string str) :name(str) {}
	//long long类型的数字,比c++98最大的改变就是多了这个,至少64位
	void LongNum();
	
	virtual void Test() final;//final只能修饰虚函数
	virtual void Change();//虚拟函数在类中一定要声明，在接口中才可以不声明
};
//class Child final:public learnCpp {
//public:
//	//void Test() final;//不能被重写，因为虚函数定义了final
//	void Change() override;//override表面明确要重写基类的虚函数，和基类函数有相同签名
//};
