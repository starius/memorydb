
#include <stdio.h>
#define DBGPRINTF(fmt, ...)  printf(fmt, __VA_ARGS__)


#include <cstddef>
#include <cassert>
#include <iostream>
#include <vector>

template<typename T>
class Model;

class AbstractReference
{
	virtual void foo() = 0;
};






template<typename T>
class Model
{
public:
	int ref;
	int ref1() { return ((T*)this)->q; }
};




template<typename T>
class Reference : AbstractReference
{
public:
	//~ Model<T>* host() { return (Model<T>*)((char*)this - offsetof(Model<T>, ref)); }
	//~ Model<T>* host() { return (T*)((char*)this - offset); }
	//~ Model<T>* host() { return (T*)((char*)this - offsetof(T, r)); }
	Model<T>* host() { return (T*)((char*)this - offset); }
	
	void foo() {}

private:
	static int offset;
};



class User : public Model<User>
{
public:
	int q;
	int a;
	//~ Reference<User, offsetof(User, q)> r;
	Reference<User> r;
	
	static int i;
};

template<typename T> int Reference<T>::offset = offsetof(User, q);

int User::i = 100;


int f(int a)
{
	return 1;
}
int f(int* a)
{
	return 2;
}

class Df
{
	std::vector<int> a;
	std::vector<int> b;
	//~ std::vector<int> c;
};

int main()
{
	int r = 34;
	double d;
	d = double(r);
	r = int(d);
	
	int* pr = &r;
	
	assert(f(r) == 1);
	assert(f(pr) == 2);
	
	for (int i=0; i<9999999; i++)
	{
		new Df;
	}
	
	char w;
	std::cin >> w;
	
	
	//~ User user;
	//~ assert(user.r.host() == &user);
	
	//~ DBGPRINTF("qwe%s", "123");
	
	//~ std::cout << (int)(user.r.host()) << std::endl;
	//~ std::cout << (int)(&user) << std::endl;
}

