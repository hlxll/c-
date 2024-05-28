#include "learnCpp.h"
void learnCpp::LongNum() {
	long long num1 = 123123123LL;
	//等价,默认有符号的，LL后缀和ll后缀一样
	signed long long num2 = 123123123LL;
	long long int num3 = 123123123LL;
	std::cout << num1 << std::endl;
	std::cout << num2 << std::endl;

	//无符号的,没有符号位正负，但是数字位数不变
	unsigned long long num4 = 123123123LL;
	//最大长长整数
	unsigned long long num5 = LLONG_MAX;
	long long num6 = LLONG_MIN;//最小长长整数,
	std::cout << std::to_string(num4 == num1) << std::endl;//1
	std::cout << num5 << std::endl;
	std::cout << num6 << std::endl;

	//不同数字相加，有隐式转换，看谁等级高
	//long long int > int     long long int > int64.等级低的向高的转换，有符号的向无符号的转换

	//快速初始化的参数
	auto name = std::string("huanglin");
	std::cout << name << std::endl;
	size_t len = name.size();
	std::cout << len << std::endl;
}
void learnCpp::Test() {
	std::cout << "list 学习" << std::endl;
	std::list<int> listArr;
	listArr.push_back(1);
	listArr.push_front(2);
	listArr.push_back(3);
	listArr.push_back(4);
	auto next = ++listArr.begin();
	next = ++next;
	listArr.insert(next, 8);
	for (auto i = listArr.begin(); i != listArr.end(); i++)
	{
		std::cout << *i << std::endl;
	}
	listArr.clear();


	std::stack<int> stacks;
	stacks.push(1);
	stacks.push(2);
	stacks.pop();
	std::cout << stacks.top() << std::endl;
}
void learnCpp::Change() {
	std::cout << "虚拟函数" << std::endl;
}