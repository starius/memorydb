#ifndef MEMORYDB_REFERENCE_SET_H_
#define MEMORYDB_REFERENCE_SET_H_

#include "base_link_set.h"
#include "inner.h"

namespace memorydb {

// REFERENSED is Inner's descendant (it is field)

template<typename T, int int_field, typename REFERENSED>
class BaseLinkSet : Inner<T, int_field>, BaseLink<REFERENSED>
{
};

}

#endif // MEMORYDB_REFERENCE_SET_H_
