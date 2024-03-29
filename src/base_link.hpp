#ifndef MEMORYDB_BASE_LINK_H_
#define MEMORYDB_BASE_LINK_H_

#include "id.hpp"

namespace memorydb {

inline void* id_pack(id_t ID) {
    return (void*)((ID << 1) | 1);
}

class BaseLink {
public:
    BaseLink(id_t ID) : ptr_(id_pack(ID)) { }
    template<typename T>
    BaseLink(T* ptr) : ptr_((void*)ptr) {}
    BaseLink() : ptr_(0) {}
    void* get_ptr() const {
        return ptr_;
    }

    void* get() const {
        return ptr_;
    }
    void unload_simple(BaseLink /* ptr */, id_t ID) {
        set_simple(ID);
    }
    void load_simple(BaseLink ptr, id_t /* ID */) {
        set_simple(ptr);
    }
    void erase_simple() {
        ptr_ = 0;
    }
    void erase_simple(BaseLink /* ptr */) {
        erase_simple();
    }
    void erase_simple(id_t /* ID */) {
        erase_simple();
    }

    void set_simple(BaseLink ptr) {
        ptr_ = ptr.get_ptr();
    }
    void set_simple(id_t ID) {
        ptr_ = id_pack(ID);
    }
    bool operator ==(const BaseLink b) const {
        return ptr_ == b.get_ptr();
    }
    bool operator ==(const void* b) const {
        return ptr_ == b;
    }
    bool operator ==(const id_t b) const {
        return *this == BaseLink(b);
    }

    bool is_set() const {
        return ptr_ != 0;
    }
    bool is_id() const {
        return ((id_t)ptr_) & 1;
    }
    bool is_loaded() const {
        return !is_id() && is_set();
    }
    id_t neighbour_id() const {
        return ((id_t)ptr_) >> 1;
    }

private:
    void* ptr_;
};

}

#endif // MEMORYDB_BASE_LINK_H_

