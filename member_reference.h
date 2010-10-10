#ifndef MEMORYDB_MEMBER_REFERENCE_H_
#define MEMORYDB_MEMBER_REFERENCE_H_

#include "reference.h"

namespace memorydb {

template<typename T, T::* field>
class MemberReference : Reference
{
public:
	int id() const { return id_; }
	const std::slist<Reference*>* refs() const { return &refs_; }
	void save();
	
private:
	bool changed_;
	int id_;
	std::slist<Reference*> refs_;
	static Tracker* tracker_;
};

}


#endif // MEMORYDB_MEMBER_REFERENCE_H_


