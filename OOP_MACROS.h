#ifndef __OOP_MACROS__
#define __OOP_MACROS__
//marks
#define id void*
#define xxx void* __xxx
#define nil ((void*)0)
//useage
#define call(ins,method,...) ins->method(ins,__VA_ARGS__)
#define new(ins,cls,...) cls* ins=cls##_new(__VA_ARGS__)
//this pointer
#define pull(type,var) type var = this->var
#define push(var) this->var = var
#define cast(obj,type,old) type* obj = (type*)old
//method
#define method(ret,name,...) ret (*name)(void* self,__VA_ARGS__)
#define method_imp(ret,name,...) static ret name(void* self,__VA_ARGS__)
#define body(lines) {CLASS* this=(CLASS*)self;lines}
//global functions
// #define function(ret,name,...) extern ret name(__VA_ARGS__)
// #define function_imp(ret,name,...) ret name(__VA_ARGS__)
//define class
#define MCInterface(name) typedef struct name##_tag{
#define MCInterfaceEnd(name,...) }name;\
name* name##_new(__VA_ARGS__);
#define MCImplement(name)
#define MCImplementEnd(name,...) name classobj;\
name* name##_new(__VA_ARGS__)
#define Body(lines) {lines;\
CLASS* __instance = (CLASS*)malloc(sizeof(classobj));\
memcpy(__instance, &classobj, sizeof(classobj));\
return __instance;}
#define Bind(method) classobj.method=method
#define Set(var,value) classobj.var=value
//must include libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#endif