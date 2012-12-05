#ifndef __ObjectsPool__
#define __ObjectsPool__

#include "Basic.h"

typedef struct tag_ObjectsPool
{
	extends_LinkList;
	//data
	LinkList* list;
	//methods
	int (*put)(void* self, void* aobject_p);
	void*(*get)(void* self,int index);
	void (*destory)(void* self);
}ObjectsPool;

extern ObjectsPool* ObjectsPool_init(MemAllocator* allocator);

#endif
