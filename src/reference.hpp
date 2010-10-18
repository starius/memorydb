#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include "inner.hpp"
#include "base_link.hpp"
#include "base_link_set.hpp"

namespace memorydb {

//~ * умеет получать указатели на LINK_TO, на который(ые) ссылается
//~ * возвращает указатели на Reference<TO, to_field, FROM, from_field, LINK_TO, LINK_FROM>
	//~ unload() -- превращает все указатели в ID
	//~ delete() -- обнуляет все ID/указатели или удаляет их в случае BaseLinkSet
	//~ delete(указатель или ID) -- исключает из себя этот элемент (для BaseLinkSet)
	//~ set(указатель или ID) -- налаживает связь с этим элементом
		//~ если LINK_TO=BaseLink, то сначала вызывает у Reference этого элемента delete (если был установлен)
	//~ load() -- загружает объект(ы), на которые ссылается, устанавливает указатели
	//~ load(ID) -- (для BaseLinkSet) загружает объект с таким ID

template<typename FROM, int from_field, 
	typename TO, int to_field, 
	typename LINK_FROM, typename LINK_TO>
class Reference : LINK_FROM
{
public:
	FROM* host() { return Inner<FROM, from_field>::host(this); }
private:
};


template<typename FROM, int from_field, 
	typename TO, int to_field, 
	typename LINK_TO>
class Reference<FROM, from_field, TO, to_field, BaseLink, LINK_TO>
 : BaseLink
{
public:
	Reference<TO, to_field, FROM, from_field, LINK_TO, BaseLink>* const neighbour() {
		return (Reference<TO, to_field, FROM, from_field, LINK_TO, BaseLink>*)(get());
	}
	
	void unload() { 
		unload_simple(this, neighbour()->host()->id());
		neighbour()->unload_simple(this, this->host()->id());
	}
	
	void set(void* ptr) {
		if (is_set()) {
			neighbour()->delete_simple(this);
		}
		set_simple(ptr);
	}
private:
};


}

#endif // MEMORYDB_REFERENCE_H_
