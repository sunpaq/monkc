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
	mc_block* tail;
}mc_blockpool;

//meta class, the struct is a node for inherit hierarchy
typedef struct mc_class_struct
{
	size_t objsize;
	mc_hashtable* table;
	mc_blockpool* free_pool;
	mc_blockpool* used_pool;
	mc_hashitem* item;
}mc_class;

//for type cast, every object have the 3 var members
typedef struct mc_object_struct
{
	struct mc_object_struct* super;
	mc_class* isa;
	mc_block* block;
	int ref_count;
	mc_class* saved_isa;
	mc_class* mode;
}mc_object;
typedef mc_object* mo;

#define monkc(cls) \
typedef struct cls##_struct{\
	struct mc_object_struct* super;\
	mc_class* isa;\
	mc_block* block;\
	int ref_count;\
	mc_class* saved_isa;\
	mc_class* mode;\

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
#define initer(cls)						 cls* cls##_init(cls* const this)

//method binding
#define binding(cls, type, met, ...)  		_binding(class, S(met), A_B(cls, met))
#define override(cls, type, met, ...) 		_override(class, S(met), A_B(cls, met))
#define hinding(cls, type, met, hash, ...)	_binding_h(class, S(met), A_B(cls, met), hash)
#define hverride(cls, type, met, hash, ...) _override_h(class, S(met), A_B(cls, met), hash)
#define method(cls, type, name, ...) 	type cls##_##name(cls* volatile this, volatile void* entry, __VA_ARGS__)
#define protocol(pro, type, name, ...)  static type pro##_##name(mo volatile this, volatile void* entry, __VA_ARGS__)
#define cast(cls, obj) 					((cls*)obj)

//for create object
#define new(cls)						(cls*)_new(_alloc(S(cls), sizeof(cls), (loaderFP)cls##_load), (initerFP)cls##_init)
#define hew(cls, hash)					(cls*)_new(_alloc_h(S(cls), sizeof(cls), cls##_load, hash), cls##_init)
#define new_category(ori, cat)			(ori*)_new_category(_alloc(S(ori), sizeof(ori), ori##_load), ori##_init, cat##_load, cat##_init)
#define hew_category(ori, hash, cat)	(ori*)_new_category(_alloc_h(S(ori), sizeof(ori), ori##_load, hash), ori##_init, cat##_load, cat##_init)
#define clear(cls)  					_clear(S(cls), sizeof(cls), cls##_load)
#define hlear(cls, hash)  				_clear_h(S(cls), sizeof(cls), cls##_load, hash)
#define info(cls)                  		_info(S(cls), sizeof(cls), cls##_load)
#define hnfo(cls, hash)                 _info_h(S(cls), sizeof(cls), cls##_load, hash)

//for call method
#define call(this, cls, name, ...)      cls##_##name(this, cls##_##name, __VA_ARGS__)//call other class method
#define response_to(obj, met) 			_response_to(obj, S(met))
#define hesponse_to(obj, met, hash) 	_response_to_h(obj, S(met), hash)
#define ff(obj, met, ...)				_push_jump(_response_to((mo)obj, S(met)), __VA_ARGS__)
#define fh(obj, met, hash, ...)			_push_jump(_response_to_h(obj, S(met), hash), __VA_ARGS__)
#define fs(obj, met, ...)				_push_jump(_self_response_to(obj, S(met)), __VA_ARGS__)
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
mo _new(mo const this, initerFP initer);
mo _new_category(mo const this, initerFP initer, loaderFP loader_cat, initerFP initer_cat);
//object mode change
void _shift(mo const obj, const char* modename, size_t objsize, loaderFP loader);
void _shift_back(mo const obj);
//mm
#define REFCOUNT_NO_MM 	-1
#define REFCOUNT_ERR 	-100
void _recycle(mo const this);
void _release(mo const this);
mo _retain(mo const this);
#define recycle(obj) _recycle((mo)obj)
#define release(obj) _release((mo)obj)
#define retain(obj)  _retain((mo)obj)

//functions
mc_class* alloc_mc_class();
mc_class* init_mc_class(mc_class* const aclass, const size_t objsize);
mc_class* new_mc_class(const size_t objsize);
char* nameof(mc_object* const aobject);
char* nameofc(mc_class* const aclass);
#define deref(x) (*(x))
#define addrof(x) (&(x))

#include "Log.h"
#include "Lock.h"
#include "Key.h"
#include "Vectors.h"
#include "HashTable.h"
#include "Messaging.h"
#include "ObjectManage.h"


#endif
