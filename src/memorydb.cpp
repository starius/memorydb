#include "base_link.hpp"
#include "base_link_set.hpp"
#include "reference.hpp"

using namespace memorydb;


class A
{
public:
	Reference<A, 1, A, 1, BaseLinkSet<>, BaseLinkSet<> > ref;
};

memorydb_init(A, 1, ref);


int main()
{
	BaseLink base_link;
	BaseLinkSet<> base_link_set;
	
}
