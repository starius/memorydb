#ifndef MEMORYDB_RELATION_H_
#define MEMORYDB_RELATION_H_

#include "reference.hpp"

namespace memorydb {

template<typename FROM, int from_field, 
	typename TO, int to_field, 
	typename LINK_FROM, typename LINK_TO>
class Relation : <FROM, from_field, TO, to_field, LINK_FROM, LINK_TO>
{
public:
private:
};



}

#endif // MEMORYDB_RELATION_H_
