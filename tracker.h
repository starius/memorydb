#ifndef MEMORYDB_TRACKER_H_
#define MEMORYDB_TRACKER_H_

#include "reference.h"
#include "item.h"
#include <map>

namespace memorydb {

class Tracker
{
public:
	Item* get(int id);
	
private:
	std::map<id, Item*> loaded_;
	int occupied_; // total space in bytes
	std::slist<Item*> changed_;
	
	Item* load(int id);
	void unload(int id);
	void unload(Item* item);
	void save(int id);
	void save(Item* item);
};

static Tracker tracker;

}


#endif // MEMORYDB_TRACKER_H_
