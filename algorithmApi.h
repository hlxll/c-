#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
class SortMapClass {
public:
	bool operator()(int val, int val2) const {
		return val2 > val;
	}
};
struct GetForData {
	void operator()(const pair<int, std::string>& element) const {
		cout << element.first << endl;
	}
};

struct SortMapPair {
	bool operator()(const pair<int, std::string>& val, const pair<int, std::string>& val2) const  {
		return val.first > val2.first;
	}
};
class Algorithm {
public:
	void sortNum(std::vector<int> arr) {
		std::sort(arr.begin(), arr.end());
		for (const auto& num : arr)
		{
			cout << num << endl;
		}
	};

	void AlgorNumber() {
		map<int, string, SortMapClass> p;
		p.insert({ 1, "huang" });
		p.insert({ 3, "xll" });
		p.insert({ 2, "xll" });
		/*for (map<int, string>::iterator it = p.begin(); it != p.end(); it++) {
			cout << it->first << endl;
		}*/
		for_each(p.begin(), p.end(), GetForData());
		vector<pair<int, string>> vec(p.begin(), p.end());
		sort(vec.begin(), vec.end(), SortMapPair());

		for_each(vec.begin(), vec.end(), GetForData());
	}
};