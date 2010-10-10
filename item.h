#ifndef MEMORYDB_ITEM_H_
#define MEMORYDB_ITEM_H_

#include "reference.h"

namespace memorydb {

class Item
{
public:
	int id() const { return id_; }
	const std::slist<Reference*>* refs() const { return &refs_; }
	void save();
	
private:
	bool changed_;
	int id_;
	static Tracker* tracker_;
};

}


#endif // MEMORYDB_ITEM_H_
