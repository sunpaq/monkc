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

#include "monkc.h"

//private data
static mc_hashtable* mc_global_classtable = nil;

void trylock_global_classtable()
{
	mc_trylock(&(mc_global_classtable->lock));
}

void unlock_global_classtable()
{
	mc_unlock(&(mc_global_classtable->lock));
}

static void mc_check()
{
	mc_object* obj = (mc_object*)malloc(sizeof(mc_object));
	runtime_log("sizeof obj pointer is: %p", obj);
	//do some checks
}

void mc_init()
{
	//default we set log level to debug
	LOG_LEVEL = MC_DEBUG;
	//create a class hashtable
	if(mc_global_classtable == nil)
		mc_global_classtable = new_table(0);
	//_init_class_list();
	//_init_anony_pool();
	//_init_vector_stack();
	//_init_wector_stack();
	mc_check();
	runtime_log("mc_init finished\n");
}

void mc_end()
{
	runtime_log("mc_end finished\n");
}

/*
for method binding
*/

unsigned _binding(mc_class* const aclass, const char* methodname, void* value)
{
	return _binding_h(aclass, methodname, value, hash(methodname));
}

unsigned _binding_h(mc_class* const aclass, const char* methodname, void* value, unsigned hashval)
{
	if(aclass==nil){
		error_log("_binding_h(mc_class* aclass) aclass is nill return 0\n");
		return 0;
	}
	if(aclass->table==nil){
		error_log("_binding_h(mc_class* aclass) aclass->table is nill return 0\n");
		return 0;
	}
	unsigned res = set_item(&(aclass->table), 
		new_item_h(methodname, value, hashval),
		0, 0);
	return res;
}

unsigned _override(mc_class* const aclass, const char* methodname, void* value)
{
	return _override_h(aclass, methodname, value, hash(methodname));
}

unsigned _override_h(mc_class* const aclass, const char* methodname, void* value, unsigned hashval)
{
	if(aclass==nil){
		error_log("_override_h(mc_class* aclass) aclass is nill return 0\n");
		return 0;
	}
	if(aclass->table==nil){
		error_log("_override_h(mc_class* aclass) aclass->table is nill return 0\n");
		return 0;
	}
	unsigned res = set_item(&(aclass->table), 
		new_item_h(methodname, value, hashval),
		1, 0);
	return res;
}

/*
for class load
*/

mc_class* alloc_mc_class()
{
	return (mc_class*)malloc(sizeof(mc_class));
}

mc_class* init_mc_class(mc_class* const aclass, const size_t objsize)
{
	aclass->objsize = objsize;
	aclass->table = new_table(0);
	aclass->free_pool = new_mc_blockpool();
	aclass->used_pool = new_mc_blockpool();
	if(aclass->table==nil){
		error_log("init_mc_class new_table() failed\n");
		exit(-1);
	}
	if(aclass->free_pool==nil || aclass->used_pool==nil){
		error_log("init_mc_class new_mc_blockpool() failed\n");
		exit(-1);
	}
	return aclass;
}

mc_class* new_mc_class(const size_t objsize)
{
	return init_mc_class(alloc_mc_class(), objsize);
}

mc_class* _load(const char* name, size_t objsize, loaderFP loader)
{
	return _load_h(name, objsize, loader, hash(name));
}

mc_class* _load_h(const char* name, size_t objsize, loaderFP loader, unsigned hashval)
{
	//try lock spin lock
	trylock_global_classtable();

	mc_hashitem* item = nil;
	if((item=get_item_byhash(&mc_global_classtable, hashval, name)) == nil){
		//new a item
		mc_class* aclass = new_mc_class(objsize);
		item = new_item(name, nil);//nil first
		package_by_item(&item, &aclass);
		(*loader)(aclass);
		//set item
		set_item(&mc_global_classtable, item, 0, 1);
		runtime_log("load a class[%s]\n", nameofc(aclass));
	}else{
		runtime_log("find a class[%s]\n", nameofc((mc_class*)item->value));
	}
	//unlock
	unlock_global_classtable();
	return (mc_class*)(item->value);
}

mo _new(mo const this, initerFP initer)
{
	//block, isa, saved_isa is setted at _alloc()
	this->ref_count = 1;
	this->super = nil;
	this->mode = nil;
	(*initer)(this);
	return this;
}

mo _new_category(mo const this, initerFP initer, loaderFP loader_cat, initerFP initer_cat)
{
	//block, isa, saved_isa is setted at _alloc()
	this->ref_count = 1;
	(*loader_cat)(this->isa);
	this->super = nil;
	this->mode = nil;
	(*initer)(this);
	(*initer_cat)(this);
	return this;
}

void _shift(mo const obj, const char* modename, size_t objsize, loaderFP loader)
{
	mc_class* aclass = _load(modename, objsize, loader);
	if(obj->mode != aclass)
		obj->mode = aclass;
	//switch to mode
	obj->isa = obj->mode;
	runtime_log("obj[%p/%s] shift to mode[%s]\n", 
		obj, nameofc(obj->saved_isa), nameof(obj));
}

void _shift_back(mo const obj)
{
	obj->isa = obj->saved_isa;
	runtime_log("obj[%p/%s] shift to mode[%s]\n", 
		obj, nameofc(obj->saved_isa), nameof(obj));
}

static int ref_count_down(mo const this)
{
	for(;;){
		if(this == nil){
			error_log("recycle/release(nil) do nothing.\n");
			return REFCOUNT_ERR;
		}
		if(this->ref_count == 0)
		{
			runtime_log("recycle/release(%s) count=0 return\n", nameof(this));
			return REFCOUNT_ERR;
		}
		if(this->ref_count == REFCOUNT_NO_MM){
			debug_log("ref_count is REFCOUNT_NO_MM manage by runtime. do nothing\n");
			return REFCOUNT_NO_MM;
		}
		if(this->isa == nil){
			error_log("recycle/release(obj) obj have no class linked. do nothing.\n");
			return REFCOUNT_ERR;
		}

		int* addr = &(this->ref_count);
		int oldcount = mc_atomic_get_integer(addr);
		int newcount = oldcount;
		if(newcount > 0)
			newcount--;
		if(!mc_atomic_set_integer(addr, oldcount, newcount))
			break;
	}
	return this->ref_count;
}

void _recycle(mo const this)
{
	if(ref_count_down(this) == 0){
		//call the "bye" method on object
		fs(this, bye, nil);
		_dealloc(this, 1);
	}
}

void _release(mo const this)
{
	if(ref_count_down(this) == 0){
		//call the "bye" method on object
		fs(this, bye, nil);
		_dealloc(this, 0);
	}
}

mo _retain(mo const this)
{
	for(;;){
		if(this == nil){
			error_log("retain(nil) do nothing.\n");
			return this;
		}
		if(this->ref_count == REFCOUNT_NO_MM){
			debug_log("ref_count is REFCOUNT_NO_MM manage by runtime. do nothing\n");
			return this;
		}
		if(this->isa == nil){
			error_log("release(obj) obj have no class linked. do nothing.\n");
			return this;
		}

		int* addr = &(this->ref_count);
		int oldcount = mc_atomic_get_integer(addr);
		if(!mc_atomic_set_integer(addr, oldcount, oldcount+1))
			break;
	}
	runtime_log("%s - ref_count:%d\n", nameof(this), this->ref_count);
	return this;
}

char* nameof(mc_object* const aobject)
{
	if(aobject==nil)
		return "";
	if(aobject->isa==nil)
		return "";
	return nameofc(aobject->isa);
}

char* nameofc(mc_class* const aclass)
{
	if(aclass==nil)
		return "";
	if(aclass->item==nil)
		return "";
	if(aclass->item->key==nil)
		return "";
	return aclass->item->key;
}



