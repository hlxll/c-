#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <mutex>
#include <thread>
#include "controlSystem.h"
#include "windowAPi.h"

using namespace std;
//重载运算符
class customOperator {
private:
	int value;
public:
	//构造函数
	customOperator(int val) : value(val) {}
	//析构函数(对象被销毁时执行的清理和释放资源)
	~customOperator() {
		cout << "析构函数的执行，对象被销毁了" << endl;
	}
	//重载运算符 +
	customOperator operator+(const customOperator& other) {
		return customOperator(value + other.value);
	}
	int getValue() const {
		return value;
	}
};

class People
{
private:
	int ParentAge;
public:
	double age;
	string name;
	string griendFriend;
	double get(void);
	void set(double ag, string na, string fri);
	//函数重载
	void print(int age) {
		cout << "int：" << age << endl;
	}
	void print(string age) {
		cout << "str：" << age << endl;
	}
protected:
	int height;
};


double People::get(void) {
	return age;
};
void People::set(double ag, string na, string fri) {
	age = ag;
	name = na;
	griendFriend = fri;
};



class Man : public People {
public:
	double height;
	double weight;
	double getHei(void);
};

//抽象类（至少有一个纯虚函数的类,不能直接实例化，需要被继承并实现这个方法）
class Space
{
private:
	string name;
public:
	//纯虚函数
	virtual int getArea() {
		return 0;
	};
};
class ChildSpace : public Space {
public:
	//override标注重写的虚函数
	int getArea() override {
		return 1;
	};
};
class ChildTwoSpace : private Space {
public:
	int getArea() override {
		return 2;
	};
};

//文件读写
class FstreamFile
{
public:
	void openFileXie() {//创建并打开，用于写入数据
		// std::ofstream outputFile("demo.txt"); 
		std::ofstream outputFile;
		outputFile.open("demo.txt", ios::app);
		if (outputFile.is_open()) {
			outputFile << "Hello,word1!";
			const char* data = "hello, word2";
			outputFile.write(data, strlen(data));
			outputFile.put('A');
			outputFile.close();
		}

		std::ofstream outputFileBin;
		outputFileBin.open("two.bin", ios::trunc | ios::binary);
		if (outputFileBin.is_open()) {
			outputFileBin << "Hello,word1!";
			outputFileBin.put('A');
			const int size = 4;
			char name[] = "huanglin";
			outputFileBin.write(name, size);
			outputFileBin.close();
		}

		std::ofstream createFile;
		createFile.open("create.txt", ios::app);
		if (createFile.is_open()) {
			createFile.close();
			cout << "创建成功" << endl;
		}
		else {
			cout << "创建失败" << endl;
		}
	}
	void readFile() {//打开并读取文件,read通常读取二进制文件，txt文件使用getLine读取,getline主要用于读取string数据，char不合适
		std::ifstream inputFile;
		inputFile.open("demo.txt");//以二进制模式打开文件
		if (inputFile.is_open()) {
			std::string line;
			while (std::getline(inputFile, line))
			{
				cout << line << endl;
			}
			inputFile.close();
		}
		std::ifstream oneStrFile;
		//逐个单词读取
		oneStrFile.open("demo.txt");
		if (oneStrFile.is_open()) {
			std::string str;
			oneStrFile >> str;
			cout << str << endl;
			oneStrFile.close();
		}

		std::ifstream inputFileBin;
		inputFileBin.open("two.bin", std::ios::binary);
		if (inputFileBin.is_open()) {
			const int readSize = 2;//读取字节数超出就读取失败了
			char moreLine[readSize];
			inputFileBin.read(moreLine, readSize);
			if (inputFileBin) {
				cout << inputFileBin.gcount() << endl;
				cout << moreLine << endl;
				inputFileBin.close();
			}
			// const int readSize = 20;
			// char* buffer = new char[readSize];
			// inputFileBin.read(buffer, readSize);
			// if(inputFileBin){
			//     cout << inputFileBin.gcount() << endl;
			//     cout << buffer << endl;
			// }
		}
	}

};

//自定义异常
class MyException : public std::exception {
public:
	//explicit防止编译器进行隐式类型转换，强制要求显式调用构造函数
	explicit MyException(const char* message) : errorMessage(message) {}
	const char* what() const noexcept override {//noexcept表示函数不会抛出异常,override指示当前函数是覆盖基类的虚函数
		return errorMessage.c_str();
	}
private:
	std::string errorMessage;
};
//动态内存
class dynaicSave {
public:
	void createKong() {
		//new创建内存，返回地址
		int* num = new int;
		*num = 5;
		cout << *num << endl;
		int size = 5;
		int* arr = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = i + 1;
		};
		for (int i = 0; i < size; i++) {
			cout << arr[i] << endl;
		}

		//动态内存分配
		std::vector<int> vecArr = { 1,2,3,4,5 };
		vecArr.erase(vecArr.begin() + 2);//删除的第二位
		//动态内存分配创建的数组和普通的数组不同，
	}
};


//命名空间(组织代码，避免冲突)
namespace nameControl {
	void printf() {
		cout << "命名空间数据" << endl;
	}
};

//模板
template<typename T>
inline T templateFun(T a, T b) {
	return a + b;
};

template<class T>
class Stack {
public:
	void push();
};

template <class T>
void Stack<T>::push() {
	cout << "类的成员方法定义模板" << endl;
};

//注册信号
class callSet {
public:
	//监听进程的进度，这里的SIGINT是使用ctrl+c结束进程会触发
	void handleSigFun(int signal) {
		cout << "sigint信号：" << signal << endl;
	};
};

void threadFun() {
	cout << "多线程运行" << endl;
};
void threadFunVal(std::string value) {
	std::cout << value << std::endl;
};

//人员管理系统
void controlSystemFun() {
	ControlSystem obj;
	StreamSystem fileObj;
	int isSet = 1;
	while (isSet)
	{
		int inpType;
		cout << "**********0：显示所有人员********" << endl;
		cout << "**********1：添加人员************" << endl;
		cout << "**********2：删除人员************" << endl;
		cout << "**********3：修改人员************" << endl;
		cout << "**********10：退出***************" << endl;
		cout << "**********请输入下标*************" << endl;
		cin >> inpType;
		switch (inpType)
		{
		case 0:
			// obj.show();
			fileObj.show();
			break;
		case 1://添加
		{
			char name[20];
			string type;
			int age;
			cout << "请输入名称，性别，年龄，回车结束！" << endl;
			cin >> name;
			std::cin.ignore();//忽略剩余的换行符，不然会被下面的getline读取进去
			std::getline(cin, type);
			cin >> age;
			//obj.add(name, type, age);
			fileObj.add(name, type, age);
		}
		break;
		case 2://删除
		{
			cout << "请输入下标" << "";
			int index;
			cin >> index;
			// obj.delPeople(index);
			fileObj.delPeople(index);
		}
		break;
		case 3://修改
		{
			cout << "请输入修改人索引" << endl;
			int i;
			cin >> i;
			cout << "请输入新名称：" << endl;
			char str[20];
			cin >> str;
			obj.updatePeople(i, str);
			fileObj.updatePeople(i, str);
		};
		break;
		case 10://结束
			isSet = 0;
			system("exit");
			exit(1);
			break;
		default:
			cout << "无效的输入" << endl;
			break;
		}
	}
}

//vector容器
void vectorData() {
	std::vector<int> myVector;//空的整数向量
	std::vector<int> myVector2(5);//默认5个初始化整数的向量
	myVector.push_back(1);
	myVector.push_back(2);
	cout << "使用[]访问" << myVector[0] << endl;
	cout << "使用at访问" << myVector.at(1) << endl;
	cout << "数组大小" << myVector.size() << endl;
	for (std::vector<int>::iterator it = myVector.begin(); it != myVector.end(); ++it) {
		int element = *it;
		cout << element << endl;
	}
}
class SelfPreator {
public:
	bool operator()(int val1, int val2) const {
		return val1 > val2;
	}
};
//map和set容器
void mapData() {
	//每个键是唯一的，特定顺序排序
	std::map<int, std::string, SelfPreator> myMap;
	myMap.insert({ 1, "huanglin" });
	myMap.insert({ 2, "xulinlin" });
	myMap[3] = "laopo";
	myMap[2] = "laopo";//唯一的键，重复会覆盖
	cout << myMap[1] << endl;
	for (const auto& pair : myMap) {
		cout << pair.first << pair.second << endl;
	}

	//有序元素集合，默认排序规则，整数和浮点等，默认升序。对于自定义类型，可以重载该类型的比较运算符或提供自定义的比较函数
	std::set<int> mySet;
	mySet.insert(1);
	mySet.insert(10);
	mySet.insert(7);
	mySet.insert(10);
	for (const auto& pair : mySet) {
		cout << pair << endl;
	}
	cout << mySet.size() << endl;

	//对组
	pair<int, int> p1(12, 111);
	cout << p1.first << endl;
	cout << p1.second << endl;
	pair<int, int> p2 = make_pair(11, 12);
	cout << p2.first << endl;
	cout << p2.second << endl;
}
//指针
void xingData() {
	int arr[5] = { 1,2,3,4,0 };
	int* p = arr;
	int len = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < len; i++) {
		cout << *(p + i) << endl;
	}
}
//引用
void yinyong() {
	int age = 10;
	int& a = age;
	a = 20;

	cout << a << endl;
	cout << age << endl;
}
//Lambda表达式，创建匿名函数
// auto lambda1 = [](){
//     cout << "匿名函数" << endl;
// };
// int x =10;
// auto lambda2 = [x]() -> int{
//     cout << x << endl;
//     return 0;
// };

//this指针
class thisZhi {
private:
	int age;
public:
	void getAge() {
		cout << "年龄age=" << this->age << endl;
	}
	void setAge(int age) {
		this->age = age;
	}
	thisZhi& getData(int age) {
		this->age += age;
		return *this;
	}

};
void thisFun() {
	thisZhi p1;
	p1.setAge(10);
	p1.getAge();
	p1.getData(10).getData(10);
	p1.getAge();

}
class constFun {
public:
	int age = 10;
	mutable int num = 20;
	void setAge(int num) const {
		//this->age = num;//常函数不能修改成员变量
		this->num = num;//只能修改加了mutable修饰的成员变量
		cout << this->age << endl;
		cout << this->num << endl;
	}
	void getAge() {
		cout << this->age << endl;
	}
};
//运算符重载
class addPerson
{
public:
	int age;
	addPerson operator+(addPerson p1) {
		addPerson tamp;
		tamp.age = this->age + p1.age;
		return tamp;
	}
	void setAge(int num) {
		this->age = num;
	}
};
void textPerson() {
	Person<int> p1(10);
	p1.getPerson();
}
template <class T>
class PersonFriend
{
	//放最上面是全局函数，可以直接在类外直接访问,友元可以访问当前类私有成员
	friend void getPerson(PersonFriend& a) {
		cout << a.age << endl;
	}
public:
	PersonFriend(T a) {
		this->age = a;
	}
private:
	T age;
};
void ListData() {
	list<int> c1;
	c1.push_back(10);
	c1.push_back(2);
	c1.push_back(23);
	for (auto c : c1)
	{
		cout << c << endl;
	}
	c1.sort();
	for (auto c : c1)
	{
		cout << c << endl;
	}
}
void TestStack() {
	std::stack<int> stack_1;
	stack_1.push(1);
	stack_1.push(2);
	while (!stack_1.empty())
	{
		int top = stack_1.top();
		cout << top << endl;
		stack_1.pop();
	}
}
std::mutex mtx;
std::condition_variable processCv;
bool isDataReady = false;
void processData()
{
	std::this_thread::sleep_for(std::chrono::seconds(3)); // 模拟处理数据的耗时操作

	std::lock_guard<std::mutex> lock(mtx);
	isDataReady = true;
	processCv.notify_one(); // 通知等待的线程数据已准备好
}

//调用其他库的方法和笔记
void makeOutLibrary() {
	//线程需要直接使用静态函数，如果使用成员函数需要提供一个对象的实例调用成员函数
//创建的实例作为成员函数的参数，就像js的call将this指向改一下
//因为成员函数有一个隐藏的参数---this指针
 //DoubleThread moreT;
 //People PeopleAPi;
//   std::thread t1(&DoubleThread::threadFun, &moreT);//bind将成员函数包装为可调用对象，同时绑定所需的对象的指针
//   int age = 22;
//   std::thread t2(&DoubleThread::threadFunVal, &moreT, age);
//   //静态函数
//   string str = "多线程输出";//如果输出内容在线程中的函数中，输出有错误
//   std::thread t3(threadFunVal, str);
//   // join方法：主线程等待子线程执行完成
//   t1.join();
//   t2.join();
//   t3.join();

   //条件变量
   //std::cout << "Main thread started." << std::endl;
   //std::thread dataProcessingThread(processData);
   //{
   //	std::unique_lock<std::mutex> lock(mtx);
   //	// 在条件变量上等待，直到数据准备好（isDataReady为true）
   //	processCv.wait(lock, []() { return isDataReady; });
   //}
   //std::cout << "Main thread resumed." << std::endl;
   //dataProcessingThread.join();
   //std::cout << "Main thread finished." << std::endl;

  // callSet call1;
  //注册信号处理函数
  // std::signal(SIGINT, call1.handleSigFun);


  // 宏定义
  // cout << "预处理定义的宏常量："<< PI << endl;
  // int a = 10;
  // int b = 20;
  // cout << "预处理，带参数的宏:"<<MAXNUM(a, b)<<endl;
  // cout << "C++自定义的预定义宏："<< __DATE__ << endl;//C++自带的预定义宏

  //条件语句
  // #define DEBUG
  // //条件宏
  // #ifdef DEBUG
  //     std::cerr << "Tract: inside main function" << endl;
  // #endif

  // #if 0
  //     std::cerr << "不会输出的内容" << endl;
  // #endif
  //     std::cerr << "会输出的内容" << endl;

  // if (true)
  // {
  //     cout << "正确清空" << endl;
  // }
  // switch (1)
  // {
  // case 1:
  //     cout << "switch 1" << endl;
  //     break;
  // default:
  //     cout << "switch 2" << endl;
  //     break;
  // }
  //循环语句
  // int i = 0;
  // while (i<10)
  // {
  //     i++;
  //     cout << "循环i=" << i << endl;
  // }


  //自定义异常方法
  // try{
  //     throw MyException("this is a error");
  // }catch(const MyException& e){
  //     std::cout << e.what() << endl;
  // }


  // dynaicSave dynaicNew;
  // dynaicNew.createKong();

  // nameControl::printf();

  //模板
  // int temRes = templateFun(1, 2);
  // cout << temRes << endl;
  // string str1 = "1.2";
  // string str2 = "2.2";
  // string temResStr = templateFun(str1, str2);
  // cout << temResStr << endl;



  // string name = "huanglin";
  // string& str = name;//引用 huanglin
  // string* url = &name;//指针 地址
  // string value = *url;//指针找值 huanglin
  // cout << str << "\0";
  // cout << value << "\0";
  // cout << url << endl;
  // char list[] = {'a', 'b', 'c', 'd'};
  // for(int i=0;i<4; i++){
  //     cout << list[i] << "\0";
  // }
  // int num = 0;
  // do
  // {
  //     num++;
  //     cout << num << '\0';
  // } while (num<10);

  // time_t now  = time(0);
  // cout << now << endl;
  // char* dt = ctime(&now);
  // cout << dt << endl;

  // cout << "数据结构" << endl;
  // struct Doucter
  // {
  //     string position;
  // };
  // struct Peoples
  // {
  //     char name[20];
  //     int age;
  //     string greenFriend;
  //     Doucter doucter;
  // };
  // Peoples people1;
  // strcpy(people1.name, "huanglin");
  // people1.greenFriend = "xulinlin";
  // people1.age = 23;
  // people1.doucter.position = "江西上饶";
  // cout << people1.doucter.position << endl;

  // std::ostringstream oss;
  // oss << "地址是：" << people1.doucter.position << endl;
  // std::cout << oss.str();
  // cout << "姓名 " << people1.name << endl;
  // cout << "对象 " << people1.greenFriend << endl;

  // cout << "定义类：people" << endl;

  // People people2;
  // people2.age = 24;
  // double peopleAge = people2.get();
  // cout << "类的age数据:" << peopleAge << endl;
  // people2.set(23.2, "huanglin", "xulinlin");
  // peopleAge = people2.get();
  // cout << "类的age数据:" << peopleAge << endl;
  // people2.print(12);
  // string c = "hello_huanglin";
  // people2.print(c);


  // customOperator num1(5);
  // customOperator num2(10);
  // customOperator result = num1 + num2;
  // cout << result.getValue() << endl;

  // Man people3;
  // people3.name = "huang";
  // people3.height = 33;
  // cout << people3.name << endl;
  // cout << people3.height << endl;

  // ChildSpace childS1;
  // int childNum = childS1.getArea();
  // cout <<  childNum << endl;
  // cin >> name;

  //使用基类指针指向派生类对象，调用虚函数，这里的对象不同，在运行时就会调用不同的实现方法
  // Space* obj = new ChildSpace();
  // int age = obj->getArea();
  // cout << age << endl;
  // obj = new ChildTwoSpace();
  // int age2 = obj->getArea();
  // cout << age2 << endl;
  // delete obj;
}

class LearnMain {
public:
	void learnStart() {
		void makeOutLibrary();
	}
};