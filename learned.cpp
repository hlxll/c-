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
//���������
class customOperator {
private:
	int value;
public:
	//���캯��
	customOperator(int val) : value(val) {}
	//��������(��������ʱִ�е�������ͷ���Դ)
	~customOperator() {
		cout << "����������ִ�У�����������" << endl;
	}
	//��������� +
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
	//��������
	void print(int age) {
		cout << "int��" << age << endl;
	}
	void print(string age) {
		cout << "str��" << age << endl;
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

//�����ࣨ������һ�����麯������,����ֱ��ʵ��������Ҫ���̳в�ʵ�����������
class Space
{
private:
	string name;
public:
	//���麯��
	virtual int getArea() {
		return 0;
	};
};
class ChildSpace : public Space {
public:
	//override��ע��д���麯��
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

//�ļ���д
class FstreamFile
{
public:
	void openFileXie() {//�������򿪣�����д������
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
			cout << "�����ɹ�" << endl;
		}
		else {
			cout << "����ʧ��" << endl;
		}
	}
	void readFile() {//�򿪲���ȡ�ļ�,readͨ����ȡ�������ļ���txt�ļ�ʹ��getLine��ȡ,getline��Ҫ���ڶ�ȡstring���ݣ�char������
		std::ifstream inputFile;
		inputFile.open("demo.txt");//�Զ�����ģʽ���ļ�
		if (inputFile.is_open()) {
			std::string line;
			while (std::getline(inputFile, line))
			{
				cout << line << endl;
			}
			inputFile.close();
		}
		std::ifstream oneStrFile;
		//������ʶ�ȡ
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
			const int readSize = 2;//��ȡ�ֽ��������Ͷ�ȡʧ����
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

//�Զ����쳣
class MyException : public std::exception {
public:
	//explicit��ֹ������������ʽ����ת����ǿ��Ҫ����ʽ���ù��캯��
	explicit MyException(const char* message) : errorMessage(message) {}
	const char* what() const noexcept override {//noexcept��ʾ���������׳��쳣,overrideָʾ��ǰ�����Ǹ��ǻ�����麯��
		return errorMessage.c_str();
	}
private:
	std::string errorMessage;
};
//��̬�ڴ�
class dynaicSave {
public:
	void createKong() {
		//new�����ڴ棬���ص�ַ
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

		//��̬�ڴ����
		std::vector<int> vecArr = { 1,2,3,4,5 };
		vecArr.erase(vecArr.begin() + 2);//ɾ���ĵڶ�λ
		//��̬�ڴ���䴴�����������ͨ�����鲻ͬ��
	}
};


//�����ռ�(��֯���룬�����ͻ)
namespace nameControl {
	void printf() {
		cout << "�����ռ�����" << endl;
	}
};

//ģ��
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
	cout << "��ĳ�Ա��������ģ��" << endl;
};

//ע���ź�
class callSet {
public:
	//�������̵Ľ��ȣ������SIGINT��ʹ��ctrl+c�������̻ᴥ��
	void handleSigFun(int signal) {
		cout << "sigint�źţ�" << signal << endl;
	};
};

void threadFun() {
	cout << "���߳�����" << endl;
};
void threadFunVal(std::string value) {
	std::cout << value << std::endl;
};

//��Ա����ϵͳ
void controlSystemFun() {
	ControlSystem obj;
	StreamSystem fileObj;
	int isSet = 1;
	while (isSet)
	{
		int inpType;
		cout << "**********0����ʾ������Ա********" << endl;
		cout << "**********1�������Ա************" << endl;
		cout << "**********2��ɾ����Ա************" << endl;
		cout << "**********3���޸���Ա************" << endl;
		cout << "**********10���˳�***************" << endl;
		cout << "**********�������±�*************" << endl;
		cin >> inpType;
		switch (inpType)
		{
		case 0:
			// obj.show();
			fileObj.show();
			break;
		case 1://���
		{
			char name[20];
			string type;
			int age;
			cout << "���������ƣ��Ա����䣬�س�������" << endl;
			cin >> name;
			std::cin.ignore();//����ʣ��Ļ��з�����Ȼ�ᱻ�����getline��ȡ��ȥ
			std::getline(cin, type);
			cin >> age;
			//obj.add(name, type, age);
			fileObj.add(name, type, age);
		}
		break;
		case 2://ɾ��
		{
			cout << "�������±�" << "";
			int index;
			cin >> index;
			// obj.delPeople(index);
			fileObj.delPeople(index);
		}
		break;
		case 3://�޸�
		{
			cout << "�������޸�������" << endl;
			int i;
			cin >> i;
			cout << "�����������ƣ�" << endl;
			char str[20];
			cin >> str;
			obj.updatePeople(i, str);
			fileObj.updatePeople(i, str);
		};
		break;
		case 10://����
			isSet = 0;
			system("exit");
			exit(1);
			break;
		default:
			cout << "��Ч������" << endl;
			break;
		}
	}
}

//vector����
void vectorData() {
	std::vector<int> myVector;//�յ���������
	std::vector<int> myVector2(5);//Ĭ��5����ʼ������������
	myVector.push_back(1);
	myVector.push_back(2);
	cout << "ʹ��[]����" << myVector[0] << endl;
	cout << "ʹ��at����" << myVector.at(1) << endl;
	cout << "�����С" << myVector.size() << endl;
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
//map��set����
void mapData() {
	//ÿ������Ψһ�ģ��ض�˳������
	std::map<int, std::string, SelfPreator> myMap;
	myMap.insert({ 1, "huanglin" });
	myMap.insert({ 2, "xulinlin" });
	myMap[3] = "laopo";
	myMap[2] = "laopo";//Ψһ�ļ����ظ��Ḳ��
	cout << myMap[1] << endl;
	for (const auto& pair : myMap) {
		cout << pair.first << pair.second << endl;
	}

	//����Ԫ�ؼ��ϣ�Ĭ��������������͸���ȣ�Ĭ�����򡣶����Զ������ͣ��������ظ����͵ıȽ���������ṩ�Զ���ıȽϺ���
	std::set<int> mySet;
	mySet.insert(1);
	mySet.insert(10);
	mySet.insert(7);
	mySet.insert(10);
	for (const auto& pair : mySet) {
		cout << pair << endl;
	}
	cout << mySet.size() << endl;

	//����
	pair<int, int> p1(12, 111);
	cout << p1.first << endl;
	cout << p1.second << endl;
	pair<int, int> p2 = make_pair(11, 12);
	cout << p2.first << endl;
	cout << p2.second << endl;
}
//ָ��
void xingData() {
	int arr[5] = { 1,2,3,4,0 };
	int* p = arr;
	int len = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < len; i++) {
		cout << *(p + i) << endl;
	}
}
//����
void yinyong() {
	int age = 10;
	int& a = age;
	a = 20;

	cout << a << endl;
	cout << age << endl;
}
//Lambda���ʽ��������������
// auto lambda1 = [](){
//     cout << "��������" << endl;
// };
// int x =10;
// auto lambda2 = [x]() -> int{
//     cout << x << endl;
//     return 0;
// };

//thisָ��
class thisZhi {
private:
	int age;
public:
	void getAge() {
		cout << "����age=" << this->age << endl;
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
		//this->age = num;//�����������޸ĳ�Ա����
		this->num = num;//ֻ���޸ļ���mutable���εĳ�Ա����
		cout << this->age << endl;
		cout << this->num << endl;
	}
	void getAge() {
		cout << this->age << endl;
	}
};
//���������
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
	//����������ȫ�ֺ���������ֱ��������ֱ�ӷ���,��Ԫ���Է��ʵ�ǰ��˽�г�Ա
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
	std::this_thread::sleep_for(std::chrono::seconds(3)); // ģ�⴦�����ݵĺ�ʱ����

	std::lock_guard<std::mutex> lock(mtx);
	isDataReady = true;
	processCv.notify_one(); // ֪ͨ�ȴ����߳�������׼����
}

//����������ķ����ͱʼ�
void makeOutLibrary() {
	//�߳���Ҫֱ��ʹ�þ�̬���������ʹ�ó�Ա������Ҫ�ṩһ�������ʵ�����ó�Ա����
//������ʵ����Ϊ��Ա�����Ĳ���������js��call��thisָ���һ��
//��Ϊ��Ա������һ�����صĲ���---thisָ��
 //DoubleThread moreT;
 //People PeopleAPi;
//   std::thread t1(&DoubleThread::threadFun, &moreT);//bind����Ա������װΪ�ɵ��ö���ͬʱ������Ķ����ָ��
//   int age = 22;
//   std::thread t2(&DoubleThread::threadFunVal, &moreT, age);
//   //��̬����
//   string str = "���߳����";//�������������߳��еĺ����У�����д���
//   std::thread t3(threadFunVal, str);
//   // join���������̵߳ȴ����߳�ִ�����
//   t1.join();
//   t2.join();
//   t3.join();

   //��������
   //std::cout << "Main thread started." << std::endl;
   //std::thread dataProcessingThread(processData);
   //{
   //	std::unique_lock<std::mutex> lock(mtx);
   //	// �����������ϵȴ���ֱ������׼���ã�isDataReadyΪtrue��
   //	processCv.wait(lock, []() { return isDataReady; });
   //}
   //std::cout << "Main thread resumed." << std::endl;
   //dataProcessingThread.join();
   //std::cout << "Main thread finished." << std::endl;

  // callSet call1;
  //ע���źŴ�����
  // std::signal(SIGINT, call1.handleSigFun);


  // �궨��
  // cout << "Ԥ������ĺ곣����"<< PI << endl;
  // int a = 10;
  // int b = 20;
  // cout << "Ԥ�����������ĺ�:"<<MAXNUM(a, b)<<endl;
  // cout << "C++�Զ����Ԥ����꣺"<< __DATE__ << endl;//C++�Դ���Ԥ�����

  //�������
  // #define DEBUG
  // //������
  // #ifdef DEBUG
  //     std::cerr << "Tract: inside main function" << endl;
  // #endif

  // #if 0
  //     std::cerr << "�������������" << endl;
  // #endif
  //     std::cerr << "�����������" << endl;

  // if (true)
  // {
  //     cout << "��ȷ���" << endl;
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
  //ѭ�����
  // int i = 0;
  // while (i<10)
  // {
  //     i++;
  //     cout << "ѭ��i=" << i << endl;
  // }


  //�Զ����쳣����
  // try{
  //     throw MyException("this is a error");
  // }catch(const MyException& e){
  //     std::cout << e.what() << endl;
  // }


  // dynaicSave dynaicNew;
  // dynaicNew.createKong();

  // nameControl::printf();

  //ģ��
  // int temRes = templateFun(1, 2);
  // cout << temRes << endl;
  // string str1 = "1.2";
  // string str2 = "2.2";
  // string temResStr = templateFun(str1, str2);
  // cout << temResStr << endl;



  // string name = "huanglin";
  // string& str = name;//���� huanglin
  // string* url = &name;//ָ�� ��ַ
  // string value = *url;//ָ����ֵ huanglin
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

  // cout << "���ݽṹ" << endl;
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
  // people1.doucter.position = "��������";
  // cout << people1.doucter.position << endl;

  // std::ostringstream oss;
  // oss << "��ַ�ǣ�" << people1.doucter.position << endl;
  // std::cout << oss.str();
  // cout << "���� " << people1.name << endl;
  // cout << "���� " << people1.greenFriend << endl;

  // cout << "�����ࣺpeople" << endl;

  // People people2;
  // people2.age = 24;
  // double peopleAge = people2.get();
  // cout << "���age����:" << peopleAge << endl;
  // people2.set(23.2, "huanglin", "xulinlin");
  // peopleAge = people2.get();
  // cout << "���age����:" << peopleAge << endl;
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

  //ʹ�û���ָ��ָ����������󣬵����麯��������Ķ���ͬ��������ʱ�ͻ���ò�ͬ��ʵ�ַ���
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