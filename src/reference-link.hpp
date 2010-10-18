

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

};
