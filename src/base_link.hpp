#ifndef MEMORYDB_BASE_LINK_H_
#define MEMORYDB_BASE_LINK_H_

#include "id.hpp"

namespace memorydb {

class BaseLink
{
public:
	BaseLink(void* ptr) : ptr_(ptr) {}
	
	void* get() const { return ptr_; }
	void unload_simple(void* ptr, int ID) { set_simple(ID); }
	void load_simple(void* ptr, int ID) { set_simple(ptr); }
	void delete_simple(void* ptr) { delete_simple(); }
	void delete_simple(int ID) { delete_simple(); }
	
	void set_simple(void* ptr) { ptr_ = ptr; }
	void set_simple(int ID) { ptr_ = id_pack(ID); }
	void delete_simple() { ptr_ = 0; }
	bool operator ==(const void* b) const { return ptr_ == b; }
	bool operator ==(const int b) const { return ptr_ == id_pack(b); }
	
	bool is_set() const { return ptr_ != 0; }
	bool is_loaded() const { return !is_id(ptr_); }
private:
	void* ptr_;
};


}

#endif // MEMORYDB_BASE_LINK_H_
