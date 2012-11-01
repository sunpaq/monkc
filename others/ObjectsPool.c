
#include "ObjectsPool.h"

static struct node templete_node = {NULL,NULL,NULL};

static int _put(void* self, void* aobject_p)
{
	ObjectsPool* mself = (ObjectsPool*)self;
	struct node* anode = (struct node*)malloc(sizeof(templete_node));
	memcpy(anode, &templete_node, sizeof(templete_node));
	
	anode->data = aobject_p;
	mself->list->add_node_next(mself->list, anode);
	return mself->list->count;
}

static void* _get(void* self,int index)
{
	ObjectsPool* mself = (ObjectsPool*)self;
	struct node* iter = mself->list->head_p;
	int i;
	for(i=0;i<index;i++){
		iter = iter->next;
	}
	return iter->data;
}

static void _destory(void* self)
{
	ObjectsPool* mself = (ObjectsPool*)self;
	free(mself->list);
}

static ObjectsPool classobj;
static LinkList* list;
ObjectsPool* ObjectsPool_init(MemAllocator* allocator)
{
	//data
	list = LinkList_init();
	classobj.list = (LinkList*)allocator->alloc(allocator, list);
	//methods
	classobj.put = _put;
	classobj.get = _get;
	//mem allocation
	ObjectsPool* instance = (ObjectsPool*)allocator->alloc(allocator, &classobj);
	return instance;
}