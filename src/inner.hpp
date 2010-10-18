#ifndef MEMORYDB_INNER_H_
#define MEMORYDB_INNER_H_

namespace memorydb {

template<typename T, int int_field>
class Inner
{
public:
	static T* host(void* inner) 
	{ 
		return (T*)((char*)inner - offset_);
	}
	
	static void* from_host(T* host) 
	{ 
		return (void*)(((char*)host) + offset_);
	}
private:
	static int offset_;
};

#define memorydb_init(T, int_field, field) \
template<> int Inner<T, int_field>::offset_ = offsetof(T, field);

}

#endif // MEMORYDB_INNER_H_
