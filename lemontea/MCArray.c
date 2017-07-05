#include <string.h>
#include "MCArray.h"

static void expand_array(MCArray* obj)
{
    if(obj->maxcount == 0){
        obj->maxcount = 10;
        MCArray_initWithMaxCount(obj, obj->maxcount);
    }else{
        obj->maxcount = (obj->maxcount) * 2;//double
        MCGeneric* newbuff = (MCGeneric*)malloc(sizeof(MCGeneric) * obj->maxcount);
        memcpy(newbuff, obj->buff, obj->maxcount * sizeof(MCGeneric));
        free(obj->buff);
        obj->buff = newbuff;
        //printf("[MCArray] expand to (%d)\n", obj->size);
    }
}

static void insert_item(MCArray* obj, MCGeneric item)
{
    obj->buff[obj->indexLast++] = item;
    obj->count++;
}

static void delete_item(MCArray* obj, size_t index)
{
    if(index > obj->indexLast) return;
    obj->buff[index] = (MCGeneric){.mcvoidptr=null};
    if(index==obj->indexLast)
        obj->indexLast--;
    obj->count--;
}

oninit(MCArray)
{
    if (init(MCObject)) {
        obj->count = 0;
        obj->maxcount = 0;
        obj->indexLast = 0;
        obj->buff = null;
        return obj;
    }else{
        return null;
    }
}

method(MCArray, MCArray*, initWithMaxCount, size_t max)
{
	obj->count = 0;
	obj->maxcount = max;
	obj->indexLast = 0;
    obj->buff = (MCGeneric*)malloc(sizeof(MCGeneric) * max);
	return obj;
}

method(MCArray, void, bye, voida)
{
    if (obj->buff != null) {
        free(obj->buff);
    }
    superbye(MCObject);
}

method(MCArray, MCArray*, clear, voida)
{
    free(obj->buff);
    return MCArray_initWithMaxCount(obj, 10);
}

method(MCArray, MCArray*, addItem, MCGeneric item)
{
	if(obj->indexLast >= obj->maxcount){
		expand_array(obj);
	}
	insert_item(obj, item);
	return obj;
}

method(MCArray, MCArray*, addItemToIndex, MCGeneric item, size_t index)
{
	if(index >= obj->maxcount){
		expand_array(obj);
	}
	insert_item(obj, item);
	return obj;
}

method(MCArray, MCArray*, removeLastItem, voida)
{
	delete_item(obj, obj->indexLast);
	return obj;
}

method(MCArray, MCArray*, removeItem, MCGeneric* item)
{
    for (int i=0; i<obj->maxcount; i++) {
        if (&obj->buff[i] == item) {
            delete_item(obj, i);
        }
    }
	return obj;
}

method(MCArray, MCArray*, removeItemByIndex, size_t index)
{
	delete_item(obj, index);
	return obj;
}

method(MCArray, MCGeneric*, getItemByIndex, size_t index)
{
	return &obj->buff[index];
}

method(MCArray, void, printAll, const char* delimiter)
{
    for (int i=0; i<obj->count; i++) {
        printf("%.2f%s", obj->buff[i].mcfloat, delimiter);
    }
    printf("\n");
}

onload(MCArray)
{
    if (load(MCObject)) {
        binding(MCArray, void, bye, voida);
        binding(MCArray, MCArray*, initWithMaxCount, size_t max);
        binding(MCArray, MCArray*, addItem, MCGeneric item);
        binding(MCArray, MCArray*, addItemToIndex, MCGeneric item, size_t index);
        binding(MCArray, MCArray*, removeLastItem, voida);
        binding(MCArray, MCArray*, removeItem, MCGeneric* item);
        binding(MCArray, MCArray*, removeItemByIndex, size_t index);
        binding(MCArray, MCArray*, clear, voida);
        binding(MCArray, MCGeneric*, getItemByIndex, size_t index);
        binding(MCArray, void, printAll, const char* delimiter);
        return cla;
    }else{
        return null;
    }
}
