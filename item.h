#ifndef MEMORYDB_ITEM_H_
#define MEMORYDB_ITEM_H_

#include <ext/slist>
#include "reference.h"

namespace memorydb {

template<typename T> // T is Item's descendant
class Item
{
public:
	int id() const { return id_; }
	const std::slist<Reference<T>*>* refs() const { return &refs_; }
	void save();
	
private:
	bool changed_;
	int id_;
	std::slist<Reference<T>*> refs_;
};

}


#endif // MEMORYDB_ITEM_H_
