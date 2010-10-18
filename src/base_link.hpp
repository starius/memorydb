#ifndef MEMORYDB_BASE_LINK_H_
#define MEMORYDB_BASE_LINK_H_

#include "id.hpp"

namespace memorydb {

class BaseLink
{
public:
	BaseLink(void* ptr) : ptr_(ptr) {}
	BaseLink() : ptr_(0) {}
	void* get_ptr() const { return ptr_; }
	
	void* get() const { return ptr_; }
	void unload_simple(BaseLink ptr, int ID) { set_simple(ID); }
	void load_simple(BaseLink ptr, int ID) { set_simple(ptr); }
	void erase_simple() { ptr_ = 0; }
	void erase_simple(BaseLink ptr) { erase_simple(); }
	void erase_simple(int ID) { erase_simple(); }
	
	void set_simple(BaseLink ptr) { ptr_ = ptr.get_ptr(); }
	void set_simple(int ID) { ptr_ = id_pack(ID); }
	bool operator ==(const BaseLink b) const { return ptr_ == b.get_ptr(); }
	bool operator ==(const void* b) const { return ptr_ == b; }
	bool operator ==(const int b) const { return ptr_ == id_pack(b); }
	
	bool is_set() const { return ptr_ != 0; }
	bool is_loaded() const { return !is_id(ptr_); }
	int neighbour_id() const { return id_unpack(ptr_); }
	
private:
	void* ptr_;
};


}

#endif // MEMORYDB_BASE_LINK_H_
