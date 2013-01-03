#ifndef __MCRuntime__
#define __MCRuntime__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

#define ROOT_CLASS_NAME "MCObject"
#define INIT_METHOD_NAME "init"
//max memory useage for class  table is: 4Byte x 1000 = 4KB
//max memory useage for method table is: 4Byte x 500 x 1000 = 2000KB = 2M

//1000 classes 2M    
//100  classes 200KB
//10   classes 20KB

#define MAX_METHOD_PER_CLASS 100
#define MAX_METHOD_NUM (MAX_METHOD_PER_CLASS*5)
#define MAX_CLASS_NUM  1000

typedef char* String;
typedef double Float;
typedef int BOOL;
#define YES 1
#define NO 0
#define xxx void* xxx
#define nil ((void*)0)
#define _FunctionPointer(name) void* (*name)()
#define _FunctionArray(name) void* (*name[MAX_METHOD_NUM])()
//MK: Method Key  MV: Method Value
#define MV(cls, name) cls##_##name
#define MK(value) #value
#define Handle(cls) cls*

//root class
#define _MCObject //we keep this macro blank but insert fileds to every object struct
#define _newline  //just a blank mark for syntex
#define _alloc(cls) (cls*)mc_malloc(sizeof(cls))//private macro, usr should not call this
//meta class, the struct is a node for inherit hierarchy
//enum MCCLASSTYPE { SINGLETON, NORMAL };
typedef struct MCClass_tag
{
	struct MCClass_tag* super;
	int method_count;
	_FunctionArray(method_list);
	char* name;
}MCClass;
//for type cast, every object have the 3 var members
typedef struct {
	MCClass* isa;
	BOOL need_bind_method;
	int ref_count;
}MCObject;
typedef MCObject* id;
id MCObject_init(id const this, char* cmd, xxx);

//for class define
#define class(cls) _newline;\
typedef struct{\
	MCClass* isa;\
	BOOL need_bind_method;\
	int ref_count;\
	_##cls;\
}cls;

#define constructor(cls, ...)       cls* cls##_init(cls* const this, char* cmd, __VA_ARGS__)
#define new(cls, ...)                    cls##_init(_alloc(cls), 0, __VA_ARGS__)
//for method
#define method(cls, name, ...)        id cls##_##name(cls* const this, char* cmd, __VA_ARGS__)
#define call(this, cls, name, ...)       cls##_##name(this, 0, __VA_ARGS__)//call other class method
#define super_init(this, cls, ...)  do{this->need_bind_method=NO;\
									this->isa=nil;\
									cls##_init(this, 0, __VA_ARGS__);\
									this->isa=nil;\
									this->need_bind_method=YES;}while(0)
//for protocol define
#define protocol(cls, name, ...) static id cls##_##name(id const this, char* cmd, __VA_ARGS__)
#define This(cls)      ((cls*)this)
#define Cast(cls, obj) ((cls*)obj)
//runtime parts

//logs
#define SILENT     0
#define ERROR_ONLY 1
#define DEBUG      2
#define VERBOSE    3
int LOG_LEVEL;
void error_log(char* fmt, ...);
void debug_log(char* fmt, ...);
void runtime_log(char* fmt, ...);

BOOL set_class(id const self_in, const char* classname, const char* superclassname);

//MM
void release(id const this);
void retain(id const this);

//method handing
int bind(id const self, char *key, _FunctionPointer(value));
int override(id const self, char *key, _FunctionPointer(value));
BOOL response(id const obj, char *key);
id ff(const id obj, const char *key, ...);
//ff-release, for the fr(New(Class, nil), MK(method), nil)
id fr(const id obj, const char *key, ...);

//make a thread-safe allocator
void* mc_malloc(size_t size);
void  mc_free(void *ptr);

//log colors
static char* LOG_FMT = "%s%s\033[0m";
static char* LOG_COLOR_NONE="\033[0m";
static char* LOG_COLOR_BLACK="\033[0;30m";
static char* LOG_COLOR_DARK_GRAY="\033[1;30m";
static char* LOG_COLOR_BLUE="\033[0;34m";
static char* LOG_COLOR_LIGHT_BLUE="\033[1;34m";
static char* LOG_COLOR_GREEN="\033[0;32m";
static char* LOG_COLOR_LIGHT_GREEN="\033[1;32m";
static char* LOG_COLOR_CYAN="\033[0;36m";
static char* LOG_COLOR_LIGHT_CYAN="\033[1;36m";
static char* LOG_COLOR_RED="\033[0;31m";
static char* LOG_COLOR_LIGHT_RED="\033[1;31m";
static char* LOG_COLOR_PURPLE="\033[0;35m";
static char* LOG_COLOR_LIGHT_PURPLE="\033[1;35m";
static char* LOG_COLOR_BROWN="\033[0;33m";
static char* LOG_COLOR_YELLOW="\033[1;33m";
static char* LOG_COLOR_LIGHT_GRAY="\033[0;37m";
static char* LOG_COLOR_WHITE="\033[1;37m";

#endif
