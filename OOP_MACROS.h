//something strange with _ in connect the para
//so we use ## to connect
//usually ## is used to connect the two para

#ifndef __OOP_MACROS__
#define __OOP_MACROS__

//class define
#define Interface(name) typedef struct _##name{
#define Implement(name) }name;name name##_obj;
#define Constructor(name) name* name##_new(
#define Arg() 
#define End() )
#define Body(body) {body}
#define Finish(name) 
//Global Macros
#define New(name) name##_new( 
#define Bind(class,name) class##_obj.name=name;
#define Set(class,name,value) class##_obj.name=value;
#define ReturnInstance(name) \
	name* instance = (name*)malloc(sizeof(name##_obj));\
	memcpy(instance, &name##_obj, sizeof(name##_obj));\
	return instance;
//methods
#define method static
#define function static
#define var static
#define Function extern
#define Var extern

#define dcl(name) (*name)(void* self
#define	imp(name) name(void* self
#define arg() ,
#define end() )
#define body(body) {CLASS* this = (CLASS*)self;body}
#define call(obj,name) obj->name(obj
//main loop
#define Main(body) int main(int argc, char* argv[]){body}
//basic includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif