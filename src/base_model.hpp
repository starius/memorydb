#ifndef MEMORYDB_BASE_MODEL_H_
#define MEMORYDB_BASE_MODEL_H_

#include "inner_link_set.hpp"

namespace memorydb {

template<typename T>
class BaseModel
{
public:
	typedef ModelTracker<T> tracker;
	
	int id() const { return id_; } // FIXME!!! save if needed
	bool is_saved() const { return id_ == 0; }
private:
	InnerLinkSet<T> inner_link_set_;
	int id_;
};

}

memorydb_init(T, -1, inner_link_set_);

#endif // MEMORYDB_BASE_MODEL_H_
