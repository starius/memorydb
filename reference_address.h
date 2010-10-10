#ifndef MEMORYDB_REFERENCE_ADDRESS_H_
#define MEMORYDB_REFERENCE_ADDRESS_H_

#include "reference.h"
#include <vector>

namespace memorydb {

class ReferenceAddress
{
public:
	int id() const { return id_; }
	const std::slist<Reference*>* refs() const { return &refs_; }
	void save();
	
private:
	std::vector<Reference*> refs_;
};

}


#endif // MEMORYDB_REFERENCE_ADDRESS_H_

