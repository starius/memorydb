#include "base_link.hpp"
#include "base_link_set.hpp"
#include "reference.hpp"

using namespace memorydb;


class A
{
	Reference<A, 1, A, 1, BaseLinkSet<>, BaseLinkSet<> > ref;
};


int main()
{
	BaseLink base_link;
	BaseLinkSet<> base_link_set;
	
}
