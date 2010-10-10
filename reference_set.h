#ifndef MEMORYDB_REFERENSE_SET_H_
#define MEMORYDB_REFERENSE_SET_H_

#include <vector>

#include "inner.h"
#include "base_link.h"
#include "inner.h"

namespace memorydb {

// REFERENSED is Inner's descendant (it is field)

template<typename T, int int_field, typename REFERENSED>
class BaseLinkSet : Inner<T, int_field>
{
	typedef BaseLink<REFERENSED> BL;
public:
	std::vector<BL>* refs() { return refs_; }
	bool unload_recur();
	bool delete_recur();
	bool delete_recur(REFERENSED* item);
	bool delete_recur(int id);
	bool is_set() const { return !(refs_.empty()); }
	bool is_set(REFERENSED* item) const;
	bool is_set(int id) const;
private:
	std::vector<BL> refs_;
	bool unload(REFERENSED* item, int id);
	bool delete(REFERENSED* item);
};

}

#endif // MEMORYDB_REFERENSE_SET_H_
