#ifndef MEMORYDB_REFERENSE_SET_H_
#define MEMORYDB_REFERENSE_SET_H_

#include <vector>

#include "inner.h"
#include "base_link.h"
#include "inner.h"

namespace memorydb {

// REFERENSED is Inner's descendant (it is field)

template<typename T, int int_field, typename REFERENSED>
class BaseLinkSet : Inner<T, int_field>
{
	typedef BaseLink<REFERENSED> BL;
public:
	std::vector<BL>* refs() { return refs_; }
private:
	std::vector<BL> refs_;
};

}

#endif // MEMORYDB_REFERENSE_SET_H_
