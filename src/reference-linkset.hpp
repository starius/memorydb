

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
		return (neighbour_type*)(elm->get());
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
	
	iterator find(id_t ID) { return find(BaseLink(ID)); }
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
	
	void erase(id_t ID) { erase(BaseLink(ID)); }
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
	
	void set(id_t ID) { set(BaseLink(ID)); }
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
