#ifndef MEMORYDB_MEMBER_REFERENCE_H_
#define MEMORYDB_MEMBER_REFERENCE_H_

#include "reference.h"

namespace memorydb {

template<Item::* from_reference, Item::* to_reference_addresses>
class MemberReference : public Reference
{
public:
	int host() const;
	
private:
};

}


#endif // MEMORYDB_MEMBER_REFERENCE_H_


