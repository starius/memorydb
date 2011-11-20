#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include "inner.hpp"
#include "base_link.hpp"
#include "base_link_set.hpp"

namespace memorydb {

template < typename FROM, int from_field,
         typename TO, int to_field,
         typename LINK_FROM, typename LINK_TO >
class Reference : public LINK_FROM {
public:
private:
};

#define MEMORYDB_INNER(FROM, from_field, my_type) \
FROM* host() { return Inner<FROM, from_field>::host((void*)this); } \
static my_type* from_host(FROM* host) { \
    return (my_type*)(Inner<FROM, from_field>::from_host(host)); \
}

#include "reference-link.hpp"
#include "reference-linkset.hpp"

}

#endif // MEMORYDB_REFERENCE_H_

