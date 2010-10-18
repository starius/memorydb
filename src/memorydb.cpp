#include "base_link.hpp"
#include "base_link_set.hpp"
#include "reference.hpp"

#include <iostream>

using namespace memorydb;


class A
{
public:
	Reference<A, 1, A, 1, BaseLinkSet<>, BaseLinkSet<> > m2m;
	Reference<A, 2, A, 2, BaseLink, BaseLink> o2o;
};

memorydb_init(A, 1, m2m);
memorydb_init(A, 2, o2o);


int main()
{
	BaseLink base_link;
	BaseLinkSet<> base_link_set;
	A a1;
	A a2;
	
	a1.o2o.set(&a2);
	
	std::cout << a1.o2o.is_set() << std::endl;
	std::cout << a2.o2o.is_set() << std::endl;
}
