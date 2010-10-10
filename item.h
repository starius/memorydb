#ifndef MEMORYDB_ITEM_H_
#define MEMORYDB_ITEM_H_

#include <ext/slist>
#include "reference.h"

namespace memorydb {

class Item
{
public:
	int id() const { return id_; }
	const std::slist<Reference*>* refs() const { return &refs_; }
	
private:
	bool changed_;
	int id_;
	std::slist<Reference*> refs_;
	static Tracker* tracker_;
};

}


#endif // MEMORYDB_ITEM_H_
