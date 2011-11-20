#ifndef MEMORYDB_BASE_MODEL_H_
#define MEMORYDB_BASE_MODEL_H_

#include "inner_link_set.hpp"
#include "id.hpp"

namespace memorydb {

template<typename T>
class BaseModel {
public:
    typedef ModelTracker<T> tracker;
    static get(id_t ID) {
        return tracker::get(ID);
    }

    id_t id() const {
        return used_id_ >> 1;    // FIXME!!! save if needed
    }
    bool is_saved() const {
        return id() == 0;
    }

    bool is_used() const {
        return used_id_ & 1;
    }
    void use() {
        used_id_ |= 1;
    }
    void used_reset() {
        used_id_ &= (~1);
    }
private:
    InnerLinkSet<T> inner_link_set_;
    id_t used_id_;
};

}

memorydb_init(T, -1, inner_link_set_);

#endif // MEMORYDB_BASE_MODEL_H_

