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
	//���ٳ�ʼ��
	learnCpp(std::string str) :name(str) {}
	//long long���͵�����,��c++98���ĸı���Ƕ������,����64λ
	void LongNum();
	
	virtual void Test() final;//finalֻ�������麯��
	virtual void Change();//���⺯��������һ��Ҫ�������ڽӿ��вſ��Բ�����
};
//class Child final:public learnCpp {
//public:
//	//void Test() final;//���ܱ���д����Ϊ�麯��������final
//	void Change() override;//override������ȷҪ��д������麯�����ͻ��ຯ������ͬǩ��
//};
