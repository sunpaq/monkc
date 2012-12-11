#ifndef __MCRuntime__
#define __MCRuntime__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
typedef void* id;
typedef double Float;
typedef int BOOL;
#define YES 1
#define NO 0
#define MAX_METHOD_NUM 100
#define MAX_CLASS_NUM 1000

#define xxx void* xxx
#define nil ((void*)0)
#define funcptr(name) id (*name)()
#define funcarray(name) id (*name[MAX_METHOD_NUM])(id)
//meta class, the struct is a node for inherit hierarchy
typedef struct MCClass_tag
{
	struct MCClass_tag* super;
	int method_count;
	funcarray(method_list);
	char* name;
}MCClass;
//for type cast, every object have the 3 var members
typedef struct {
	MCClass* isa;
	int ref_count;
	id data;
}MCObject;
//for class define
#define MCInterface(cls, super) typedef struct{ MCClass* isa; int ref_count; id data;
#define MCInterfaceEnd(cls, cmd, ...) }cls;extern id cls##_init(void* const self, char* cmd, __VA_ARGS__)
#define method(cls, name, ...) extern id cls##_##name(void* const self, char* cmd, __VA_ARGS__)
#define method_imp(cls, name, ...) id cls##_##name(void* const self, char* cmd, __VA_ARGS__)
#define This(cls) cls* this = (cls*) self
//MA: Method Address  MT: Method Tag
#define MA(cls, name) cls##_##name
#define MT(value) #value
#define New(cls, obj, ...) error_log("----New: %s\n",#cls);cls* obj = (cls*)malloc(sizeof(cls));cls##_##init(obj, 0, __VA_ARGS__)
#define SuperInit(cls, obj, ...) cls##_##init(obj, 0, __VA_ARGS__)
//for protocol define
#define MCCast(cls) typedef struct{ MCClass* isa; int ref_count; id data;
#define MCCastEnd(cls) }cls;
#define protocol(cls, name, ...) //extern id cls##_##name(void* const self, char* cmd, __VA_ARGS__)
#define protocol_imp(cls, name, ...) static id cls##_##name(void* const self, char* cmd, __VA_ARGS__)

//runtime parts

//logs
#define SILENT     0
#define ERROR_ONLY 1
#define DEBUG      2
#define VERBOSE    3
extern int LOG_LEVEL;
void error_log(char* fmt, ...);
void debug_log(char* fmt, ...);
void runtime_log(char* fmt, ...);

//class loading
MCClass* load_class(const char* name_in, const char* super_class);
MCClass* get_class(const char* name_in);
BOOL set_class(MCObject* const self_in, const char* classname, const char* superclassname);

//MM
void release(id const instance);
void retain(id const instance);

//method handing
int bind(id const self_in, char *key, funcptr(mptr));
int override(id const self_in, char *key, funcptr(mptr));
BOOL response(id const self_in, char *key);
id ff(id const self_in, char *key, ...);

#endif
