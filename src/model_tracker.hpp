#ifndef MEMORYDB_MODEL_TRACKER_H_
#define MEMORYDB_MODEL_TRACKER_H_

#include "reference.hpp"
#include <map>

namespace memorydb {

template<typename T>
class ModelTracker
{
public:
	Tracker(char* db_name);
	Item* get(id_t id);
	
private:
	std::map<id, Item*> loaded_;
	int occupied_; // total space in bytes
	std::slist<Item*> changed_;
	
	Item* load(id_t id);
	void unload(id_t id);
	void unload(Item* item);
	void save(id_t id);
	void save(Item* item);
};


}


#endif // MEMORYDB_MODEL_TRACKER_H_
