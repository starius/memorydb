#ifndef MEMORYDB_ITEM_H_
#define MEMORYDB_ITEM_H_

#include "inner_link_set.h"

namespace memorydb {

template<typename T>
class BaseModel
{
public:
private:
	InnerLinkSet<T> inner_link_set_;
	int id_;
};

}


#endif // MEMORYDB_ITEM_H_
