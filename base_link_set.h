#ifndef MEMORYDB_BASELINK_SET_H_
#define MEMORYDB_BASELINK_SET_H_

#include <vector>

#include "base_link.h"

namespace memorydb {

template<bool ordered=false, bool multi=false, typename Container=std::vector>
class BaseLinkSet
{
public:
private:
	Container<BaseLink> refs_;
};

}

#endif // MEMORYDB_BASELINK_SET_H_
