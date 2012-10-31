//something strange with _ in connect the para
//so we use ## to connect
//usually ## is used to connect the two para

#ifndef __OOP_MACROS__
#define __OOP_MACROS__

//marks
#define id void*
#define xxx void* __xxx
#define nil ((void*)0)
//instance manipulate
#define call(ins,method,...) ins->method(ins,__VA_ARGS__)
#define new(ins,cls,...) cls* ins=cls##_new(__VA_ARGS__)
//method
#define method(ret,name,...) ret (*name)(void* self,__VA_ARGS__)
#define method_imp(ret,name,...) static ret name(void* self,__VA_ARGS__)
#define this(cls) cls* this = (cls*)self
//friend method
#define friend(ret,name,...) ret (*name)(void* self,__VA_ARGS__)
#define friend_imp(ret,name,...) static ret name(void* self,__VA_ARGS__)
#define friend_borrow(cls,fri,ret,name,...) static ret name(void* self,__VA_ARGS__){\
cls* this = (cls*)self;\
return this->fri->name(__VA_ARGS__);}
//virtual method
#define virtual(ret,name,...) ret (*name)(void* self,__VA_ARGS__)
#define virtual_imp(ret,name,...) static ret name(void* self,__VA_ARGS__)
//global functions
#define function(ret,name,...) extern ret name(__VA_ARGS__)
#define function_imp(ret,name,...) ret name(__VA_ARGS__)
//class define
#define MCInterface typedef struct{
#define MCInterfaceEnd(name,...) }name;\
name* name##_new(__VA_ARGS__);
#define MCImplement 
#define MCImplementEnd(name,...) name classobj;\
name* name##_new(__VA_ARGS__)
#define Bind(method) classobj.method=method
#define Set(var,value) classobj.var=value
#define Return(name) name* __instance = (name*)malloc(sizeof(classobj));\
memcpy(__instance, &classobj, sizeof(classobj));\
return __instance;

//basic includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif