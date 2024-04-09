#include <string>
#include <cstring>

template <typename T>
class Person
{
public:
	Person(T a);
	void getPerson();
	T age;
};

template <typename T>
Person<T>::Person(T a) {
	this->age = a;
	std::cout << "ÊäÈëa" << this->age << std::endl;
}

template <typename T>
void Person<T>::getPerson() {
	std::cout << "Êä³öa" << this->age << std::endl;
}