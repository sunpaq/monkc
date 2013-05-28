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

//max memory useage for class  table is: 4Byte x 4000 = 16KB
//max memory useage for method table is: 4Byte x 4000 x 1000 = 16000KB = 16M

//1000 classes 16M    
//100  classes 1.6M
//10   classes 160KB

//MAX_METHOD_NUM set to 4 time of the space needed
//10level x 100 x 4 = 4000

#ifndef MAX_KEY_CHARS
#define MAX_KEY_CHARS 100
#endif

typedef int BOOL;
#define YES 1
#define NO 0
typedef int RES;
#define SUCCESS 0
#define ERROR -1

#define xxx void* xxx
#define nil ((void*)0)
#define S(value) #value
#define A_B(a, b) a##_##b

typedef struct mc_hashitem_struct
{
	struct mc_hashitem_struct* next;
	unsigned hash;
	unsigned index;
	unsigned level;
	void* value;
	char key[MAX_KEY_CHARS];
}mc_hashitem;

typedef struct mc_hashtable_struct
{
	int lock;
	unsigned level;
	unsigned count;
	mc_hashitem* items[];
}mc_hashtable;

typedef struct mc_block_struct
{
	struct mc_block_struct* next;
	void* data;
}mc_block;

typedef struct mc_blockpool_struct
{
	int lock;
	mc_block* head;
	mc_block* first;
	mc_block* tail;
}mc_blockpool;

//meta class, the struct is a node for inherit hierarchy
typedef struct mc_class_struct
{
	size_t objsize;
	mc_hashtable* table;
	mc_blockpool* pool;
	mc_hashitem* item;
}mc_class;

//for type cast, every object have the 3 var members
typedef struct mc_object_struct
{
	int ref_count;
	mc_class* isa;
	mc_class* saved_isa;
	mc_class* mode;
	mc_block* block;
	struct mc_object_struct* super;
}mc_object;
typedef mc_object* id;

#define class(cls) \
typedef struct cls##_struct{\
	int ref_count;\
	mc_class* isa;\
	mc_class* saved_isa;\
	mc_class* mode;\
	mc_block* block;\
	struct mc_object_struct* super;

#define end(cls) }cls;\
mc_class* cls##_load(mc_class* const class);\
cls* cls##_init(cls* const this);

#define implements(protocol) 
#define extends(super) 

//callback function pointer types
typedef mc_class* (*loaderFP)(mc_class*);
typedef mc_object* (*initerFP)(mc_object*);

//callbacks
#define loader(cls)					mc_class* cls##_load(mc_class* const class)
#define initer(cls)						cls* cls##_init(cls* const this)

//callback caller
#define load(cls)					_load(S(cls), sizeof(cls), cls##_load)
#define init(obj, cls)			    cls##_init(obj)

//method binding
#define binding(cls, met, ...)  	_binding(class, S(met), A_B(cls, met))
#define override(cls, met, ...) 	_override(class, S(met), A_B(cls, met))
#define method(cls, name, ...) 		void* cls##_##name(cls* const this, const void* entry, __VA_ARGS__)
#define protocol(pro, name, ...)  	static void* pro##_##name(id const this, const void* entry, __VA_ARGS__)
#define cast(cls, obj) 				((cls*)obj)
#define returns(type)

//for create object
#define new(cls)					_new((cls*)_alloc(S(cls), sizeof(cls), cls##_load), cls##_init)
#define new_category(ori, cat)		_new_category((ori*)_alloc(S(ori), sizeof(ori), ori##_load), ori##_init, cat##_load, cat##_init)
#define clear(cls)  				_clear(S(cls), sizeof(cls), cls##_load)

//for call method
#define call(this, cls, name, ...)      cls##_##name(this, cls##_##name, __VA_ARGS__)//call other class method
#define response_to(obj, met) 			_response_to(obj, S(met))
#define ff(obj, met, ...)				_push_jump(_response_to(obj, S(met)), __VA_ARGS__)
#define shift(obj, mode)				_shift(obj, S(mode), sizeof(mode), mode##_load)
#define shift_back(obj)					_shift_back(obj)

//global
void mc_init();
void mc_end();
void trylock_global_classtable();
void unlock_global_classtable();
//binding method api
unsigned _binding(mc_class* const aclass, const char* methodname, void* value);
unsigned _binding_h(mc_class* const aclass, const char* methodname, void* value, unsigned hashval);
unsigned _override(mc_class* const aclass, const char* methodname, void* value);
unsigned _override_h(mc_class* const aclass, const char* methodname, void* value, unsigned hashval);
//class load
mc_class* _load(const char* name, size_t objsize, loaderFP loader);
mc_class* _load_h(const char* name, size_t objsize, loaderFP loader, unsigned hashval);
//object create
id _new(id const this, initerFP initer);
id _new_category(id const this, initerFP initer, loaderFP loader_cat, initerFP initer_cat);
//object mode change
void _shift(id const obj, const char* modename, size_t objsize, loaderFP loader);
void _shift_back(id const obj);
//mm
#define REFCOUNT_NO_MM 		-1
#define REFCOUNT_ANONY_OBJ 	-100
void release(mc_object** const this_p);
mc_object* retain(mc_object* const this);

//functions
inline mc_class* alloc_mc_class();
mc_class* init_mc_class(mc_class* const aclass, const size_t objsize);
mc_class* new_mc_class(const size_t objsize);
char* nameof(mc_object* const aobject);
char* nameofc(mc_class* const aclass);

#include "Log.h"
#include "HashTable.h"
#include "Lock.h"
#include "Messaging.h"
#include "ObjectManage.h"
#include "String.h"
#include "Vectors.h"

#endif
