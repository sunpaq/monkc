#include <string.h>
#include "MCArray.h"

initer(MCArray){
	obj->count = 0;
	obj->size = 0;
	obj->indexLast = 0;
	obj->buff = nil;
	return obj;
}

loader(MCArray)
{
	binding(MCArray, MCArray*, initWithSize, int size);
	binding(MCArray, MCArray*, addItem, void* item);
	binding(MCArray, MCArray*, addItemToIndex, void* item, int index);

	binding(MCArray, MCArray*, removeLastItem, xxx);
	binding(MCArray, MCArray*, removeItem, void* item);
	binding(MCArray, MCArray*, removeItemByIndex, int index);
	binding(MCArray, MCArray*, clear, xxx);

	binding(MCArray, void*, getItemByIndex, int index);
	binding(MCArray, void, visiteEachBy, mc_message visitorFunction);
	binding(MCArray, void, visiteEachWithData, lamdafunc visitorFunction, void* data);
	return claz;
}

method(MCArray, MCArray*, initWithSize, int size)
{
	obj->count = 0;
	obj->size = size;
	obj->indexLast = 0;
	obj->buff = (void*(*)[])calloc(size, sizeof(void*));
	return obj;
}

static void expand_array(MCArray* obj)
{
	if(obj->size == 0){
		obj->size = 10;
		call(obj, MCArray, initWithSize, obj->size);
	}else{
		obj->size = (obj->size) * 2;//double
		void* (*newbuff)[] = (void*(*)[])calloc(obj->size, sizeof(void*));
		memcpy(*newbuff, *(obj->buff), obj->size * sizeof(void*));
		free(obj->buff);
		obj->buff = newbuff;
		//printf("[MCArray] expand to (%d)\n", obj->size);
	}
}

static void insert_item(MCArray* obj, void* item)
{
	(*(obj->buff))[obj->indexLast++] = item;
	obj->count++;
}

static void delete_item(MCArray* obj, int index)
{
	if(index < 0) return;
	if(index > obj->indexLast) return;
	(*(obj->buff))[index] = nil;
	if(index==obj->indexLast)
		obj->indexLast--;
	obj->count--;
}

method(MCArray, MCArray*, addItem, void* item)
{
	if(obj->indexLast >= obj->size){
		expand_array(obj);
	}
	insert_item(obj, item);
	return obj;
}

method(MCArray, MCArray*, addItemToIndex, void* item, int index)
{
	if(index >= obj->size){
		expand_array(obj);
	}
	insert_item(obj, item);
	return obj;
}

method(MCArray, MCArray*, removeLastItem, xxx)
{
	delete_item(obj, obj->indexLast);
	return obj;
}

static void visitor(_lamda, void* eachitem, int index)
{
	delete_item(obj, index);
}

method(MCArray, MCArray*, removeItem, void* item)
{
	call(obj, MCArray, visiteEachBy, lamda(visitor));
	return obj;
}

method(MCArray, MCArray*, removeItemByIndex, int index)
{
	delete_item(obj, index);
	return obj;
}

method(MCArray, MCArray*, clear, xxx)
{
	free(obj->buff);
	return call(obj, MCArray, initWithSize, 10);
}

method(MCArray, void*, getItemByIndex, int index)
{
	return deref(obj->buff)[index];
}

//just an example
void example_visitor1(_lamda, void* item, int index){}
void example_visitor2(_lamda, void* item, int index, void* data){}

method(MCArray, void, visiteEachBy, lamdafunc visitorFunction)
{
	int i;
	for(i=0; i<(obj->size); i++){
		void* eachItem = deref(obj->buff)[i];
		if(eachItem)
			_push_jump(visitorFunction, eachItem, i);
		//else
			//printf("[MCArray] item(%d) is nil\n", i);
	}
}

method(MCArray, void, visiteEachWithData, lamdafunc visitorFunction, void* data)
{
	int i;
	for(i=0; i<(obj->size); i++){
		void* eachItem = deref(obj->buff)[i];
		if(eachItem)
			_push_jump(visitorFunction, eachItem, i, data);
		//else
			//printf("[MCArray] item(%d) is nil\n", i);
	}
}
