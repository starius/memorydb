#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include "item.h"

namespace memorydb {


class Reference
{
public:
	int id() const { return id_; }
	//~ Item* operator ->() { return get(); }
	Item* get();
	void set(Item* item);
	void set(int id);
	
private:
	Item* item_;
	int id_;
};

}

#endif // MEMORYDB_REFERENCE_H_

