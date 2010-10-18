#ifndef MEMORYDB_INNER_LINK_SET_H_
#define MEMORYDB_INNER_LINK_SET_H_

#include "base_link_set.h"
#include "base_link.h"
#include "reference.h"
#include "external_pointer.h"

namespace memorydb {

template<typename FROM>
class InnerLinkSet : Reference<FROM, -1, ExternalPointer, -1, BaseLinkSet, BaseLink>
{
public:
private:
};

}




#endif // MEMORYDB_INNER_LINK_SET_H_
