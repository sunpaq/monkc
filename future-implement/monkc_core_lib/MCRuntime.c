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

#include "MCRuntime.h"

/*
	Pre declears
*/

extern void _init_vector_stack();
extern void _init_wector_stack();
extern void _init_class_list();
extern void _clear_class_list();

void ff_from_root(id const obj, const char* methodname);
void ff_to_root(id const obj, const char* methodname);

//private
static void _nil_check(id const self, 
	char* log1, char* log2, char* log3, 
	char* log4, char* log5, char* log6, pthread_mutex_t* lock);

/*
	Anonymous objects pool for automatic memory management
*/

static MCObject* mc_anony_pool[ANONY_POOL_SIZE];
static unsigned mc_anony_count = 0;
static void _init_anony_pool()
{
	int i;
	for (i = 0; i < ANONY_POOL_SIZE; i++)
		mc_anony_pool[i]=nil;
}

void _push_anony_obj(MCObject* anony)
{
	//if(anony==nil)return;

	int oldcount, tmpcount;
	MCObject *oldobj, *tmpobj;
	//lock free
	for(;;)
	{
		oldcount = mc_anony_count;//lock
		oldobj = mc_anony_pool[mc_anony_count];
		tmpcount = oldcount;
		tmpobj = oldobj;
		tmpobj = anony;

		if(tmpobj == nil)
			return;
		if(tmpcount >= ANONY_POOL_SIZE)
			tmpcount = 0;
		else
			tmpcount = tmpcount + 1;

		if(!mc_compareAndSwapInteger(&mc_anony_count, oldcount, tmpcount)
		&&!mc_compareAndSwapPointer(&mc_anony_pool[mc_anony_count], oldobj, tmpobj))
		{
			break;
		}
	}

	//operate on the saved old object is thread safe
	if(oldobj!=nil)relnil(oldobj);
}

//pop do not release the obj, when a anony obj is poped from pool
//you need manage it by retain/release manually
static void _pop_anony_obj(MCObject* anony)
{
	if(anony==nil)return;

	//no need lock free
	int i;
	for (i = 0; i < ANONY_POOL_SIZE; i++)
	{
		if(mc_anony_pool[i]==anony){
			mc_anony_pool[i]=nil;
			return;
		}
	}
}

/*
	Runtime Start and End
*/

void mc_init()
{
	//default we set log level to debug
	LOG_LEVEL = DEBUG;
	_init_class_list();
	//_init_anony_pool();
	//_init_vector_stack();
	//_init_wector_stack();
	runtime_log("mc_init finished\n");
}

void mc_check()
{
	MCObject* obj = (MCObject*)malloc(sizeof(MCObject));
	runtime_log("sizeof obj pointer is: %p", obj);

}

void mc_end()
{
	_clear_class_list();
	runtime_log("mc_end finished\n");
}

/*
	Memory Management Part
*/

void release(id const this)
{
	int oldcount, tmpcount;
	MCObject *oldobj, *tmpobj;
	MCClass *oldclass, *tmpclass;

	runtime_log("release begin CAS\n");
	for(;;)
	{
		oldobj = this;//lock
		oldclass = this->isa;
		oldcount = this->ref_count;
		tmpobj = oldobj;
		tmpclass = oldclass;
		tmpcount = oldcount;

		if(tmpobj == nil)
		{
			error_log("%s\n", "release(nil) do nothing.");
			return;
		}
		if (tmpclass == nil)
		{
			error_log("release(%d) twice. do nothing.\n", this);
			return;
		}
		if (tmpcount == REFCOUNT_NO_MM)
		{
			debug_log("ref_count is -1 manage by runtime. do nothing\n");
			return;
		}

		//try to set the ref_count to 0
		if(tmpcount == REFCOUNT_ANONY_OBJ)
			tmpcount = 0;
		//try to minus 1
		if(tmpcount > 0)
			tmpcount--;

		if (!mc_compareAndSwapPointer(&this, oldobj, tmpobj)
		&&!mc_compareAndSwapInteger(&this->ref_count, oldcount, tmpcount))//unlock
		{
			break;
		}else{
			runtime_log("release CAS fail: this[%p/%p] count[%d/%d]\n", oldobj, this, oldcount, this->ref_count);
		}	 
	}
	runtime_log("release end CAS\n");

	//no other thread call release
	//operate on the saved old object is thread safe
	if(tmpcount == 0)
	{
		//call the "bye" method on object
		_push_jump(_self_response_to(this, "bye"), nil);

		if(oldcount == REFCOUNT_ANONY_OBJ)
			_pop_anony_obj(oldobj);

		//destory the obj
		runtime_log("----free[%p]: goodbye!\n", this);
		if(this!=nil)mc_free(this);
	}
}

void retain(id const this)
{
	int oldcount, tmpcount;
	MCObject *oldobj, *tmpobj;
	MCClass *oldclass, *tmpclass;

	runtime_log("begin CAS\n");
	for(;;)
	{
		oldobj = this;//lock
		oldclass = this->isa;
		oldcount = this->ref_count;
		tmpobj = oldobj;
		tmpclass = oldclass;
		tmpcount = oldcount;

		if(tmpobj == nil)
		{
			error_log("%s\n", "retain(nil) do nothing.");
			return;
		}
		if (tmpclass == nil)
		{
			error_log("retain(obj) obj have no class linked. do nothing.\n");
			return;
		}
		if (tmpcount == REFCOUNT_NO_MM)
		{
			debug_log("ref_count is -1 manage by runtime. do nothing\n");
			return;
		}

		//try to set the ref_count to 0
		if(tmpcount == REFCOUNT_ANONY_OBJ)			
			tmpcount = 0;
			
		tmpcount++;//try to plus 1

		if (!mc_compareAndSwapPointer(&this, oldobj, tmpobj)
		&&!mc_compareAndSwapPointer(&this->isa, oldclass, tmpclass)
		&&!mc_compareAndSwapInteger(&this->ref_count, oldcount, tmpcount))//unlock
		{
			break;
		}
	}
	runtime_log("end CAS\n");

	//no other thread call release
	//operate on the saved old object is thread safe
	if(oldcount == REFCOUNT_ANONY_OBJ)
		_pop_anony_obj(oldobj);
	
	runtime_log("%s - ref_count:%d\n", oldclass->name, tmpcount);
}

void _relnil(MCObject** const this)
{
	release(*this);
	(*this) = nil;
}

/*
	Method Binding and Reflection Part
*/

unsigned _binding(MCClass* const class, const char* methodname, void* value)
{
	if(class==nil)return;

	//prepare
	unsigned hashkey = _hash(methodname);
	MCMethod* method = (MCMethod*)malloc(sizeof(MCMethod));
	method->addr = value;
	mc_copyName(method, methodname);

	//save
	MCMethod* oldmethod;
	int oldcount;
	for(;;)
	{
		oldmethod = (MCMethod*)class->method_list[hashkey];//lock
		oldcount = class->method_count;
		if(oldmethod!=nil)
			break;
		if(oldcount > MAX_METHOD_NUM-1){
			error_log("method index out of bound\n");
			//need some clean for ARM maybe
			exit(-1);
		}

		if(!mc_compareAndSwapPointer(&class->method_list[hashkey], oldmethod, method)
		&& !mc_compareAndSwapInteger(&class->method_count, oldcount, oldcount+1))
		{
			runtime_log("binding a method, hash index:[%s/%d]\n", methodname, hashkey);
			return hashkey;
		}
	}
	
	//clean up
	if(mc_compareName(oldmethod, methodname)==0){
		//no conflict already binded.
		error_log("binding: class[%s] method[%s/%d] have already binded. clean temp MCMethod\n", 
			class->name, methodname, hashkey);
		free(method);
	}else{
		//conflict
		error_log("binding: class[%s] method[%s/%d] is conflict with oldmethod[%s/%d] please chanege a name\n", 
			class->name, methodname, hashkey, oldmethod->name, hashkey);
		exit(-1);
	}
	return hashkey;
}

unsigned _override(MCClass* const class, const char* methodname, void* value)
{
	if(class==nil)return;

	//prepare
	unsigned hashkey = _hash(methodname);
	MCMethod* method = (MCMethod*)malloc(sizeof(MCMethod));
	method->addr = value;
	mc_copyName(method, methodname);

	//save
	MCMethod* oldmethod;
	int oldcount;
	for(;;)
	{
		oldmethod = class->method_list[hashkey];//lock
		oldcount = class->method_count;
		if(oldmethod!=nil)
			break;
		if(oldcount > MAX_METHOD_NUM-1){
			error_log("method index out of bound\n");
			//need some clean for ARM maybe
			exit(-1);
		}

		if(!mc_compareAndSwapPointer(&class->method_list[hashkey], oldmethod, method)
		&& !mc_compareAndSwapInteger(&class->method_count, oldcount, oldcount+1))
		{
			runtime_log("override a method, hash index:[%s/%d]\n", methodname, hashkey);
			return hashkey;
		}
	}
	
	//clean up
	if(mc_compareName(oldmethod, methodname)==0){
		//no conflict already binded.
		error_log("override: class[%s] method[%s/%d] have already binded. clean old MCMethod and rebind new\n", 
			class->name, methodname, hashkey);
		free(oldmethod);
		class->method_list[hashkey]=method;
	}else{
		//conflict
		error_log("override: class[%s] method[%s/%d] is conflict with oldmethod[%s/%d] please chanege a name\n", 
			class->name, methodname, hashkey, oldmethod->name, hashkey);
		exit(-1);
	}
	return hashkey;
}

MCMessage make_msg(id const obj, const void* entry)
{
	//we will return a struct
	MCMessage tmpmsg = {nil, nil};
	tmpmsg.object = obj;
	tmpmsg.addr = entry;
	return tmpmsg;
}

void ff_from_root(id const obj, const char* methodname)
{	
	runtime_log("<ff_from_root> start\n");
	MCMessage address_stack[MAX_CLASS_NUM];

	int count = 0;
	unsigned hashkey = _hash(methodname);
	MCMethod* amethod;
	id iter;
	for(iter = obj;
		iter!= nil;
		iter = iter->super){
		runtime_log("<ff_from_root> checking [%s]\n", iter->isa->name);
		if(iter->isa!=nil)amethod = iter->isa->method_list[hashkey];
		if(amethod!=nil && amethod->addr!=nil){
			runtime_log("<ff_from_root> push a method[%s/%s/%p] count[%d]\n", 
				iter->isa->name, amethod->name, amethod->addr, count);
			address_stack[count].object=iter;
			address_stack[count].addr=amethod->addr;
			count++;
		}
	}
	runtime_log("<ff_from_root> ---\n");
	for(count--; count>=0; count--){
		runtime_log("<ff_from_root> pop a method[%p]\n", address_stack[count].addr);
		_push_jump(address_stack[count], nil);
	}
	runtime_log("<ff_from_root> end\n");
}

void ff_to_root(id const obj, const char* methodname)
{
	unsigned hashkey = _hash(methodname);
	MCMessage tmpmsg = {nil, nil};
	MCMethod* amethod;
	id iter;
	for(iter = obj;
		iter!= nil;
		iter = iter->super){
		amethod = iter->isa->method_list[hashkey];
		if(amethod!=nil && amethod->addr!=nil)
			_push_jump(make_msg(iter, amethod->addr), nil);
	}
}

MCMessage _self_response_to(id const obj, const char* methodname)
{
	_nil_check(obj,
		"_response_to(obj, name)",
		"obj is nil, name is:",
		methodname,
		"_response_to(obj, name)",
		"obj have no class object linked. please call set_class(). the key is:",
		"", nil);
	//we will return a struct
	MCMessage tmpmsg = {nil, nil};
	MCMethod* amet = obj->isa->method_list[_hash(methodname)];
	if(amet!=nil)
	{
		tmpmsg.object = obj;
		tmpmsg.addr = amet->addr;
		return tmpmsg;
	}
	else{
		return tmpmsg;
	}
}

MCMessage _response_to(id const obj, const char* methodname)
{
	_nil_check(obj,
		"_response_to(obj, name)",
		"obj is nil, name is:",
		methodname,
		"_response_to(obj, name)",
		"obj have no class object linked. please call set_class(). the key is:",
		"", nil);
	//we will return a struct
	MCMessage tmpmsg = {nil, nil};

	unsigned hashkey = _hash(methodname);
	MCObject* obj_iterator = obj;
	MCObject* first_hit_obj = nil;
	MCObject* last_hit_obj = nil;
	MCMethod* amethod = nil;
	int hit_count = 0;

	//for root object
	if(obj_iterator->super==nil){
		if((amethod=obj_iterator->isa->method_list[hashkey]) != nil){
			hit_count = 1;
			first_hit_obj = obj_iterator;
			last_hit_obj = obj_iterator;
		}
	}else{
	//for non-root object
		for(obj_iterator = obj; 
			obj_iterator!= nil;
			obj_iterator = obj_iterator->super){

			if((amethod=obj_iterator->isa->method_list[hashkey]) != nil)
			{
				hit_count++;
				if(first_hit_obj==nil)first_hit_obj = obj_iterator;
				last_hit_obj = obj_iterator;
			}

			runtime_log("go super\n");
		}
	}

	if(hit_count == 0)
	{
		if(obj->isa->name!=nil && methodname!=nil)
			error_log("class[%s] can not response to method[%s/%d]\n", obj->isa->name, methodname, hashkey);
		return tmpmsg;
	}

	//for the no confilict method
	else if(hit_count == 1)
	{
		tmpmsg.object = last_hit_obj;
		tmpmsg.addr = last_hit_obj->isa->method_list[hashkey]->addr;
		return tmpmsg;
	}

	//for the method key have conflicted with some super class in inherit tree
	else
	{
		for(obj_iterator = first_hit_obj;
			obj_iterator!= last_hit_obj->super;
			obj_iterator = obj_iterator->super){
			//get the method obj
			amethod = obj_iterator->isa->method_list[hashkey];
			//nil check
			if(amethod!=nil && amethod->name!=nil)
			{
				runtime_log("hit a method [%s/%d] to match [%s]\n", amethod->name, hashkey, methodname);
				if(mc_compareName(amethod, methodname) == 0)
				{
					runtime_log("method name matched! we return the method address\n");
					tmpmsg.object = obj_iterator;
					tmpmsg.addr = obj_iterator->isa->method_list[hashkey]->addr;
					return tmpmsg;
				}
			}
		}
	}
}

//the _ff() function is implement in assemblly language in folder /MCRuntimeAsm
//the mc_compareAndSwap() is implement in assemblly language in folder /MCRuntimeAsm

static inline void _nil_check(id const self, 
	char* log1, char* log2, char* log3, 
	char* log4, char* log5, char* log6,
	pthread_mutex_t* lock){
	if(self == nil){
		error_log("%s:\n%s\n%s\n", log1, log2, log3);
		//if(lock != nil)pthread_mutex_unlock(lock);
		exit(-1);
	}
	if(self->isa == nil){
		error_log("%s:\n%s\n%s\n", log4, log5, log6);
		//if(lock != nil)pthread_mutex_unlock(lock);
		exit(-1);
	}
}

void mc_copyName(MCMethod* method, const char* name)
{
	if(sizeof(*name) >= MAX_METHOD_NAME_CHAR_NUM)
		error_log("method name[%s] length is large than Max method name char number: %d\n", 
			name, MAX_METHOD_NAME_CHAR_NUM);
	strncpy(method->name, name, MAX_METHOD_NAME_CHAR_NUM-1);
	method->name[MAX_METHOD_NAME_CHAR_NUM-1]='\0';
}

int mc_compareName(MCMethod* method, const char* name)
{
	return strncmp(method->name, name, MAX_METHOD_NAME_CHAR_NUM);
}