
#include <iostream>

template<typename T>
class My
{
public:
	T value;
	static int test;
};

template <> int My<int>::test = 0;
template <> int My<char>::test = 0;

int main()
{
	My<int> first;
	first.test = 100;
	std::cout << first.test << std::endl;
	
	My<char> second;
	std::cout << second.test << std::endl;
	second.test = 200;
	std::cout << second.test << std::endl;
	
	My<int> third;
	std::cout << third.test << std::endl;
	third.test = 300;
	std::cout << third.test << std::endl;
}
