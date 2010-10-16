#ifndef MEMORYDB_ID_H_
#define MEMORYDB_ID_H_

namespace memorydb {

inline void* id_pack(int ID)
{
	return (void*)((ID << 1) | 1);
}

inline int id_unpack(void* ID)
{
	return ((int)ID) >> 1;
}

}

#endif // MEMORYDB_ID_H_
