#ifndef MEMORYDB_BASELINK_SET_H_
#define MEMORYDB_BASELINK_SET_H_

#include <vector>
#include <algorithm>

#include "base_link.hpp"

//~ Методы BaseLink и BaseLinkSet (указатели везде тут BaseLink или BaseLinkSet) 
	//~ unload_simple(указатель, ID) -- исправиль указанный указатель внутри себя на соответствующий ID
	//~ load_simple(указатель, ID) -- обратное к unload_simple
	//~ delete_simple(указатель или ID):
		//~ BaseLink: установить соотв. указатель или ID на NULL
		//~ BaseLinkSet: удалить соотв. указатель или ID на NULL из себя
			//~ если ordered=false и Container!=list, последний элемент становится на место удаленного
			//~ если ordered=true, происходит сдвиг, чтобы сохранить порядок следования
			//~ в случае multi=true, удаляется одна связь, а не все
	//~ set_simple(указатель или ID) -- для BaseLink устанавливает его смотрящим на это
		//~ для BaseLinkSet, добавляет элемент к списку

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
	iterator find(void* ptr) { return std::find(begin(), end(), ptr); }
	iterator find(int ID) { return find(id_pack(ID)); }
	
	void unload_simple(void* ptr, int ID);
	void load_simple(void* ptr, int ID);
	
	void delete_simple(iterator elm) {
		if (ordered) { 
			refs_.erase(elm); 
		} 
		else {
			*elm = refs_.back();
			refs_.pop_back();
		}
	}
	void delete_simple(void* ptr);
	void delete_simple(int ID) { delete_simple(id_pack(ID)); }
	
	void set_simple(void* ptr) { refs_.push_back(BaseLink(ptr)); }
	void set_simple(int ID) { set_simple(id_pack(ID)); }
	
private:
	 LinksContainer refs_;
};

 
template<>
void BaseLinkSet<>::unload_simple(void* ptr, int ID) 
{
	iterator elm = find(ptr);
	if (elm != end())
	{
		elm->set_simple(ID);
	}
}

template<>
void BaseLinkSet<>::load_simple(void* ptr, int ID) 
{
	iterator elm = find(ID);
	if (elm != end())
	{
		elm->set_simple(ptr);
	}	
}

template<>
void BaseLinkSet<>::delete_simple(void* ptr)
{
	iterator elm = find(ptr);
	if (elm != end())
	{
		delete_simple(elm);
	}
}

}

#endif // MEMORYDB_BASELINK_SET_H_
