#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include "item.h"

namespace memorydb {

template<typename T>
class Reference
{
public:
	int id() const { return id_; }
	//~ Item<T>* operator ->() { return get(); }
	Item<T>* get();
	void set(Item<T>* item);
	void set(int id);
	
private:
	Item<T>* item_;
	int id_;
};

}

#endif // MEMORYDB_REFERENCE_H_

