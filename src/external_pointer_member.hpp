#ifndef MEMORYDB_EXTERNAL_POINTER_MEMBER_H_
#define MEMORYDB_EXTERNAL_POINTER_MEMBER_H_

#include "base_link_set.hpp"
#include "base_link.hpp"
#include "reference.hpp"

namespace memorydb {

template<typename TO>
class ExternalPointerMember : Reference<ExternalPointer, -1, TO, -1, BaseLink, BaseLinkSet>
{
public:
private:
};

}


#endif // MEMORYDB_EXTERNAL_POINTER_MEMBER_H_
