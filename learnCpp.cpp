#include "learnCpp.h"
void learnCpp::LongNum() {
	long long num1 = 123123123LL;
	//�ȼ�,Ĭ���з��ŵģ�LL��׺��ll��׺һ��
	signed long long num2 = 123123123LL;
	long long int num3 = 123123123LL;
	std::cout << num1 << std::endl;
	std::cout << num2 << std::endl;

	//�޷��ŵ�,û�з���λ��������������λ������
	unsigned long long num4 = 123123123LL;
	//��󳤳�����
	unsigned long long num5 = LLONG_MAX;
	long long num6 = LLONG_MIN;//��С��������,
	std::cout << std::to_string(num4 == num1) << std::endl;//1
	std::cout << num5 << std::endl;
	std::cout << num6 << std::endl;

	//��ͬ������ӣ�����ʽת������˭�ȼ���
	//long long int > int     long long int > int64.�ȼ��͵���ߵ�ת�����з��ŵ����޷��ŵ�ת��

	//���ٳ�ʼ���Ĳ���
	auto name = std::string("huanglin");
	std::cout << name << std::endl;
	size_t len = name.size();
	std::cout << len << std::endl;
}
void learnCpp::Test() {
	std::cout << "list ѧϰ" << std::endl;
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
	std::cout << "���⺯��" << std::endl;
}