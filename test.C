
#include <cstddef>
#include <cassert>
#include <iostream>

template<typename T>
class Model;

class AbstractReference
{
};


template<typename T, int offset>
class Reference;



template<typename T>
class Model
{
public:
	int ref;
	int ref1() { return ((T*)this)->q; }
};




template<typename T, int offset>
class Reference : AbstractReference
{
public:
	//~ Model<T>* host() { return (Model<T>*)((char*)this - offsetof(Model<T>, ref)); }
	Model<T>* host() { return (T*)((char*)this - offset); }
};


class User : public Model<User>
{
public:
	int q;
	int a;
	//~ Reference<User, offsetof(Model<T>, ref)> r;
	Reference<User, 12> r;
};




int main()
{
	User user;
	assert(user.r.host() == &user);
	
	//~ std::cout << (int)(user.r.host()) << std::endl;
	//~ std::cout << (int)(&user) << std::endl;
}

