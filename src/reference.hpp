#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include <vector>
#include <algorithm>
#include <boost/bind.hpp>

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
	
	neighbour_type* neighbour() const 
	{
		// FIXME!!! load neighbour if needed
		return (neighbour_type*)get();
	}
	
	TO* to() const { return neighbour()->host(); }
	
	void unload() 
	{ 
		neighbour()->unload_simple(this, this->host()->id());
		unload_simple(this, neighbour()->host()->id());
	}
	
	void set(BaseLink ptr) 
	{
		if (is_set()) 
		{
			neighbour()->erase_simple(this);
		}
		set_simple(ptr);
		neighbour()->set_simple(this);
	}
	void set(int ID) { set(BaseLink(ID)); }
	void set(neighbour_type* neighbour) { set(BaseLink(neighbour)); }
	void set(TO* to) { set(neighbour_type::from_host(to)); }
	
	void erase() 
	{ 
		neighbour()->erase_simple(this);
		erase_simple();
	}
	
	void load() 
	{
		if (!is_loaded()) 
		{
			set(TO::get(neighbour_id()));
		}
	}
};


//~ template<typename neighbour_type, typename BLS>
//~ class bls_iterator : BLS::iterator
//~ {
	//~ typedef typename BLS::iterator native_iterator;
//~ public:
	//~ neighbour_type operator *() { return (neighbour_type)(this->native_iterator::operator*()); }
	//~ neighbour_type* operator ->() { return (neighbour_type*)(this->native_iterator::operator->()); }
//~ };


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
	//~ typedef bls_iterator<neighbour_type, BLS> iterator;
	typedef typename BLS::iterator iterator;
	MEMORYDB_INNER(FROM, from_field, my_type)
	
	//~ iterator begin() { return this->BLS::begin(); }
	//~ iterator end() { return this->BLS::end(); }
	
	//FIXME
	//~ iterator find(neighbour_type ptr) { return this->BLS::find(ptr); }
	//FIXME
	
	static neighbour_type* neighbour(BaseLink ptr) 
	{
		return (neighbour_type*)(ptr.get()); // CHECK IS LOADED
	}
	
	static TO* to(BaseLink ptr) 
	{
		return neighbour(ptr)->host();
	}	
	
	static bool cmp_items_id(BaseLink candidate, BaseLink id) 
	{
		return candidate == id || candidate.is_loaded() && to(candidate)->id() == id;
	}
	
	static bool cmp_items_ptr(BaseLink candidate, BaseLink ptr, BaseLink id) 
	{
		return candidate == ptr || !candidate.is_loaded() && candidate == id;
	}
	
	
	iterator find(BaseLink base_link) 
	{
		if (base_link.is_id()) 
		{
			return std::find_if(this->begin(), this->end(), 
				boost::bind(cmp_items_id, _1, base_link));
		}
		else if (base_link.is_loaded()) 
		{
			return std::find_if(this->begin(), this->end(), 
				boost::bind(cmp_items_ptr, _1, base_link, BaseLink(base_link)));
		}
		else 
		{
			return this->end();
		}
	}
	
	iterator find(int ID) { return find(BaseLink(ID)); }
	iterator find(neighbour_type* neighbour) { return find(BaseLink(neighbour)); }
	iterator find(TO* to) { return find(neighbour_type::from_host(to)); }
	
	template<typename T>
	bool has(T what) 
	{
		return find(what) != this->end();
	}
	
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
	//~ void set(int ID) { set(BaseLink(ID)); }
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
