#ifndef MEMORYDB_TRACKER_H_
#define MEMORYDB_TRACKER_H_

#include "reference.h"
#include "item.h"
#include <map>

namespace memorydb {

template<typename T>
class Tracker
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


#endif // MEMORYDB_TRACKER_H_
