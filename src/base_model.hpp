#ifndef MEMORYDB_BASE_MODEL_H_
#define MEMORYDB_BASE_MODEL_H_

#include "inner_link_set.hpp"

namespace memorydb {

template<typename T>
class BaseModel
{
public:
	typedef ModelTracker<T> tracker;
	static get(int ID) { return tracker::get(ID); }
	
	int id() const { return id_; } // FIXME!!! save if needed
	bool is_saved() const { return id() == 0; }
	
	bool is_used() const { return used_; }
	void use() { used_ = true; }
	void used_reset() { used_ = false; }
private:
	InnerLinkSet<T> inner_link_set_;
	int id_;
	bool used_;
};

}

memorydb_init(T, -1, inner_link_set_);

#endif // MEMORYDB_BASE_MODEL_H_
