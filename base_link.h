#ifndef MEMORYDB_BASE_LINK_H_
#define MEMORYDB_BASE_LINK_H_

namespace memorydb {

class BaseLink
{
public:
	void* get() const { return ptr_; }
	void unload_simple(void* ptr, int ID) { set_simple(int ID); }
	void load_simple(void* ptr, int ID) { set_simple(ptr); }
	void delete_simple(void* ptr) { delete_simple(); }
	void delete_simple(int ID) { delete_simple(); }
private:
	void* ptr_;
	void set_simple(void* ptr) { ptr_ = ptr; }
	void set_simple(int ID) { ptr_ = (ID<<1) | 1; }
	void delete_simple() { ptr_ = NULL; }
};

}

#endif // MEMORYDB_BASE_LINK_H_
