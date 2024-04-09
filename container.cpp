#include "container.h"
void container::createContain() {
	boost::container::map<std::string, int> mapList;
	mapList["one"] = 1;
	std::cout << mapList["one"] << std::endl;

	boost::container::vector<int> vectArr = { 1,2,3,4 };
	vectArr.push_back(11);
	for (size_t i = 0; i < vectArr.size(); i++)
	{
		std::cout << vectArr[i] << std::endl;
	}

 }