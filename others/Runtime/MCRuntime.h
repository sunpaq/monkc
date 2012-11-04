#ifndef __MCRuntime__
#define __MCRuntime__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_METHOD_NUM 100

#define nil ((void*)0)
#define funcptr(name) id (*name)(id)
#define funcarray(name) id (*name[MAX_METHOD_NUM])(id)

// #define method(class, name)  id class##_##name(id para)
// #define method_anchor(class, name) static id name(id para);\
// 				  id class##_##name(id para){return name(para);}

#define alloc(obj, cls) cls* obj = (cls*)malloc(sizeof(cls))

typedef void* id;
typedef struct MCClass_tag
{
	struct MCClass_tag* super;
	/* methods */
	int method_index;
	funcptr(method_first);
	int method_offset;
	funcarray(method_list);
	int method_boolean[MAX_METHOD_NUM];
}MCClass;

// typedef struct MCObject_tag
// {
// 	MCClass* isa;
// }MCObject;

void bind_start(MCClass* const self, funcptr(mptr1), funcptr(mptr2));
int bind_method(MCClass* const self, funcptr(mptr));
int get_method_index(MCClass* const self, funcptr(name));
bool response_to_method(MCClass* const self, funcptr(name));
void call(MCClass* const self, funcptr(name), id para);

#endif
