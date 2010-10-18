#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include "inner.hpp"

namespace memorydb {

template<typename FROM, int from_field, 
	typename TO, int to_field, 
	typename LINK_FROM, typename LINK_TO>
class Reference : Inner<FROM, from_field>, LINK_FROM
{
public:
	//~ Reference<TO, to_field, FROM, from_field, LINK_TO, LINK_FROM>* another_ref();
private:
};



}

#endif // MEMORYDB_REFERENCE_H_
