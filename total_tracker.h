#ifndef MEMORYDB_TOTAL_TRACKER_H_
#define MEMORYDB_TOTAL_TRACKER_H_

#include "reference.h"
#include "item.h"
#include <map>

namespace memorydb {

class TotalTracker
{
public:
	Item<T>* get(int id);
	
private:
	std::map<id, Item<T>*> loaded_;
	int occupied_; // total space in bytes
	std::slist<Item<T>*> changed_;
	
	Item<T>* load(int id);
	void unload(int id);
	void unload(Item<T>* item);
};

}


#endif // MEMORYDB_TOTAL_TRACKER_H_
