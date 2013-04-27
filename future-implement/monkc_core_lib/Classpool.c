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

//public
void _init_class_list();
void _clear_class_list();

//private
static MCClass* mc_classobj_pool[MAX_CLASS_NUM];

//implements
static inline void _clear_method_list(MCClass* const class)
{
	int i;
	for (i = 0; i < MAX_METHOD_NUM; i++){
		class->method_list[i] = nil;
	}
}

MCClass* _load(const char* name_in, loaderFP loader)
{
	unsigned hashkey = _chash(name_in);
	if(mc_classobj_pool[hashkey] == nil){
		//new a class object
		MCClass* aclass = (MCClass*)malloc(sizeof(MCClass));
		_clear_method_list(aclass);
		//setting
		aclass->name = name_in;
		(*loader)(aclass);
		if(mc_classobj_pool[hashkey]==nil)
			mc_classobj_pool[hashkey] = aclass;
		else
			error_log("class[%s] is conflict with class[%s], please change a name.\n", 
				name_in, mc_classobj_pool[hashkey]->name);
	}

	return mc_classobj_pool[hashkey];
}

id _new(id const this, const char* name_in, loaderFP loader, initerFP initer)
{
	this->isa = _load(name_in, loader);
	this->saved_isa = this->isa;
	this->mode = nil;
	this->super = nil;
	(*initer)(this);
	return this;
}

void _shift(id const obj, const char* modename, loaderFP loader)
{
	unsigned modehashkey = _chash(modename);
	if(mc_classobj_pool[modehashkey] != nil
	&&mc_classobj_pool[modehashkey] == obj->mode)
		runtime_log("mode class[%s] already loaded\n", obj->mode->name);
	else
		obj->mode = _load(modename, loader);
	obj->isa = obj->mode;
	runtime_log("obj[%p/%s] shift to mode[%s]\n", 
		obj, obj->saved_isa->name, obj->isa->name);
}

void _shift_back(id const obj)
{
	obj->isa = obj->saved_isa;
	runtime_log("obj[%p/%s] shift to mode[%s]\n", 
		obj, obj->saved_isa->name, obj->isa->name);
}

void _init_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; i++)
		mc_classobj_pool[i] = nil;
}

void _clear_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; i++){
		MCClass* tmp = mc_classobj_pool[i];
		if(tmp!=nil)mc_free(tmp);
	}
}