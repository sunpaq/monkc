//something strange with _ in connect the para
//so we use ## to connect
//usually ## is used to connect the two para

#ifndef __OOP_MACROS__
#define __OOP_MACROS__

//interface
#define Interface(name) typedef struct _##name{
#define IEnd(name,...) }name;name name##_obj;name* name##_new(__VA_ARGS__);
//implement
#define Implement(name)
#define MEnd(name)
//constructor
#define Constructor(name) name* name##_new
#define Arg(...) (__VA_ARGS__)
#define Body(body) {body
#define CEnd(name) \
	name* instance = (name*)malloc(sizeof(name##_obj));\
	memcpy(instance, &name##_obj, sizeof(name##_obj));\
	return instance;}
//use at runntime
#define nil ((void*)0)
#define Main(body) int main(int argc, char* argv[]){body return 0;}
#define call(obj,name,...) obj->name(obj,__VA_ARGS__);
#define new(class,obj,...) class* obj = class##_new(__VA_ARGS__);obj->onnew(obj,((void*)0))
#define bye(obj) obj->onbye(obj,((void*)0));free(obj)
//use in constructor
#define Bind(cls,name) cls##_obj.name=name;
#define Set(cls,name,value) cls##_obj.name=value;
//marks for file scope
#define method static
#define function static
#define var static
//marks for global scope
#define Function 
#define Var 
//methods
#define dcl(name) (*name)
#define	imp(name) name
#define arg(...) (void* self, __VA_ARGS__)
#define body(body) {CLASS* this = (CLASS*)self;body}
//argument place holder
#define tail void* all_the_method_must_have_at_least_one_arg

//basic includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif