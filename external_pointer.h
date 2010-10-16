#ifndef MEMORYDB_EXTERNAL_POINTER_H_
#define MEMORYDB_EXTERNAL_POINTER_H_

#include "external_pointer_member.h"

namespace memorydb {

template<typename TO>
class ExternalPointer
{
public:
private:
	ExternalPointerMember<TO> external_pointer_member_;
};

}


#endif // MEMORYDB_EXTERNAL_POINTER_MEMBER_H_
