#ifndef MEMORYDB_REFERENCE_H_
#define MEMORYDB_REFERENCE_H_

#include "item.h"

namespace memorydb {


class Reference
{
public:
	int id() const { return id_; }
	//~ Item* operator ->() { return get(); }
	Item* get();
	void set(Item* item);
	void set(int id);
	
private:
	Item* item_;
};

}


namespace Wt {
  namespace Dbo {

template<>
struct sql_value_traits<memorydb::Reference, void>
{
  static const bool specialized = true;
  static std::string type(SqlConnection *conn, int size);

  //~ static const char *type(SqlConnection *conn, int size);
  static void bind(const memorydb::Reference& v, SqlStatement *statement, int column, int size);
  static bool read(memorydb::Reference& v, SqlStatement *statement, int column, int size);
};

	}
}


#endif // MEMORYDB_REFERENCE_H_

