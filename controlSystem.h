#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class ControlSystem {
private:
	struct people
	{
		char name[20] = {};
		string type = "";
		int age = 0;
	};
	int len = 0;
	people list[100];
public:
	//չʾ������Ա
	void show() {
		for (int i = 0; i < len; i++) {
			std::cout << "���ƣ�" << list[i].name << "�Ա�" << list[i].type << "����" << list[i].age << endl;
		}
	}
	//�����Ա
	void add(const char na[], string ty, int a) {
		people peo;
		strcpy_s(peo.name, na);
		peo.type = ty;
		peo.age = a;
		list[len] = peo;
		len++;
	};
	//ɾ����Ա
	void delPeople(int i) {
		if (i > len) {
			cout << "������Χ" << endl;
		}
		else {
			for (int j = i; j < 99; j++) {
				list[j] = list[j + 1];
			}
			len--;
		}
	};
	//�޸ĳ�Ա
	void updatePeople(int index, char na[]) {
		strcpy_s(list[index].name, na);
	}
};

class StreamSystem : ControlSystem {
private:
	std::vector<std::string> splitString(const std::string& str) {
		std::istringstream iss(str);
		std::vector<std::string> result;
		std::string token;

		while (std::getline(iss, token, ' ')) {
			result.push_back(token);
		}

		return result;
	}
public:
	//չʾ������Ա
	void show() {
		cout << "��ѯpeople.txt�ļ�����" << endl;
		std::ifstream readFile;
		readFile.open("people.txt");
		if (readFile.is_open()) {
			string str = "";
			while (getline(readFile, str))
			{
				cout << str << endl;
			}
			readFile.close();
		}
	};
	void add(const char na[], string ty, int a) {
		//�ļ�����
		std::ofstream inputFile;
		inputFile.open("people.txt", ios::app);
		if (inputFile.is_open()) {
			std::string str;
			str = na;
			str = str + " " + ty + " " + std::to_string(a) + "\n";
			inputFile.write(str.c_str(), str.size());
			inputFile.close();
		}
	};
	void delPeople(int i) {
		ifstream readFile;
		readFile.open("people.txt");
		std::vector<string> list;
		if (readFile.is_open()) {
			string std;
			int num = 0;
			while (getline(readFile, std)) {
				if (num != i) {
					list.push_back(std);
				}
				num++;
			}
		}
		std::ofstream writeFile;
		writeFile.open("people.txt");
		if (writeFile.is_open()) {
			for (std::vector<string>::iterator it = list.begin(); it != list.end(); ++it) {
				string element = *it + "\n";
				writeFile.write(element.c_str(), element.size());
			}
			writeFile.close();
		}
	};
	void updatePeople(int index, char na[]) {
		ifstream readFile;
		readFile.open("people.txt");
		std::vector<string> list;
		if (readFile.is_open()) {
			string std;
			int num = 0;
			while (getline(readFile, std)) {
				if (num != index) {
					list.push_back(std);
				}else {
					string str = "";
					std::vector<std::string> tokens = splitString(std);
					int len = 0;
					for (const auto& token : tokens) {
						if (len == 0) {
							str = na;
						}else {
							str = str + " " + token;
						}
						len++;
					}
					
					list.push_back(str);
				}
				num++;
			}
		}
		std::ofstream writeFile;
		writeFile.open("people.txt");
		if (writeFile.is_open()) {
			for (std::vector<string>::iterator it = list.begin(); it != list.end(); ++it) {
				string element = *it + "\n";
				writeFile.write(element.c_str(), element.size());
			}
			writeFile.close();
		}
	}
};