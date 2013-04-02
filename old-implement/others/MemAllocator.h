#ifndef __MemAllocator__
#define __MemAllocator__

#include "LinkList.h"

#define extends_MemAllocator LinkList* pool;\
		void* (*alloc)(void* self, void* classobj);\
		void* (*freeall)(void* self);\

typedef struct tag_MemAllocator
{
	extends_MemAllocator
}MemAllocator;

extern MemAllocator* MemAllocator_init();
extern void MemAllocator_destory(MemAllocator* self);

#endif