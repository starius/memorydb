#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include "inner.h"
#include "base_link.h"

namespace memorydb {

// REFERENSED is Inner's descendant (it is field)

template<typename T, int int_field, typename REFERENSED>
class Reference : Inner<T, int_field>, BaseLink<REFERENSED>
{
};



}

#endif // MEMORYDB_REFERENCE_H_
