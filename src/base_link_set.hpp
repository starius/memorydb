#ifndef MEMORYDB_BASELINK_SET_H_
#define MEMORYDB_BASELINK_SET_H_

#include <vector>
#include <algorithm>

#include "base_link.hpp"

namespace memorydb {

template<bool ordered=false, bool multi=false, template<typename, typename> class Container=std::vector>
class BaseLinkSet
{
public:
	typedef Container<BaseLink, std::allocator<BaseLink> > LinksContainer;
	typedef typename LinksContainer::iterator iterator;
	
	iterator begin() { return refs_.begin(); }
	iterator end() { return refs_.end(); }
	int size() const { return refs_.size(); }
	bool empty() const { return refs_.empty(); }
	iterator find(BaseLink ptr) { return std::find(begin(), end(), ptr); }
	iterator find(int ID) { return find(BaseLink(ID)); }
	
	void unload_simple(BaseLink ptr, int ID);
	void load_simple(BaseLink ptr, int ID);
	
	void erase_simple(iterator elm) 
	{
		if (ordered) 
		{ 
			refs_.erase(elm); 
		} 
		else 
		{
			*elm = refs_.back();
			refs_.pop_back();
		}
	}
	void erase_simple(BaseLink ptr);
	void erase_simple(int ID) { erase_simple(BaseLink(ID)); }
	
	void set_simple(BaseLink ptr) 
	{ 
		if (multi || find(ptr) == end()) 
		{
			refs_.push_back(BaseLink(ptr));
		}
	}
	void set_simple(int ID) { set_simple(BaseLink(ID)); }
	
private:
	LinksContainer refs_;
};

 
template<>
void BaseLinkSet<>::unload_simple(BaseLink ptr, int ID) 
{
	iterator elm = find(ptr);
	if (elm != end())
	{
		elm->set_simple(ID);
	}
}

template<>
void BaseLinkSet<>::load_simple(BaseLink ptr, int ID) 
{
	iterator elm = find(ID);
	if (elm != end())
	{
		elm->set_simple(ptr);
	}	
}

template<>
void BaseLinkSet<>::erase_simple(BaseLink ptr)
{
	iterator elm = find(ptr);
	if (elm != end())
	{
		erase_simple(elm);
	}
}

}

#endif // MEMORYDB_BASELINK_SET_H_
