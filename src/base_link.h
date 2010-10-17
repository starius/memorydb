#ifndef MEMORYDB_BASE_LINK_H_
#define MEMORYDB_BASE_LINK_H_

#include "id.h"

namespace memorydb {

class BaseLink
{
public:
	void* get() const { return ptr_; }
	void unload_simple(void* ptr, int ID) { set_simple(ID); }
	void load_simple(void* ptr, int ID) { set_simple(ptr); }
	void delete_simple(void* ptr) { delete_simple(); }
	void delete_simple(int ID) { delete_simple(); }
	
	void set_simple(void* ptr) { ptr_ = ptr; }
	void set_simple(int ID) { ptr_ = id_pack(ID); }
	void delete_simple() { ptr_ = NULL; }
	​bool operator ==(const void* b) const;
private:
	void* ptr_;
};


}

#endif // MEMORYDB_BASE_LINK_H_
