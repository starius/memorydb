#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include <vector>

#include "id.hpp"
#include "inner.hpp"
#include "base_link.hpp"
#include "base_link_set.hpp"

namespace memorydb {

//~ * умеет получать указатели на LINK_TO, на который(ые) ссылается
//~ * возвращает указатели на Reference<TO, to_field, FROM, from_field, LINK_TO, LINK_FROM>
	//~ unload() -- превращает все указатели в ID
	//~ erase() -- обнуляет все ID/указатели или удаляет их в случае BaseLinkSet
	//~ erase(указатель или ID) -- исключает из себя этот элемент (для BaseLinkSet)
	//~ set(указатель или ID) -- налаживает связь с этим элементом
		//~ если LINK_TO=BaseLink, то сначала вызывает у Reference этого элемента erase (если был установлен)
	//~ load() -- загружает объект(ы), на которые ссылается, устанавливает указатели
	//~ load(ID) -- (для BaseLinkSet) загружает объект с таким ID

template<typename FROM, int from_field, 
	typename TO, int to_field, 
	typename LINK_FROM, typename LINK_TO>
class Reference : public LINK_FROM
{
public:
private:
};

#define MEMORYDB_INNER(FROM, from_field, my_type) \
FROM* host() { return Inner<FROM, from_field>::host((void*)this); } \
static my_type* from_host(FROM* host) { \
	return (my_type*)(Inner<FROM, from_field>::from_host(host)); \
}


template<typename FROM, int from_field, 
	typename TO, int to_field, 
	typename LINK_TO>
class Reference<FROM, from_field, TO, to_field, BaseLink, LINK_TO>
 : public BaseLink
{
public:
	typedef Reference<FROM, from_field, TO, to_field, BaseLink, LINK_TO> my_type;
	typedef Reference<TO, to_field, FROM, from_field, LINK_TO, BaseLink> neighbour_type;
	MEMORYDB_INNER(FROM, from_field, my_type)
	
	neighbour_type* neighbour() const {
		// FIXME!!! load neighbour if needed
		return (neighbour_type*)get();
	}
	
	TO* to() const { return neighbour()->host(); }
	
	void unload() { 
		neighbour()->unload_simple(this, this->host()->id());
		unload_simple(this, neighbour()->host()->id());
	}
	
	void set(void* ptr) {
		if (is_set()) {
			neighbour()->erase_simple(this);
		}
		set_simple(ptr);
		neighbour()->set_simple(this);
	}
	void set(int ID) { set(id_pack(ID)); }
	void set(neighbour_type* neighbour) { set((void*)neighbour); }
	void set(TO* to) { set(neighbour_type::from_host(to)); }
	
	void erase() { 
		neighbour()->erase_simple(this);
		erase_simple();
	}
	
	void load() {
		if (!is_loaded()) {
			set(TO::get(neighbour_id()));
		}
	}
};



template<typename FROM, int from_field, 
	typename TO, int to_field, 
	typename LINK_TO, 
	bool ordered, bool multi, template<typename, typename> class Container>
class Reference<FROM, from_field, TO, to_field, BaseLinkSet<ordered, multi, Container>, LINK_TO>
 : public BaseLinkSet<ordered, multi, Container>
{
public:
	typedef BaseLinkSet<ordered, multi, Container> BLS;
	typedef Reference<FROM, from_field, TO, to_field, BLS, LINK_TO> my_type;
	typedef Reference<TO, to_field, FROM, from_field, LINK_TO, BLS> neighbour_type;
	MEMORYDB_INNER(FROM, from_field, my_type)
	
	//~ typedef typename LinksContainer::iterator iterator;
	//~ 
	//~ neighbour_type* neighbour() const {
		//~ // FIXME!!! load neighbour if needed
		//~ return (neighbour_type*)get();
	//~ }
	//~ 
	//~ void unload() {
		//~ neighbour()->unload_simple(this, this->host()->id());
		//~ unload_simple(this, neighbour()->host()->id());
	//~ }
	//~ 
	//~ void set(void* ptr) {
		//~ if (is_set()) {
			//~ neighbour()->erase_simple(this);
		//~ }
		//~ set_simple(ptr);
	//~ }
	//~ void set(int ID) { set(id_pack(ID)); }
	//~ void set(neighbour_type* neighbour) { set((void*)neighbour); }
	//~ void set(TO* to) { set(neighbour_type::from_host(to)); }
	//~ 
	//~ void erase() { set((void*)0); }
	//~ 
	//~ void load() {
		//~ if (!is_loaded()) {
			//~ set(TO::get(neighbour_id()));
		//~ }
	//~ }
};




}

#endif // MEMORYDB_REFERENCE_H_
