#ifndef MEMORYDB_BASELINK_SET_H_
#define MEMORYDB_BASELINK_SET_H_

#include <boost/foreach.hpp>

#include "base_link.h"

Методы BaseLink и BaseLinkSet (указатели везде тут BaseLink или BaseLinkSet) 
	unload_simple(указатель, ID) -- исправиль указанный указатель внутри себя на соответствующий ID
	load_simple(указатель, ID) -- обратное к unload_simple
	delete_simple(указатель или ID):
		BaseLink: установить соотв. указатель или ID на NULL
		BaseLinkSet: удалить соотв. указатель или ID на NULL из себя
			если ordered=false и Container!=list, последний элемент становится на место удаленного
			если ordered=true, происходит сдвиг, чтобы сохранить порядок следования
			в случае multi=true, удаляется одна связь, а не все
	set_simple(указатель или ID) -- для BaseLink устанавливает его смотрящим на это
		для BaseLinkSet, добавляет элемент к списку

namespace memorydb {

template<bool ordered=false, bool multi=false, typename Container=std::vector>
class BaseLinkSet
{
public:
	void* get() const { return ptr_; }
	void unload_simple(void* ptr, int ID);
	void load_simple(void* ptr, int ID);
	void delete_simple(void* ptr) { delete_simple(); }
	void delete_simple(int ID) { delete_simple(); }
private:
	Container<BaseLink> refs_;
};


template<>
void BaseLinkSet::unload_simple(void* ptr, int ID) 
{
	BOOST_FOREACH(BaseLink& ref, refs_)
	{
		if (ref == ptr)
		{
			ref.set_simple(ID);
			return;
		}
	}
}

template<>
void BaseLinkSet::load_simple(void* ptr, int ID) 
{
	register void* pattern = id_pack(ID);
	BOOST_FOREACH(BaseLink& ref, refs_)
	{
		if (ref == pattern)
		{
			ref.set_simple(ptr);
			return;
		}
	}
}



}

#endif // MEMORYDB_BASELINK_SET_H_
