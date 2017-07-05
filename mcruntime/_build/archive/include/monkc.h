/*
 Copyright (c) <2013-2016>, <Sun Yuli>
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

//https://github.com/sunpaq/monkc
#ifndef __MCRuntimeVer__
#define __MCRuntimeVer__ 10
//version=20 means 2.0
static inline unsigned monkc_version() {return __MCRuntimeVer__;}

/* Monk-C use many C99 standard features, make sure your compiler and platform support C99 standard */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#ifndef LINE_MAX
#define LINE_MAX 2048
#endif
#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

/* *
 * Configure strict mode:
 * MC_STRICT_MODE=1/0
 * in strict mode if dynamic call a invalid method use ff()
 * exit the process and dump the error message.
 * in normal mode there is a error log only
 * */
#define MC_STRICT_MODE 1
#define NO_RECYCLE 1
#define NO_ATOMIC 1

#ifndef mull
#define mull ((void*)0)
#endif
#define voida void* voidarg
#define S(value) #value
#define SEQ(dest, src) (mc_compare_key(dest, src)==0)
#define A_B(a, b) a##_##b
#define nameof(obj) mc_nameof((mo)obj)
#define nameofc(cls) mc_nameofc(cls)
#define deref(x) (*(x))
#define addrof(x) (&(x))

//in C99,
//inline function need to be have "inline" and "non-inline" version both implement
//static inline not require "non-inline" version
#define MCInline static inline

/**
 * the types can not be used in Monk-C method arguments:
 * (Limitation of C variable arguments method)
 *
 * char/signed  char/unsigned  char              (use int)
 * short/signed short/unsigned short             (use int)
 * short int/signed short int/unsigned short int (use int)
 * float                                         (use double)
 *
 * any int type should larger than int
 * any float type should larger than double
 * */
typedef signed int       MCChar;
typedef signed int       MCShort;
typedef signed int       MCInt;
typedef signed long      MCLong;
typedef signed long long MCLongLong;

typedef unsigned int       MCUChar;
typedef unsigned int       MCUShort;
typedef unsigned int       MCUInt;
typedef unsigned long      MCULong;
typedef unsigned long long MCULongLong;

typedef union {
    double    d;
    long long ll;
} MCDouble;

typedef union {
    float f;
    int   i;
} MCFloat;

typedef MCUInt       MCHash;
typedef size_t       MCSizeT;
typedef void*        MCPtr;

typedef const char*  MCStaticString;
typedef void         (*MCFuncPtr)(void);

typedef int MCBool;
#define MCFalse 0
#define MCTrue 1

#define MCFuncPtr(value) ((MCFuncPtr)value)
#define MCDouble(value)  ((MCDouble)value)
#define MCFloat(value)   ((MCFloat)value)

/*
 Generic Type
 */

struct mc_object_struct;
typedef union {
    MCChar      mcchar;
    MCShort     mcshort;
    MCInt       mcint;
    MCLong      mclong;
    MCLongLong  mclonglong;
    MCUChar     mcuchar;
    MCUShort    mcushort;
    MCUInt      mcuint;
    MCULong     mculong;
    MCULongLong mculonglong;
    MCFloat     mcfloat;
    MCDouble    mcdouble;
    MCHash      mchash;
    MCSizeT     mcsizet;
    MCPtr       mcptr;
    MCFuncPtr   mcfuncptr;
    MCBool      mcbool;
    MCStaticString mcstaticstr;
    struct mc_object_struct *mcobject;
} MCGeneric;

#define MCGenericI(value)  (MCGeneric){.mcint=value}
#define MCGenericU(value)  (MCGeneric){.mcunsigned=value}
#define MCGenericL(value)  (MCGeneric){.mclong=value}
#define MCGenericF(value)  (MCGeneric){.double=value}
#define MCGenericSz(value) (MCGeneric){.mcsizet=value}
#define MCGenericH(value)  (MCGeneric){.mchash=value}
#define MCGenericP(value)  (MCGeneric){.mcptr=value}
#define MCGenericFp(value) (MCGeneric){.mcfuncptr=value}
#define MCGenericB(value)  (MCGeneric){.mcbool=value}
#define MCGenericSS(value) (MCGeneric){.mcstaticstr=value}
#define MCGenericEmpty     (MCGeneric){0}



/*
 Log.h
 */

/* *
 * Configure whether use colored output log
 * some terminal/IDE can not support ANSI color codes
 * (comment out it to avoid strange output strings on some IDE)
 * */
//#define MC_LOG_USE_COLOR
typedef enum {
    MC_SILENT = 0,
    MC_ERROR_ONLY,
    MC_DEBUG,
    MC_VERBOSE
} MCLogType;
extern void MCLogTypeSet(MCLogType type);

#ifdef __ANDROID__
#include <android/log.h>
#define runtime_log(...)       __android_log_print(ANDROID_LOG_VERBOSE, "[monkc]", __VA_ARGS__)
#define debug_log(...)         __android_log_print(ANDROID_LOG_INFO,    "[monkc]", __VA_ARGS__)
#define error_log(...)         __android_log_print(ANDROID_LOG_ERROR,   "[monkc]", __VA_ARGS__)
#define runtime_logt(tag, ...) __android_log_print(ANDROID_LOG_WARN,  tag, __VA_ARGS__)
#define debug_logt(tag, ...)   __android_log_print(ANDROID_LOG_INFO,  tag, __VA_ARGS__)
#define error_logt(tag, ...)   __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)
#else
int printc(const char* fmt, ...);
void error_log(const char* fmt, ...);
void debug_log(const char* fmt, ...);
void runtime_log(const char* fmt, ...);
void error_logt(const char* tag, const char* fmt, ...);
void debug_logt(const char* tag, const char* fmt, ...);
void runtime_logt(const char* tag, const char* fmt, ...);
#endif

/* *
 * Configure hash table size:
 * have 5 levels of size
 * and it can auto expand to next level when some key conflicted
 *
 * Example of memory usage:
 * max memory useage for one class  table is: 4Byte x 10000 = 40KB
 * max memory useage for one method table is: 4Byte x 10000 = 40KB
 * max total memory useage is 4Byte x 10000 x 10000 = 400000KB = 400MB
 * */
typedef enum  {
    MCHashTableLevel1 = 0,
    MCHashTableLevel2,
    MCHashTableLevel3,
    MCHashTableLevel4,
    MCHashTableLevelMax,
    MCHashTableLevelCount
} MCHashTableLevel;
typedef MCUInt MCHashTableSize;
typedef MCUInt MCHashTableIndex;
#define MAX_KEY_CHARS 100
typedef struct mc_hashitem_struct
{
    struct mc_hashitem_struct* next;
    MCHash hash;
    MCHashTableIndex index;
    MCHashTableLevel level;
    MCGeneric value;
    const char* key;
    //char key[MAX_KEY_CHARS+1];
}mc_hashitem;

typedef struct
{
    MCInt lock;
    MCHashTableLevel level;
    MCHashTableSize table_item_count;
    mc_hashitem* items[];
}mc_hashtable;

static MCHashTableSize mc_hashtable_sizes[MCHashTableLevelCount] = {3001, 9001, 17001, 33001, 123001};//100
MCInline MCHashTableSize get_tablesize(const MCHashTableLevel level)
{
    if(level > MCHashTableLevelMax){
        error_log("get_tablesize(level) level>max return use level=max\n");
        return mc_hashtable_sizes[MCHashTableLevelMax];
    }
    return mc_hashtable_sizes[level];
}

MCInline void mc_hashtable_add_item(mc_hashtable* table, MCHashTableIndex index, mc_hashitem* item) { table->items[index] = item; }
MCInline mc_hashitem* mc_hashtable_get_item(mc_hashtable* table, MCHashTableIndex index) { return table->items[index]; }

typedef struct mc_block_struct
{
	struct mc_block_struct* next;
	void* data;
}mc_block;
MCInline mc_block* new_mc_block(void* data)
{
    mc_block* ablock = (mc_block*)malloc(sizeof(mc_block));
    deref(ablock).data = data;
    deref(ablock).next = mull;
    return ablock;
}

typedef struct
{
	MCInt lock;
	mc_block* tail;
}mc_blockpool;
MCInline mc_blockpool* new_mc_blockpool()
{
    mc_blockpool* bpool = (mc_blockpool*)malloc(sizeof(mc_blockpool));
    bpool->lock = 0;
    bpool->tail = mull;
    return bpool;
}
//meta class, the struct is a node for inherit hierarchy
typedef struct
{
    MCSizeT       objsize;
    mc_hashitem*  item;
    mc_blockpool  free_pool;
    mc_blockpool  used_pool;
    mc_hashtable* table; //the hashtable may expand so let it dynamic
}mc_class;
//for type cast, every object have the 3 var members
typedef struct MCObjectStruct
{
    struct MCObjectStruct* nextResponder;
    mc_block* block;
    mc_class* isa;
    mc_class* saved_isa;
    MCInt ref_count;
} MCObject;
typedef MCObject* mo;
#define mo(obj) ((mo)obj)

MCInline mc_class* alloc_mc_class(const MCSizeT objsize)
{
    MCHashTableLevel initlevel = MCHashTableLevel1;
    mc_class* aclass = (mc_class*)malloc(sizeof(mc_class));
    aclass->objsize = objsize;
    //init pool
    aclass->free_pool.lock = 0;
    aclass->free_pool.tail = mull;
    aclass->used_pool.lock = 0;
    aclass->used_pool.tail = mull;
    //init table
    aclass->table = (mc_hashtable*)malloc(sizeof(mc_hashtable) + sizeof(mc_hashitem)*get_tablesize(initlevel));
    aclass->table->lock = 0;
    aclass->table->level = initlevel;
    aclass->table->table_item_count = 0;
    //set all the slot to nil
    for (int i = 0; i < get_tablesize(initlevel); i++)
        (aclass->table->items)[i] = mull;
    return aclass;
}

MCInline void package_by_item(mc_hashitem* aitem_p, mc_class* aclass_p)
{
    (aitem_p)->value.mcptr = aclass_p;
    (aclass_p)->item = aitem_p;
}

MCInline void package_by_block(mc_block* ablock, MCObject* aobject)
{
    deref(ablock).data = aobject;
    deref(aobject).block = ablock;
}

//dynamic class
#define class(cls, supercls, ...)\
typedef struct cls##Struct{\
supercls Super;\
__VA_ARGS__;}cls;\
cls* cls##_init(cls* const obj);\
mc_class* cls##_load(mc_class* const cla);

//macros expand to nothing just a marker
#define including(protocol)

//callback function pointer types
typedef mc_class* (*MCLoaderPointer)(mc_class*);
typedef MCObject* (*MCIniterPointer)(MCObject*);
typedef MCObject* (*MCSetsuperPointer)(MCObject*);

//callbacks
#define onload(cls)					mc_class* cls##_load(mc_class* const cla)
#define oninit(cls)						 cls* cls##_init(cls* const obj)
#define load(supercls)                        supercls##_load(cla)
#define init(supercls)                        supercls##_init((supercls*)obj)
#define preload(cls)                          _load_h(#cls, sizeof(cls), cls##_##load, hash(#cls));

//method binding
#define mixing(type, met, ...)                _binding(cla, S(met), (MCFuncPtr)met)
#define binding(cls, type, met, ...)  		  _binding(cla, S(met), (MCFuncPtr)A_B(cls, met))
#define hinding(cls, type, met, hash, ...)	  _binding_h(cla, S(met), (MCFuncPtr)A_B(cls, met), hash)
#define utility(cls, type, name, ...) 	      type cls##_##name(__VA_ARGS__)
#define method(cls, type, name, ...) 	      type cls##_##name(MCFuncPtr volatile address, cls* volatile obj, __VA_ARGS__)
#define function(type, name, ...)             static type name(MCFuncPtr volatile address, void* volatile any, __VA_ARGS__)

//property
#define computing(type, name)                 type (*name)(void*)
#define compute(type, name)                   static type name(void* any)
#define computed(obj, vname)                  obj->vname(obj)
#define cpt(vname)                            obj->vname(obj)

//variable
#define superof(obj)                          (&obj->Super)
#define sobj                                  (&obj->Super)
#define var(vname)                            (obj->vname)
#define svar(vname)                           (obj->Super.vname)
#define cast(type, obj) 				      ((type)obj)
#define as(cls)                               cls* obj = (cls*)any

//for create object
#define new(cls)						(cls*)_new(mc_alloc(S(cls), sizeof(cls), (MCLoaderPointer)cls##_load), (MCIniterPointer)cls##_init)
#define hew(cls, hash)					(cls*)_new(mc_alloc_h(S(cls), sizeof(cls), cls##_load, hash), cls##_setsuper, cls##_init)
#define clear(cls)  					mc_clear(S(cls), sizeof(cls), cls##_load)
#define hlear(cls, hash)  				mc_clear_h(S(cls), sizeof(cls), cls##_load, hash)
#define info(cls)                  		mc_info(S(cls), sizeof(cls), (MCLoaderPointer)cls##_load)
#define hnfo(cls, hash)                 mc_info_h(S(cls), sizeof(cls), cls##_load, hash)

//for call method
#define response_to(obj, met) 			_response_to((mo)obj, S(met), 2)
#define hesponse_to(obj, met, hash) 	_response_to_h((mo)obj, S(met), hash, 2)
#define _ff(obj, met, ...)              _push_jump(_response_to((mo)obj, met, MC_STRICT_MODE), __VA_ARGS__)//call by string
#define ff(obj, met, ...)				_push_jump(_response_to((mo)obj, S(met), MC_STRICT_MODE), __VA_ARGS__)//send message
#define fh(obj, met, hash, ...)			_push_jump(_response_to_h((mo)obj, S(met), hash, MC_STRICT_MODE), __VA_ARGS__)
#define fs(obj, met, ...)				_push_jump(_self_response_to((mo)obj, S(met)), __VA_ARGS__)

//lock
void trylock_global_classtable();
void unlock_global_classtable();

//binding method api
MCHashTableIndex _binding(mc_class* const aclass, const char* methodname, MCFuncPtr value);
MCHashTableIndex _binding_h(mc_class* const aclass, const char* methodname, MCFuncPtr value, MCHash hashval);

//class load
mc_class* _load(const char* name, MCSizeT objsize, MCLoaderPointer loader);
mc_class* _load_h(const char* name, MCSizeT objsize, MCLoaderPointer loader, MCHash hashval);

//object create
mo _new(mo const obj, MCIniterPointer initer);

//memory management
#define REFCOUNT_NO_MM 	-1
#define REFCOUNT_ERR 	-100
void _recycle(mo const obj);
void _release(mo const obj);
mo _retain(mo const obj);
#define recycle(obj) _recycle((mo)obj)
#define release(obj) _release((mo)obj)
#define retain(obj)  _retain((mo)obj)

//tool for class
extern void _init_class_list();
extern void _clear_class_list();

MCInline const char* mc_nameofc(const mc_class* aclass) {
    if(aclass==mull)
        return "unknown";
    if(aclass->item==mull)
        return "unknown";
    if(aclass->item->key==mull)
        return "unknown";
    return aclass->item->key;
}

MCInline const char* mc_nameof(const MCObject* aobject) {
    if(aobject->isa==mull)
        return "unknown";
    return mc_nameofc(aobject->isa);
}

/*
 Lock.h
 */
MCInt mc_atomic_get_integer(volatile MCInt* target);
void* mc_atomic_get_pointer(volatile void** target);
MCInt mc_atomic_set_integer(volatile MCInt* target, volatile MCInt old, volatile MCInt value);
MCInt mc_atomic_set_pointer(volatile void** target, volatile void* old, volatile void* value);
void mc_trylock(volatile MCInt* lock_p);
void mc_unlock(volatile MCInt* lock_p);

/*
 Key.h
 */

MCInline int mc_compare_key(const char* dest, const char* src) {
    if (dest && src) {
        if (dest[0]!='\0' && src[0]!='\0') {
            return strcmp(dest, src);
        }else if (dest[0]=='\0' && src[0]=='\0') {
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

/*
 HashTable.h
 */

//copy form << The C Programming language >>
//BKDR Hash Function
MCInline MCHash hash(const char *s) {
    //runtime_log("hash(%s) --- ", s);
    MCHash hashval;
    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    //runtime_log("hashval is: %d\n", hashval);
    return hashval;
}

mc_hashitem* new_item(const char* key, MCGeneric value);
mc_hashitem* new_item_h(const char* key, MCGeneric value, const MCHash hashval);
mc_hashtable* new_table(const MCHashTableLevel initlevel);

MCHashTableIndex set_item(mc_hashtable** const table_p,
                mc_hashitem* const item,
                MCBool isOverride, MCBool isFreeValue, const char* classname);
mc_hashitem* get_item_bykey(mc_hashtable* const table_p, const char* key);
mc_hashitem* get_item_byhash(mc_hashtable* const table_p, const MCHash hashval, const char* refkey);
mc_hashitem* get_item_byindex(mc_hashtable* const table_p, const MCHashTableIndex index);

/*
 Messaging.h
 */
typedef struct {
    MCFuncPtr address;
    MCObject* volatile object;
} mc_message;
#define mc_message_arg(Class) void* volatile address, Class* volatile obj
MCInline mc_message make_msg(void* obj, void* address) { return (mc_message){address, (mo)obj}; };

//write by asm
void* _push_jump(mc_message volatile msg, ...);

//write by c
mc_message _self_response_to(const mo obj, const char* methodname);
mc_message _self_response_to_h(const mo obj, const char* methodname, MCHash hashval);
mc_message _response_to(mo const obj, const char* methodname, MCInt strict);
mc_message _response_to_h(mo const obj, const char* methodname, MCHash hashval, MCInt strict);

/*
 ObjectManage.h
 */

void mc_info(const char* classname, MCSizeT size, MCLoaderPointer loader);
void mc_clear(const char* classname, MCSizeT size, MCLoaderPointer loader);
mo mc_alloc(const char* classname, MCSizeT size, MCLoaderPointer loader);
void mc_info_h(const char* classname, MCSizeT size, MCLoaderPointer loader, MCHash hashval);
void mc_clear_h(const char* classname, MCSizeT size, MCLoaderPointer loader, MCHash hashval);
mo mc_alloc_h(const char* classname, MCSizeT size, MCLoaderPointer loader, MCHash hashval);
void mc_dealloc(MCObject* aobject, MCInt is_recycle);

#define MC_NO_NODE(bpool) (bpool->tail==mull)
#define MC_ONE_NODE(bpool) (bpool->tail->next==bpool->tail)
#define MC_TWO_NODE(bpool) (bpool->tail->next->next==bpool->tail)

void pushToTail(mc_blockpool* bpool, mc_block* ablock);
mc_block* getFromHead(mc_blockpool* bpool);
void empty(mc_blockpool* bpool);
MCInt count(mc_blockpool* bpool);
MCInt cut(mc_blockpool* bpool, mc_block* ablock, mc_block** result);

/*
 Root Class MCObject
 */

static inline MCObject* MCObject_init(MCObject* const obj) {obj->nextResponder=mull; return obj;}
static inline void      MCObject_responseChainConnect(mc_message_arg(MCObject), mo upperObj) {obj->nextResponder=upperObj;}
static inline void      MCObject_responseChainDisconnect(mc_message_arg(MCObject), voida) {obj->nextResponder=mull;}
static inline void      MCObject_bye(mc_message_arg(MCObject), voida) {}
static inline mc_class* MCObject_load(mc_class* const cla) {
    _binding(cla, "responseChainConnect", (MCFuncPtr)MCObject_responseChainConnect);
    _binding(cla, "responseChainDisconnect", (MCFuncPtr)MCObject_responseChainDisconnect);
    _binding(cla, "bye", (MCFuncPtr)MCObject_bye);
    return cla;
}

#endif

/* Code Snippet
-----------------------------------------
class(MyClass, SuperClass,

    int   member1;
    float member2;
)
-----------------------------------------
oninit(MyClass)
{
    if (init(MCObject)) {

        return obj;
    } else {
        return mull;
    }
}
-----------------------------------------
onload(MyClass)
{
    if (load(MCObject)) {

        return cla;
    } else {
        return mull;
    }
}
-----------------------------------------
method(MyClass, void, name, voida)
-----------------------------------------
utility(MyClass, void, name, voida)
-----------------------------------------
function(void, name, voida)
-----------------------------------------
compute(type, name)
-----------------------------------------
computing(type, name)
-----------------------------------------

-----------------------------------------
End Snippet */


