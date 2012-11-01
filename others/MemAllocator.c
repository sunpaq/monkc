#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MemAllocator.h"
#include "LinkList.h"

static struct node templete_node={NULL,NULL,NULL};
static void* _alloc(void* self, void* classobj_p)
{
	MemAllocator* mself = (MemAllocator*)self;
	void* instance = (void*)malloc(sizeof(*classobj_p));//alloc
	memcpy(instance, classobj_p, sizeof(*classobj_p));//init

	struct node* anode = (struct node*)malloc(sizeof(templete_node));//alloc
	memcpy(anode, &templete_node, sizeof(templete_node));//init

	mself->pool->add_node_next(mself->pool,anode);
	return instance;
}

static void* _freeall(void* self)
{
	MemAllocator* mself = (MemAllocator*)self;
	struct node* iter = mself->pool->head_p->next;
	struct node* tempit;
	while(iter->next!=NULL){
		tempit=iter;
		iter = iter->next;
		mself->pool->delete_node(mself->pool,tempit);
	}
}

static MemAllocator classobj;
MemAllocator* MemAllocator_init()
{
	//data
	classobj.pool = LinkList_init();
	//method
	classobj.alloc = _alloc;
	classobj.freeall = _freeall;
	//mem allocation
	MemAllocator* instance = (MemAllocator*)malloc(sizeof(classobj));//alloc
	memcpy(instance, &classobj, sizeof(classobj));//init
	return instance;
}

void MemAllocator_destory(MemAllocator* self)
{
	self->freeall(self);
	free(self->pool);
	free(self);
}