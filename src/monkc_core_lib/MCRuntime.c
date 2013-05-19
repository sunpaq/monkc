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

/*
	Anonymous objects pool for automatic memory management
*/

/*
static mc_object* mc_anony_pool[ANONY_POOL_SIZE];
static unsigned mc_anony_count = 0;
static void _init_anony_pool()
{
	int i;
	for (i = 0; i < ANONY_POOL_SIZE; i++)
		mc_anony_pool[i]=nil;
}

void _push_anony_obj(mc_object* anony)
{
	if(anony==nil)return;
	if(mc_anony_count >= ANONY_POOL_SIZE)
		mc_atomic_set_integer(&mc_anony_count, 0);
	else
		mc_atomic_set_integer(&mc_anony_count, mc_anony_count+1);
	if(mc_anony_pool[mc_anony_count]!=nil)
		relnil(mc_anony_pool[mc_anony_count]);
	else
		mc_atomic_set_pointer(&mc_anony_pool[mc_anony_count], anony);
}

//pop do not release the obj, when a anony obj is poped from pool
//you need manage it by retain/release manually
static void _pop_anony_obj(mc_object* anony)
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
*/

/*
	Memory Management Part
*/

void release(mc_object** const this_p)
{
	for(;;){
		if((*this_p) == nil){
			error_log("release(nil) do nothing.\n");
			return;
		}
		if((*this_p)->ref_count == REFCOUNT_NO_MM){
			debug_log("ref_count is REFCOUNT_NO_MM manage by runtime. do nothing\n");
			return;
		}
		if((*this_p)->isa == nil){
			error_log("release(obj) obj have no class linked. do nothing.\n");
			return;
		}

		int* addr = &((*this_p)->ref_count);
		int oldcount = mc_atomic_get_integer(addr);
		if(oldcount == 0)
			break;
		if(!mc_atomic_set_integer(addr, oldcount, oldcount-1))
			break;
	}

	if((*this_p)->ref_count == 0)
	{
		//call the "bye" method on object
		_push_jump(_self_response_to(*this_p, "bye"), nil);
		//destory the obj
		runtime_log("----free[%p]: goodbye!\n", *this_p);
		free(*this_p);
		(*this_p) = nil;
	}
}

void retain(mc_object* const this)
{
	for(;;){
		if(this == nil){
			error_log("retain(nil) do nothing.\n");
			return;
		}
		if(this->ref_count == REFCOUNT_NO_MM){
			debug_log("ref_count is REFCOUNT_NO_MM manage by runtime. do nothing\n");
			return;
		}
		if(this->isa == nil){
			error_log("release(obj) obj have no class linked. do nothing.\n");
			return;
		}

		int* addr = &(this->ref_count);
		int oldcount = mc_atomic_get_integer(addr);
		if(!mc_atomic_set_integer(addr, oldcount, oldcount+1))
			break;
	}
	runtime_log("%s - ref_count:%d\n", this->isa->name, this->ref_count);
}

/*
	Method Binding and Reflection Part
*/

unsigned _binding(mc_class* const aclass, const char* methodname, void* value)
{
	if(aclass==nil)return;
	//prepare
	mc_method* method = (mc_method*)malloc(sizeof(mc_method));
	method->next = nil;
	method->addr = value;
	method->hash = hash(methodname);
	mc_copy_methodname(method, methodname);
	unsigned res = set_method(&(aclass->table), method, NO);
	//insert	
	return res;
}

unsigned _override(mc_class* const aclass, const char* methodname, void* value)
{
	if(aclass==nil)return;
	//prepare
	mc_method* method = (mc_method*)malloc(sizeof(mc_method));
	method->next = nil;
	method->addr = value;
	method->hash = hash(methodname);
	mc_copy_methodname(method, methodname);
	unsigned res = set_method(&(aclass->table), method, YES);
	//insert
	return res;
}

mc_message make_msg(id const obj, const void* entry)
{
	//we will return a struct
	mc_message tmpmsg = {nil, nil};
	tmpmsg.object = obj;
	tmpmsg.addr = entry;
	return tmpmsg;
}

mc_message _self_response_to(id const volatile obj, const char* methodname)
{
	//we will return a struct
	mc_message tmpmsg = {nil, nil};
	if(obj == nil || obj->isa == nil){
		error_log("_self_response_to(obj) obj is nil or obj->isa is nil. return {nil, nil}\n");
		return tmpmsg;
	}

	mc_message* res;
	if((res=get_method_by_name(&(obj->isa->table), methodname)) != nil){
		tmpmsg.object = obj;
		tmpmsg.addr = res->addr;
		return tmpmsg;
	}else{
		return tmpmsg;
	}
}

mc_message _response_to(id const volatile obj, const char* methodname)
{
	mc_message tmpmsg = {nil, nil};
	if(obj == nil || obj->isa == nil){
		error_log("_response_to(obj) obj is nil or obj->isa is nil. return {nil, nil}\n");
		return tmpmsg;
	}

	mc_object* obj_iterator = obj;
	mc_object* obj_first_hit = nil;
	mc_method* met_first_hit = nil;
	mc_method* amethod = nil;
	int hit_count = 0;
	unsigned hashval = hash(methodname);

	for(obj_iterator = obj; 
		obj_iterator!= nil;
		obj_iterator = obj_iterator->super){
		if((amethod=get_method_by_hash(&(obj_iterator->isa->table), hashval, methodname)) != nil) {
			runtime_log("hit a method [%s/%d] to match [%s]\n", 
				amethod->name, amethod->index, methodname);
			hit_count++;
			tmpmsg.object = obj_iterator;
			tmpmsg.addr = amethod->addr;
			if(obj_first_hit==nil)obj_first_hit = obj_iterator;
			if(met_first_hit==nil)met_first_hit = amethod;
			//for the method key have conflicted with some super class in inherit tree
			if(hit_count>1){
				if(hit_count==2){
					//to support the "overide" feature of oop
					if(mc_compare_methodname(met_first_hit, methodname) == 0){
						tmpmsg.object = obj_first_hit;
						runtime_log("return a message[%s/%s]\n", tmpmsg.object->isa->name, methodname);
						return tmpmsg;}
				}
				if(mc_compare_methodname(amethod, methodname) == 0){
					tmpmsg.object = obj_iterator;
					runtime_log("return a message[%s/%s]\n", tmpmsg.object->isa->name, methodname);
					return tmpmsg;}
			}
		}
	}
	if(hit_count==1)
		runtime_log("return a message[%s/%s]\n", tmpmsg.object->isa->name, methodname);
	else if(hit_count==0)
		error_log("class[%s] can not response to method[%s]\n", obj->isa->name, methodname);
	else
		//error_log("hit_count[%s]>1 but class[%s] can not response to method[%s]\n", 
		//	hit_count, obj->isa->name, methodname);
		error_log("hit_count>1 but class still can not response to method\n");
	return tmpmsg;
}

void mc_copy_methodname(mc_method* method, const char* name)
{
	strncpy(method->name, name, strlen(name)+1);
	method->name[strlen(name)+1]='\0';
	if(strlen(name)+1 >= MAX_METHOD_NAME_CHAR_NUM){
		error_log("method name[%s] length is large than Max method name char number: %d\n", 
			name, MAX_METHOD_NAME_CHAR_NUM);
		method->name[MAX_METHOD_NAME_CHAR_NUM-1]='\0';
	}
}

int mc_compare_methodname(mc_method* method, const char* name)
{
	return strncmp(method->name, name, strlen(name));
}

void mc_copy_classname(mc_class* aclass, const char* name)
{
	strncpy(aclass->name, name, strlen(name)+1);
	aclass->name[strlen(name)+1]='\0';
	if(strlen(name)+1 >= MAX_CLASS_NAME_CHAR_NUM){
		error_log("class name[%s] length is large than Max class name char number: %d\n", 
			name, MAX_CLASS_NAME_CHAR_NUM);
		aclass->name[MAX_CLASS_NAME_CHAR_NUM-1]='\0';
	}
}

int mc_compare_classname(mc_class* aclass, const char* name)
{
	return strncmp(aclass->name, name, strlen(name));
}

