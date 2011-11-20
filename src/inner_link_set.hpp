#ifndef MEMORYDB_INNER_LINK_SET_H_
#define MEMORYDB_INNER_LINK_SET_H_

#include "base_link_set.hpp"
#include "base_link.hpp"
#include "reference.hpp"
#include "external_pointer.hpp"

namespace memorydb {

template<typename FROM>
class InnerLinkSet : Reference < FROM, -1, ExternalPointer, -1, BaseLinkSet, BaseLink > {
public:
private:
};

}

#endif // MEMORYDB_INNER_LINK_SET_H_

