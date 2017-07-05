/*
 Copyright (c) <2013-2017>, <Sun Yuli>
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

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

//#include <inttypes.h>
#include <string.h>
#include <limits.h>

/* Monk-C use many C99 standard features, make sure your compiler and platform support C99 standard */
#if __STDC_VERSION__ < 199901L
#error "your platform doesn't support C99"
#endif

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

#ifndef null
#define null NULL
#endif
#ifndef NUL
#define NUL '\0'
#endif

#define voida void* voidarg
#define S(value) #value
#define SEQ(dest, src) (mc_compare_key(dest, src)==0)
#define A_B(a, b) a##_##b
#define nameof(obj) mc_nameof((MCObject*)obj)
#define nameofc(cls) mc_nameofc(cls)
#define deref(x) (*(x))
#define addrof(x) (&(x))

//in C99,
//inline function need to be have "inline" and "non-inline" version both implement
//static inline not require "non-inline" version
#define MCInline static inline
#define MCGlobalKey static const char*

/**
 * Limitations of Monk-C method()/function() parameters
 *
 * 1. Limitation of C variable arguments function:
 *
 * any int type should >= int
 * any float type should wrap use MCFloat
 *
 * char/signed  char/unsigned  char              (use int/unsigned/MCInt/MCUInt)
 * short/signed short/unsigned short             (use int/unsigned/MCInt/MCUInt)
 * short int/signed short int/unsigned short int (use int/unsigned/MCInt/MCUInt)
 * float                                         (must use MCFloat)
 *
 * 2. Limitation of iOS ARM64 ABI
 *
 * we only use 8 cpu registers to pass parameters
 * first 2 are fixed into message.address and message.object
 * user can define max 6 parameters in a method()
 *
 * if you need to pass more than 6 parameters 
 * please design a structure/object wrap them and pass the pointer in
 * normal C functions NOT subject to these limitations
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

//using double for all floating point data (float is 4bytes, double is 8bytes)
typedef union {
    double   f;
    uint64_t i;
} MCFloat;

MCInline MCFloat MCFloatF(double value)   { return (MCFloat){.f=value}; }
MCInline MCFloat MCFloatI(uint64_t value) { return (MCFloat){.i=value}; }

typedef uint32_t     MCHash;
#define MCHashMax    UINT32_MAX
#define MCHashMask   0x7fffffff

typedef size_t       MCSizeT;
typedef void*        MCVoidPtr;
typedef void         (*MCFuncPtr)(void);

//true, false
#define printb(B)    (B?"true":"false")
typedef _Bool MCBool;

/*
 Generic Type
 */

struct _MCObject;
typedef union {
    //float and integers use 8bytes (64bits)
    double      mcfloat;//default
    MCSizeT     mcsizet;
    MCULongLong mculonglong;
    MCLongLong  mclonglong;
    MCULong     mculong;
    MCLong      mclong;
    //pointers use 8bytes
    struct _MCObject *mcobject;
    MCVoidPtr   mcvoidptr;
    MCFuncPtr   mcfuncptr;
    //integers use 4bytes
    MCUInt      mcuint;
    MCInt       mcint;
    MCHash      mchash;
    //bool use 1byte
    MCBool      mcbool;
} MCGeneric;

MCInline MCGeneric MCGenericF(double value)            { MCGeneric g; g.mcfloat=value; return g; }
MCInline MCGeneric MCGenericSz(MCSizeT value)          { MCGeneric g; g.mcsizet=value; return g; }
MCInline MCGeneric MCGenericUll(MCULongLong value)     { MCGeneric g; g.mculonglong=value; return g; }
MCInline MCGeneric MCGenericLl(MCLongLong value)       { MCGeneric g; g.mclonglong=value; return g; }
MCInline MCGeneric MCGenericUl(MCULong value)          { MCGeneric g; g.mculong=value; return g; }
MCInline MCGeneric MCGenericL(MCLong value)            { MCGeneric g; g.mclong=value; return g; }

MCInline MCGeneric MCGenericO(struct _MCObject* value) { MCGeneric g; g.mcobject=value; return g; }
MCInline MCGeneric MCGenericVp(MCVoidPtr value)        { MCGeneric g; g.mcvoidptr=value; return g; }
MCInline MCGeneric MCGenericFp(MCFuncPtr value)        { MCGeneric g; g.mcfuncptr=value; return g; }

MCInline MCGeneric MCGenericUi(MCUInt value)           { MCGeneric g; g.mcuint=value; return g; }
MCInline MCGeneric MCGenericI(MCInt value)             { MCGeneric g; g.mcint=value; return g; }
MCInline MCGeneric MCGenericH(MCHash value)            { MCGeneric g; g.mchash=value; return g; }

MCInline MCGeneric MCGenericB(MCBool value)            { MCGeneric g; g.mcbool=value; return g; }

MCInline int MCGenericCompare(MCGeneric A, MCGeneric B) {
    if (A.mcfloat > B.mcfloat) {
        return 1;
    }
    else if (A.mcfloat < B.mcfloat) {
        return -1;
    }
    //A == B
    return 0;
}

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
 * and it can auto expand to next level when some key collisioned
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
    MCGeneric value;
    char key[MAX_KEY_CHARS];
}mc_hashitem;

#define MAX_ITEM_CACHE 10
typedef struct
{
    mc_hashitem* cache[MAX_ITEM_CACHE];
    MCInt cache_count;
    MCInt lock;
    MCHashTableLevel level;
    mc_hashitem* items[];
}mc_hashtable;

/*
 method table is initially set min one
 class  table is initially set max one
 
 only the max size table use chain to slove collision
 other tables will expand(rehash) until they reach the max
 */

static MCHashTableSize mc_hashtable_sizes[MCHashTableLevelCount] = {
    //901,
    1301,
    3101,
    13001,
    31001,
    130001
};

MCInline MCHashTableSize get_tablesize(const MCHashTableLevel level)
{
    if(level > MCHashTableLevelMax){
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
    deref(ablock).next = null;
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
    bpool->tail = null;
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
typedef struct _MCObject
{
    //address is for dynamic method calling.
    MCFuncPtr address;
    //data
    struct _MCObject* nextResponder;
    mc_block* block;
    mc_class* isa;
    mc_class* saved_isa;
    MCInt ref_count;
} MCObject;

MCInline mc_class* alloc_mc_class(const MCSizeT objsize)
{
    MCHashTableLevel initlevel = MCHashTableLevel1;
    mc_class* aclass = (mc_class*)malloc(sizeof(mc_class));
    aclass->objsize = objsize;
    //init pool
    aclass->free_pool.lock = 0;
    aclass->free_pool.tail = null;
    aclass->used_pool.lock = 0;
    aclass->used_pool.tail = null;
    //init table
    aclass->table = (mc_hashtable*)malloc(sizeof(mc_hashtable) + sizeof(mc_hashitem)*get_tablesize(initlevel));
    aclass->table->lock = 0;
    aclass->table->level = initlevel;
    //aclass->table->table_item_count = 0;
    //set all the slot to nil
    for (int i = 0; i < get_tablesize(initlevel); i++)
        (aclass->table->items)[i] = null;
    return aclass;
}

MCInline void package_by_item(mc_hashitem* aitem_p, mc_class* aclass_p)
{
    (aitem_p)->value.mcvoidptr = aclass_p;
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
#define onextend(cls, tag)               void cls##_##tag(mc_class* cla)
#define load(supercls)                        supercls##_load(cla)
#define init(supercls)                        supercls##_init((supercls*)obj)
#define extend(cls, tag)                      cls##_##tag(_load(#cls, sizeof(cls), cls##_##load))
#define preload(cls)                          _load(#cls, sizeof(cls), cls##_##load)
#define superbye(cls)                         cls##_bye(&obj->Super, 0)

//method binding
#define mixing(type, met, ...)                _binding(cla, S(met), (MCFuncPtr)met)
#define binding(cls, type, met, ...)  		  _binding(cla, S(met), (MCFuncPtr)A_B(cls, met))
#define utility(cls, type, name, ...) 	      type cls##_##name(__VA_ARGS__)
#define method(cls, type, name, ...)          type cls##_##name(cls* volatile obj, __VA_ARGS__)
#define function(type, name, ...)             static type name(void* volatile any, __VA_ARGS__)
//#define method(cls, type, name, ...) 	      type cls##_##name(MCFuncPtr volatile address, cls* volatile obj, __VA_ARGS__)
//#define function(type, name, ...)             static type name(MCFuncPtr volatile address, void* volatile any, __VA_ARGS__)

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
#define clear(cls)  					mc_clear(S(cls), sizeof(cls), cls##_load)
#define info(cls)                  		mc_info(S(cls))

//for call method
#define ff(obj, met, ...)				 _push_jump(response_to((MCObject*)obj, S(met)), __VA_ARGS__)//send message
#define ffindex(obj, idx, ...)		     _push_jump(response_to_i((MCObject*)obj, idx), __VA_ARGS__)//send index

//lock
void trylock_global_classtable(void);
void unlock_global_classtable(void);

//binding method api
MCHashTableIndex _binding(mc_class* const aclass, const char* methodname, MCFuncPtr value);

//class load
mc_class* _load(const char* name, MCSizeT objsize, MCLoaderPointer loader);

//object create
MCObject* _new(MCObject* const obj, MCIniterPointer initer);

//memory management
#define REFCOUNT_NO_MM 	-1
#define REFCOUNT_ERR 	-100
void _recycle(MCObject* const obj);
void _release(MCObject* const obj);
MCObject* _retain(MCObject* const obj);
#define recycle(obj) _recycle((MCObject*)obj)
#define release(obj) _release((MCObject*)obj)
#define retain(obj)  _retain((MCObject*)obj)

//tool for class
extern void _init_class_list(void);
extern void _clear_class_list(void);

MCInline const char* mc_nameofc(const mc_class* aclass) {
    if(aclass==null)
        return "unknown";
    if(aclass->item==null)
        return "unknown";
    if(aclass->item->key[0]==NUL)
        return "unknown";
    return &aclass->item->key[0];
}

MCInline const char* mc_nameof(const MCObject* aobject) {
    if(aobject->isa==null)
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

MCInline MCBool mc_compare_key(const char* dest, const char* src) {
    if (dest != null && src != null) {
        return (strcmp(dest, src) == 0);
    }else{
        return false;
    }
}

/*
 HashTable.h
 */

//copy form << The C Programming language >>
//BKDR Hash Function
MCInline MCHash hash_content(const char *s) {
    register MCHash hashval;
    for(hashval = 0; *s != NUL; s++)
        hashval = *s + 31 * hashval;
    //avoid integer overflow
    return (hashval & MCHashMask);
}

MCInline MCHash hash(const char *s) {
    //avoid integer overflow
    //return ((MCHash)s & MCHashMask);
    //return ((MCHash)s);
    return hash_content(s);
}

MCInline MCHashTableIndex firstHashIndex(MCHash nkey, MCHashTableSize slots) {
    return nkey % slots;
    //return (nkey - slots * (nkey / slots));
}

MCInline MCHashTableIndex secondHashIndex(MCHash nkey, MCHashTableSize slots, MCHash first) {
    return (first + (1+(nkey % (slots-1)))) % slots;
    //MCHashTableSize slots_1 = slots - 1;
    //MCHash temp = first + 1 + nkey - slots_1 * (nkey / slots_1);
    //return (temp - slots * (temp / slots));
}

mc_hashitem* new_item(const char* key, MCGeneric value, MCHash hashval);
mc_hashtable* new_table(const MCHashTableLevel initlevel);

MCHashTableIndex set_item(mc_hashtable** table_p, mc_hashitem* item, MCBool isAllowOverride, const char* refkey);
mc_hashitem* get_item_byhash(mc_hashtable* table_p, const MCHash hashval, const char* refkey);



MCInline mc_hashitem* get_item_bykey(mc_hashtable* const table_p, const char* key)
{
    if(table_p==null){
        error_log("get_item_bykey(table_p) table_p is nil return nil\n");
        return null;
    }
    //try get index
    return get_item_byhash(table_p, hash(key), key);
}

MCInline mc_hashitem* get_item_byindex(mc_hashtable* const table_p, const MCHashTableIndex index)
{
    if(table_p==null){
        error_log("get_item_byindex(table_p) table_p is nil return nil\n");
        return null;
    }
    if(index > get_tablesize(table_p->level))
        return null;
    if(table_p->items[index] != null)
        return table_p->items[index];
    else
        return null;
}

/*
 Messaging.h
 */
typedef struct {
    MCObject* object;
    char message[MAX_KEY_CHARS];
} mc_message;

MCInline mc_message make_msg(MCObject* obj, const char* msg) {
    mc_message message;
    message.object = obj;
    strncpy(message.message, msg, strlen(msg));
    return message;
}

//write by asm
void* _push_jump(register MCObject* msg, ...);

//write by c
MCBool response_test(MCObject* obj, const char* methodname);
MCObject* response_to(MCObject* obj, const char* methodname);
MCObject* response_to_i(MCObject* obj, MCHashTableIndex index);

/*
 ObjectManage.h
 */

void mc_info(const char* classname);
void mc_clear(const char* classname, MCSizeT size, MCLoaderPointer loader);
MCObject* mc_alloc(const char* classname, MCSizeT size, MCLoaderPointer loader);
void mc_dealloc(MCObject* aobject, MCInt is_recycle);

#define MC_NO_NODE(bpool) (bpool->tail==null)
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

MCObject* MCObject_init(MCObject* const obj);
static inline void      MCObject_responseChainConnect(MCObject* const obj, MCObject* upperObj) {obj->nextResponder=upperObj;}
static inline void      MCObject_responseChainDisconnect(MCObject* const obj, voida) {obj->nextResponder=null;}
static inline void      MCObject_printDebugInfo(MCObject* const obj, mc_class* cobj) {
    mc_class* mcclass = cobj;
    if (!mcclass)
        mcclass = obj->isa;
    MCHashTableSize size = get_tablesize(mcclass->table->level);
    for (int i=0; i<size; i++) {
        mc_hashitem* item = mcclass->table->items[i];
        if (item && item->key[0]) {
            debug_log("%s - %d/%s\n", mcclass->item->key, item->hash, item->key);
        }
    }
}
static inline void      MCObject_bye(MCObject* const obj, voida) {}
static inline mc_class* MCObject_load(mc_class* const cla) {
    _binding(cla, "responseChainConnect", (MCFuncPtr)MCObject_responseChainConnect);
    _binding(cla, "responseChainDisconnect", (MCFuncPtr)MCObject_responseChainDisconnect);
    _binding(cla, "printDebugInfo", (MCFuncPtr)MCObject_printDebugInfo);
    _binding(cla, "bye", (MCFuncPtr)MCObject_bye);
    return cla;
}

#endif
