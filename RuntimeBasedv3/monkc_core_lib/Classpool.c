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

//extern
//extern pthread_mutex_t _mc_runtime_mutex;

//public
BOOL set_class(id const self_in, const char* classname, const char* superclassname);

void MCObject_doNothing(id const this, const char* methodname, xxx);
void MCObject_bye(id this, const char* methodname, xxx);
id MCObject_init(id const this, const char* methodname, xxx);
void MCObject_whatIsYourClassName(id const this, const char* methodname, xxx);

void _init_class_list();
void _clear_class_list();

//private
static MCClass* mc_classobj_pool[MAX_CLASS_NUM];
static inline void _clear_method_list(MCClass* const class);
static MCClass* load_class(const char* name_in, const char* super_class);
static inline MCClass* _get_class(const char* name_in);
static void _load_root_class();

//implements
static inline void _clear_method_list(MCClass* const class)
{
	int i;
	for (i = 0; i < MAX_METHOD_NUM; i++){
		class->method_list[i] = nil;
	}
}

static MCClass* load_class(const char* name_in, const char* super_class)
{
	//pthread_mutex_lock(&_mc_runtime_mutex);
	MCClass* oldclass;
	if ((oldclass=_get_class(name_in)) != nil){
		error_log("class name:%s hash is conflict with class name:%s hash.\n", name_in, oldclass->name);
		exit(-1);
	}

	int super_hashkey = _chash(super_class);

	MCClass* superclass = mc_classobj_pool[super_hashkey];
	if(superclass == nil){
		error_log("there is no superclass %s.please load it first!\n", super_class);
		exit(-1);
	}

	MCClass* class = (MCClass*)malloc(sizeof(MCClass));

	//set the class name
	class->name = name_in;
	class->super = superclass;
	class->method_count = 0;

	//conflict check
	int hashkey = _chash(name_in);
	if(mc_classobj_pool[hashkey] != nil){
		error_log("load_class(%s, %s) - name hash value conflict.\nplease change a name\n", name_in, super_class);
		exit(-1);
	}

	_clear_method_list(class);
	//all thread will do the same operation no need lock free
	mc_classobj_pool[hashkey] = class;
	//pthread_mutex_unlock(&_mc_runtime_mutex);
	return class;
}

static inline MCClass* _get_class(const char* name_in)
{
	int hashkey = _chash(name_in);
	return mc_classobj_pool[hashkey];
}

BOOL set_class(id const self_in, const char* classname, const char* superclassname)
{
	if (self_in == nil)
	{
		error_log("set_class(obj, classname).obj should not be nil\n");
		exit(-1);
	}

	if(self_in->need_bind_method != YES){
		runtime_log("super_init: %s no need bind methods\n",classname);
		return NO;
	}

	runtime_log("set_class: %s->%s\n", classname ,superclassname);

	//all thread will do the same operation no need lock free
	//load class
	MCClass* class;
	if ((class = _get_class(classname)) != nil)
	{
		runtime_log("class: %s already loaded\n",classname);
		self_in->isa = class;
		return NO;
	}else{
		runtime_log("load_class: %s\n", classname);
		class = load_class(classname, superclassname);
		self_in->isa = class;
		return YES;
	}
}

void MCObject_doNothing(id const this, const char* methodname, xxx)
{
	//do nothing
}

void MCObject_bye(id this, const char* methodname, xxx)
{
	//do nothing
}

id MCObject_init(id const this, const char* methodname, xxx)
{
	//do nothing
	this->isa = _get_class("MCObject");
	return this;
}

void MCObject_whatIsYourClassName(id const this, const char* methodname, xxx)
{
	if(this != nil && this->isa != nil)
		debug_log("My class name is:%s\n", this->isa->name);
}

static void _load_root_class()
{
	MCClass* class = (MCClass*)malloc(sizeof(MCClass));
	class->name = "MCObject";
	class->super = nil;
	//bind the builtin MCObject methods
	MCMethod* met1 = (MCMethod*)malloc(sizeof(MCMethod));
	MCMethod* met2 = (MCMethod*)malloc(sizeof(MCMethod));
	MCMethod* met3 = (MCMethod*)malloc(sizeof(MCMethod));
	//init
	met1->addr = MCObject_doNothing;
	met1->name = "doNothing";
	met2->addr = MCObject_whatIsYourClassName;
	met2->name = "whatIsYourClassName";
	met3->addr = MCObject_bye;
	met3->name = "bye";
	//bind
	class->method_list[_hash("doNothing")]=met1;
	class->method_list[_hash("whatIsYourClassName")]=met2;
	class->method_list[_hash("bye")]=met3;
	//load the MCObject class
	mc_classobj_pool[_chash("MCObject")] = class;
}

void _init_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; i++){
		mc_classobj_pool[i] = nil;
	}

	_load_root_class();
}

void _clear_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; i++){
		MCClass* tmp = mc_classobj_pool[i];
		if(tmp!=nil)mc_free(tmp);
	}
}
