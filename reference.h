#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include "item.h"

namespace memorydb {

template<typename T>
class Reference
{
public:
	int id() const { return id_; }
	//~ T* operator ->() { return get(); }
	T* get();
	void set(T*);
	void set(int id);
private:
	T* item_;
	int id_;
};

}

#endif // MEMORYDB_REFERENCE_H_

