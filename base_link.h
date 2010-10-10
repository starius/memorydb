#ifndef MEMORYDB_BASE_LINK_H_
#define MEMORYDB_BASE_LINK_H_

namespace memorydb {

// REFERENSED is Inner's descendant (it is field)

template<typename REFERENSED>
class BaseLink
{
public:
	REFERENSED* get();
	void set(REFERENSED* item);
private:
	REFERENSED* ref_;
};

}

#endif // MEMORYDB_BASE_LINK_H_
