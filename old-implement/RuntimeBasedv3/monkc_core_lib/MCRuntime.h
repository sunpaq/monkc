/*
Copyright (c) <2013>, <Sun Yuli>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <Monk-C> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __MCRuntime__
#define __MCRuntime__

/* Mocha use many C99 standard features, make sure your compiler and platform support C99 standard */
//#pragma warning(disable:3)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "Log.h"
#include "Vectors.h"

//max memory useage for class  table is: 4Byte x 1000 = 4KB
//max memory useage for method table is: 4Byte x 1000 x 1000 = 4000KB = 4M

//1000 classes 2M    
//100  classes 200KB
//10   classes 20KB

#ifndef MAX_METHOD_NAME_CHAR_NUM
#define MAX_METHOD_NAME_CHAR_NUM 100
#endif
#ifndef MAX_METHOD_NUM
#define MAX_METHOD_NUM 1000
#endif
#ifndef MAX_CLASS_NUM
#define MAX_CLASS_NUM  1000
#endif
#ifndef ANONY_POOL_SIZE
#define ANONY_POOL_SIZE 100
#endif

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
typedef struct MCMethod_struct
{
	_FunctionPointer(addr);
	char name[MAX_METHOD_NAME_CHAR_NUM];
}MCMethod;
#define _MethodArray(name) MCMethod* name[MAX_METHOD_NUM]
//MK: Method Key  MV: Method Value CK: Class Key
#define MV(cls, name) cls##_##name
//#define MK(value) _hash(#value)
//#define CK(value) _chash(#value)
#define MK(value) #value
#define CK(value) #value

//root class
#define _MCObject //we keep this macro blank but insert fileds to every object struct
#define _newline  //just a blank mark for syntex
#define _alloc(cls) (cls*)mc_malloc(sizeof(cls))//private macro, usr should not call this
#define _alloc_clear(cls) (cls*)mc_calloc(sizeof(cls))//private macro, usr should not call this
#define _alloc_onstack(cls) (cls*)alloca(sizeof(cls))//private macro, usr should not call this
#define _alloc_anony(cls) (cls*)mc_malloc_anony(sizeof(cls))//private macro, usr should not call this

//meta class, the struct is a node for inherit hierarchy
typedef struct MCClass_struct
{
	struct MCClass_struct* super;
	int method_count;
	//_FunctionArray(method_list);
	_MethodArray(method_list);
	BOOL is_binding_flag;
	char* name;
}MCClass;
//for type cast, every object have the 3 var members
typedef struct {
	MCClass* isa;
	BOOL need_bind_method;
	int ref_count;
}MCObject;
typedef MCObject* id;

//for class define
#define class(cls) _newline;\
typedef struct cls##_struct{\
	MCClass* isa;\
	BOOL need_bind_method;\
	int ref_count;\
	_##cls;\
}cls;
#define class_begin(cls) _newline;\
typedef struct cls##_struct{\
	MCClass* isa;\
	BOOL need_bind_method;\
	int ref_count;\
	_##cls;\
	struct {
#define class_end(cls) }private;}cls;
#define constructor(cls, ...)		cls* cls##_init(cls* const this, const char* methodname, __VA_ARGS__)
#define super_init(this, cls, ...)  do{this->need_bind_method=NO;cls##_init(this, "init", __VA_ARGS__);\
									this->need_bind_method=YES;}while(0)
#define link_class(cls, super, ...) super_init(this, super, __VA_ARGS__);\
									if(set_class(this, #cls, #super))
#define binding(cls, met, ...)  	_binding(this, MK(met), MV(cls, met))
#define override(cls, met, ...) 	_override(this, MK(met), MV(cls, met))
#define method(cls, name, ...) 			void* cls##_##name(cls* const this, const char* methodname, __VA_ARGS__)
#define moption(cls, opt, name, ...) 	void* opt##_##name(cls* const this, const char* methodname, __VA_ARGS__)
#define returns(type)

//for create object
#define new(cls, ...)                    cls##_init(_alloc(cls), "init", __VA_ARGS__)
#define new_clear(cls, ...)              cls##_init(_alloc_clear(cls), "init", __VA_ARGS__)
#define new_onstack(cls, ...)            cls##_init(_alloc_onstack(cls), "init", __VA_ARGS__)
#define new_anony(cls, ...)         	 cls##_init(_alloc_anony(cls), "init", __VA_ARGS__)
#define preload(cls, ...) 				 release(new(cls, __VA_ARGS__))

//for call method
#define ff(obj, met, ...) 				_ff(obj, MK(met), __VA_ARGS__)
#define call(this, cls, name, ...)      cls##_##name(this, #name, __VA_ARGS__)//call other class method
#define response_to(obj, met) 			_response_to(obj, MK(met))

//for protocol define
#define protocol(cls, name, ...)  	static id cls##_##name(id const this, const char* methodname, __VA_ARGS__)
#define This(cls)      				((cls*)this)
#define Cast(cls, obj) 				((cls*)obj)

//Classpool
BOOL set_class(id const self_in, const char* classname, const char* superclassname);

//Reference Count
#define REFCOUNT_NO_MM 		-1
#define REFCOUNT_ANONY_OBJ 	-100
#define relnil(obj) _relnil(&obj)
void release(id const this);
void retain(id const this);
void _relnil(MCObject** const this);

//method handling
unsigned _binding(id const self, const char* methodname, _FunctionPointer(value));
unsigned _override(id const self, const char* methodname, _FunctionPointer(value));
void* _response_to(id const obj, const char* methodname);

//make a thread-safe allocator
void* mc_malloc(size_t size);
void* mc_malloc_anony(size_t size);
void* mc_calloc(size_t size);
void* mc_realloc(void* ptr, size_t size);
void  mc_free(void *ptr);

//language context
void mc_init();
void mc_end();

//Root class
id MCObject_init(id const this, const char* methodname, xxx);
void MCObject_doNothing(id const this, const char* methodname, xxx);
void MCObject_whatIsYourClassName(id const this, const char* methodname, xxx);
void MCObject_bye(id this, const char* methodname, xxx);

//hash
unsigned _hash(const char *s);
unsigned _chash(const char *s);

//lock free
//void mc_compareAndSwapInner(int* addr, int newval);
int mc_compareAndSwap(int* addr, int oldval, int newval);
void mc_copyName(MCMethod* method, const char* name);
int mc_compareName(MCMethod* method, const char* name);

#endif