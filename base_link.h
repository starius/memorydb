#ifndef MEMORYDB_BASE_LINK_H_
#define MEMORYDB_BASE_LINK_H_

namespace memorydb {

// REFERENSED is Inner's descendant (it is field)

template<typename REFERENSED>
class BaseLink
{
public:
	REFERENSED* get();
	bool set(REFERENSED* item);
	bool unload_recur();
	bool delete_recur();
	bool is_set() const { return ref_ == NULL; }
	bool is_loaded() const { return !(ref_ & 1); }
private:
	REFERENSED* ref_;
	bool unload(REFERENSED* item, int id);
	bool delete(REFERENSED* item);
	bool load();
};

}

#endif // MEMORYDB_BASE_LINK_H_
