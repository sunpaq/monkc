#ifndef __MCRuntime__
#define __MCRuntime__

/* Mocha use many C99 standard features, make sure your compiler and platform support C99 standard */
//#pragma warning(disable:3)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

#define ROOT_CLASS_NAME "MCObject"
#define INIT_METHOD_NAME "init"
//max memory useage for class  table is: 4Byte x 1000 = 4KB
//max memory useage for method table is: 4Byte x 1000 x 1000 = 4000KB = 4M

//1000 classes 2M    
//100  classes 200KB
//10   classes 20KB

#ifndef MAX_METHOD_NUM
#define MAX_METHOD_NUM 1000
#endif
#ifndef MAX_CLASS_NUM
#define MAX_CLASS_NUM  1000
#endif
typedef char* CString;
typedef double Float;
typedef int BOOL;
#define YES 1
#define NO 0
typedef int RES;
#define SUCCESS 0
#define ERROR -1

#define xxx void* xxx
#define nil ((void*)0)
#define _FunctionPointer(name) void (*name)()//no argument means you can pass anything in C!
#define _FunctionArray(name) void (*name[MAX_METHOD_NUM])()
//MK: Method Key  MV: Method Value
#define MV(cls, name) cls##_##name
#define MK(value) _hash(#value)
#define CK(value) _chash(#value) 
#define Handle(cls) cls*

//root class
#define _MCObject //we keep this macro blank but insert fileds to every object struct
#define _newline  //just a blank mark for syntex
#define _alloc(cls) (cls*)mc_malloc(sizeof(cls))//private macro, usr should not call this
#define _alloc_clear(cls) (cls*)mc_calloc(sizeof(cls))//private macro, usr should not call this
#define _alloc_onstack(cls) (cls*)mc_alloca(sizeof(cls))//private macro, usr should not call this

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
id MCObject_init(id const this, unsigned hashkey, xxx);

//for class define
#define class(cls) _newline;\
typedef struct {\
	MCClass* isa;\
	BOOL need_bind_method;\
	int ref_count;\
	_##cls;\
}cls;
#define class_begin(cls) _newline;\
typedef struct {\
	MCClass* isa;\
	BOOL need_bind_method;\
	int ref_count;\
	_##cls;\
	struct {
#define class_end(cls) }private;}cls;

#define constructor(cls, ...)       cls* cls##_init(cls* const this, unsigned hashkey, __VA_ARGS__)
#define new(cls, ...)                    cls##_init(_alloc(cls), 0, __VA_ARGS__)
#define new_clear(cls, ...)              cls##_init(_alloc_clear(cls), 0, __VA_ARGS__)
#define new_onstack(cls, ...)            cls##_init(_alloc_onstack(cls), 0, __VA_ARGS__)

//for method
#define returns(type)
#define method(cls, name, ...)       void* cls##_##name(cls* const this, unsigned hashkey, __VA_ARGS__)
#define moption(cls, opt, name, ...) void* opt##_##name(cls* const this, unsigned hashkey, __VA_ARGS__)
#define call(this, cls, name, ...)       cls##_##name(this, 0, __VA_ARGS__)//call other class method
#define super_init(this, cls, ...)  do{this->need_bind_method=NO;\
									cls##_init(this, 0, __VA_ARGS__);\
									this->need_bind_method=YES;}while(0)
#define link_class(cls, super, ...) super_init(this, super, __VA_ARGS__);\
									if(set_class(this, #cls, #super))
#define have_method(cls, met, ...)  do{bind_method(this, MK(met), MV(cls, met));\
							  			runtime_log("%s: [%d]%s\n", #cls, _hash(#met), #met);\
							  		}while(0)
#define preload(cls, ...) release(new(cls, __VA_ARGS__))
//for protocol define
#define protocol(cls, name, ...)  static id cls##_##name(id const this, unsigned hashkey, __VA_ARGS__)
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

unsigned _hash(const char *s);
unsigned _chash(const char *s);

BOOL set_class(id const self_in, const char* classname, const char* superclassname);

//MM
void release(id const this);
void retain(id const this);
void _relnil(MCObject** const this);
#define relnil(obj) _relnil(&obj)

//method handling
unsigned bind_method(id const self, unsigned hashkey, _FunctionPointer(value));//the <sys/socket> have function called "bind"
unsigned override(id const self, unsigned hashkey, _FunctionPointer(value));
BOOL response(id const obj, unsigned hashkey);
id ff(id const obj, const unsigned hashkey, ...);
//ff-release, for the fr(new(Class, nil), MK(method), nil)
//warning: do not fr() the singleton class, use the SClass_getInstance() and SClass_releaseInstance()
id fr(id const obj, const unsigned hashkey, ...);

//make a thread-safe allocator
void* mc_malloc(size_t size);
void* mc_calloc(size_t size);
void* mc_alloca(size_t size);
void* mc_realloc(void* ptr, size_t size);
void  mc_free(void *ptr);

//language context
void mc_init();
void mc_end();

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