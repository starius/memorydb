#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include "item.h"

namespace memorydb {

namespace references {

template<typename TYPE_TO>
class Base
{
public:
	int to_id() const;
	Item<TYPE_TO>* get();
	void set(Item<TYPE_TO>* item);
	void set(int id);
	
private:
	Item<TYPE_TO>* item_;
	static Tracker* tracker_;
};


template<typename TYPE_FROM, M2O TYPE_FROM::, typename TYPE_TO>
class M2O
{
public:
	int to_id() const;
	Item<TYPE_TO>* get();
	void set(Item<TYPE_TO>* item);
	void set(int id);
	
private:
	Item<TYPE_TO>* item_;
	static Tracker* tracker_;
};




}

}






//namespace Wt {
  //namespace Dbo {

//template<>
//struct sql_value_traits<memorydb::Reference, void>
//{
  //static const bool specialized = true;
  //static std::string type(SqlConnection *conn, int size);

  ////~ static const char *type(SqlConnection *conn, int size);
  //static void bind(const memorydb::Reference& v, SqlStatement *statement, int column, int size);
  //static bool read(memorydb::Reference& v, SqlStatement *statement, int column, int size);
//};

	//}
//}


#endif // MEMORYDB_REFERENCE_H_

