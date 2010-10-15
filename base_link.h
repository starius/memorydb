#ifndef MEMORYDB_BASE_LINK_H_
#define MEMORYDB_BASE_LINK_H_

namespace memorydb {

class BaseLink
{
public:
	void set(void* ptr) { ptr_ = ptr; }
	void* get() const { return ptr_; }
private:
	void* ptr_;
};

}

#endif // MEMORYDB_BASE_LINK_H_
