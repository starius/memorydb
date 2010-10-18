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
	
	neighbour_type* neighbour() 
	{
		// FIXME!!! load neighbour if needed
		if (!is_loaded())
		{
			TO* to = TO::get(neighbour_id());
			neighbour_type* n = neighbour_type::from_host(to);
			this->load_simple(BaseLink(n), n->host()->id());
			n->load_simple(this, this->host()->id());
		}
		return (neighbour_type*)get();
	}
	
	TO* to() { return neighbour()->host(); }
	
	void unload() 
	{
		if (is_loaded()) 
		{
			neighbour()->unload_simple(this, this->host()->id());
			this->unload_simple(this, neighbour()->host()->id());
		}
	}
	
	void set(BaseLink ptr) 
	{
		if (is_set()) 
		{
			neighbour()->erase_simple(this);
		}
		this->set_simple(ptr);
		neighbour()->set_simple(this);
	}
	void set(int ID) { set(BaseLink(ID)); }
	void set(neighbour_type* neighbour) { set(BaseLink(neighbour)); }
	void set(TO* to) { set(neighbour_type::from_host(to)); }
	
	void erase() 
	{
		if (is_set())  // IS IT NEEDED ??
		{
			neighbour()->erase_simple(this);
			this->erase_simple();
		}
	}

//~ private:
	//~ void load() 
	//~ {
		//~ if (!is_loaded()) 
		//~ {
			//~ set(TO::get(neighbour_id()));
		//~ }
	//~ }
};



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
	
	neighbour_type* neighbour(BaseLink ptr) 
	{
		if (!ptr.is_loaded())
		{
			neighbour(find(ptr));
		}
		return (neighbour_type*)(ptr.get());
	}
	
	neighbour_type* neighbour(iterator elm) 
	{
		if (!elm->is_loaded())
		{
			TO* to = TO::get(elm->neighbour_id());
			neighbour_type* n = neighbour_type::from_host(to);
			this->load_simple(BaseLink(n), n->host()->id());
			n->load_simple(this, this->host()->id());
		}
		return (neighbour_type*)(elm->get()); // CHECK IS LOADED
	}
		
	TO* to(BaseLink ptr) 
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
	
	void unload() 
	{
		for (iterator elm = this->begin(); elm < this->end(); ++elm)
		{
			if (elm->is_loaded())
			{
				neighbour(elm)->unload_simple(this, this->host()->id());
				elm->unload_simple(this, neighbour(elm)->host()->id());
			}
		}
	}
	
	void erase() 
	{
		for (iterator elm = this->begin(); elm < this->end(); ++elm)
		{
			neighbour(elm)->erase_simple(this, this->host()->id());
		}
		this->refs_.clear();
	}
	
	void erase(BaseLink ptr) 
	{
		iterator elm = find(ptr);
		if (elm != this->end())
		{
			neighbour(elm)->erase_simple(this, this->host()->id());
			this->refs_.erase_simple(elm);
		}
	}
	
	void erase(int ID) { erase(BaseLink(ID)); }
	void erase(neighbour_type* neighbour) { erase(BaseLink(neighbour)); }
	void erase(TO* to) { erase(neighbour_type::from_host(to)); }
	
	
	void set(BaseLink ptr) 
	{
		if (multi || !has(ptr)) 
		{
			this->set_simple(ptr);
			neighbour(ptr)->set_simple(this);
		}
	}	
	
	void set(int ID) { set(BaseLink(ID)); }
	void set(neighbour_type* neighbour) { set(BaseLink(neighbour)); }
	void set(TO* to) { set(neighbour_type::from_host(to)); }
	
	
	void load() 
	{
		for (iterator elm = this->begin(); elm < this->end(); ++elm)
		{
			if (!elm->is_loaded())
			{
				neighbour(elm)->load_simple(this, this->host()->id());
				elm->load_simple(this, neighbour(elm)->host()->id());
			}
		}
	}
	
};




}

#endif // MEMORYDB_REFERENCE_H_
