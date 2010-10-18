#include "base_link.hpp"
#include "base_link_set.hpp"
#include "reference.hpp"

#include <iostream>
#include <cassert>

using namespace memorydb;


class A
{
public:
	A(): a(0) {}
	
	Reference<A, 1, A, 1, BaseLinkSet<>, BaseLinkSet<> > m2m;
	Reference<A, 2, A, 2, BaseLink, BaseLink> o2o;
	
	int a;
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
	a2.o2o.set(&a2);
	a2.o2o.erase();
	a1.o2o.set(&a2);
	a1.o2o.set(&a2);
	
	assert(a1.o2o.is_set() == true);
	assert(a2.o2o.is_set() == true);
	
	a1.a = 1;
	a2.a = 2;
	
	assert(a1.o2o.neighbour()->host()->a == 2);
	assert(a2.o2o.neighbour()->host()->a == 1);
}
