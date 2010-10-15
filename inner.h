#ifndef MEMORYDB_INNER_H_
#define MEMORYDB_INNER_H_

namespace memorydb {

template<typename T, int int_field>
class Inner
{
public:
	T* host() const { return (T*)((char*)this - offset); }
	//~ int host_id() const { return host()->id(); }
private:
	static int offset_;
};

#define memorydb_init(T, int_field, field) \
template<typename T, int int_field> int Inner<T, int_field>::offset_ = offsetof(T, field);

}

#endif // MEMORYDB_INNER_H_
