#ifndef MEMORYDB_ITEM_H_
#define MEMORYDB_ITEM_H_

#include <ext/slist>
#include "reference.h"

namespace memorydb {

template<typename T>
class Item
{
private:
	int id_;
	slist<Reference*> refs_;
};

}


#endif // MEMORYDB_ITEM_H_
