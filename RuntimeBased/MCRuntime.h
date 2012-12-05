#ifndef __MCRuntime__
#define __MCRuntime__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>
//bool: true false
typedef void* id;
typedef double Float;
typedef int BOOL;
#define YES 1
#define NO 0
#define MAX_METHOD_NUM 100

#define xxx void* xxx
#define nil ((void*)0)
#define funcptr(name) id (*name)()
#define funccast(ret, arg) (ret (*)(arg))
#define funcarray(name) id (*name[MAX_METHOD_NUM])(id)

#define Alloc(cls, obj) cls* obj = (cls*)malloc(sizeof(cls))
#define Init(cls, obj, ...) cls##_##init(obj, 0, __VA_ARGS__)
#define New(cls, obj, ...) cls* obj = (cls*)malloc(sizeof(cls));cls##_##init(obj, 0, __VA_ARGS__)

#define MCInterface(cls, super) typedef struct{ MCClass* isa; int ref_count; id super_instance;
#define MCInterfaceEnd(cls, cmd, ...) }cls;extern id cls##_init(void* const self, int cmd, __VA_ARGS__)

#define protocol(cls, name, ...) //extern id cls##_##name(void* const self, int cmd, __VA_ARGS__)
#define protocol_imp(cls, name, ...) static id cls##_##name(void* const self, int cmd, __VA_ARGS__)
#define method(cls, name, ...) extern id cls##_##name(void* const self, int cmd, __VA_ARGS__)
#define method_imp(cls, name, ...) id cls##_##name(void* const self, int cmd, __VA_ARGS__)

#define This(cls) cls* this = (cls*) self
#define Pull(type, name) type name = (type) this->name
#define Push(name) this->name = name
#define MA(cls, name) cls##_##name
#define MT(value) #value
#define STR(value) #value
//meta class, the struct is a node for inherit hierarchy
typedef struct MCClass_tag
{
	struct MCClass_tag* super;
	int method_index;
	int cached_index;
	char* cached_method_tag;
	funcptr(cached_method);
	funcarray(method_list);
	char* name;
}MCClass;
//for type cast, every object have the 3 var members
typedef struct {
	MCClass* isa;
	int ref_count;
	id super_instance;
}MCObject;
#define MCCast(cls) typedef struct{ MCClass* isa; int ref_count; id super_instance;
#define MCCastEnd(cls) }cls;

//pre declear a class
MCInterface(MCContext, root);
	int argc;
	char** argv;
MCInterfaceEnd(MCContext, init, int argc, char** argv);
method(MCContext, bye, xxx);
method(MCContext, dump, xxx);
method(MCContext, getPara, int index);
method(MCContext, paraEqual, int index, char* para);
method(MCContext, havePara, char* para);

int MCRuntime_runloop(MCContext* context);

void setting_start(id const self_in, char* name_in);
void set_super(id const child_in, id const father_in);

/* array-based API */
int bind_method(id const self_in, funcptr(mptr));
BOOL is_response(id const self_in, funcptr(name));
id call(id const self_in, funcptr(name), ...);

/* hashtable-based API */
int bind(id const self_in, char *key, funcptr(mptr));
BOOL response(id const self_in, char *key);
id ff(id const self_in, char *key, ...);

//void release(id const instance, funcptr(bye_callback));
void release(id const instance);
void retain(id const instance);

unsigned hash(char *s);

#endif
