
#include <iostream>

class My
{
public:
	static int test;
	int a;
};

class My1 : public My
{
};

int My::test = 0;


int main()
{
	My first;
	first.test = 100;
	std::cout << first.test << std::endl;
	
	My1 second;
	std::cout << second.test << std::endl;
	second.test = 200;
	std::cout << second.test << std::endl;
	
	My third;
	std::cout << third.test << std::endl;
	third.test = 300;
	std::cout << third.test << std::endl;
}
