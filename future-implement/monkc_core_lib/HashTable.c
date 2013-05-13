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
unsigned hash(const char *s);
void init_class_table();
void init_table(MCHashTable** const table_p, unsigned initlevel);
void expand_table(MCHashTable** const table_p, unsigned tolevel);
unsigned set_method(MCHashTable** const table_p, MCMethod** const method_p, BOOL isOverride);
unsigned set_class(const MCClass* aclass);
unsigned get_size_by_level(const unsigned level);
unsigned get_index_by_hash(const MCHashTable** table_p, const unsigned hashval, unsigned* resultlevel);
unsigned get_index_by_name(const MCHashTable** table_p, const char* name, unsigned* resultlevel);
MCMethod* get_method_by_name(const MCHashTable** table_p, const char* name);
MCMethod* get_method_by_hash(const MCHashTable** table_p, const unsigned hashval);
MCMethod* get_method_by_index(const MCHashTable** table_p, const unsigned index);
MCClass* get_class_by_name(const char* name);
MCClass* get_class_by_hash(const unsigned hashval);
MCClass* get_class_by_index(const unsigned index);

//private
static MCHashTable* mc_class_table;
static unsigned mc_table_sizes[5] = {101, 401, 1001, 2001, 4001};

/*
	Tools Part: Hash and nil pointer check
*/

//copy form << The C Programming language >>
//BKDR Hash Function
unsigned hash(const char *s)
{
	//runtime_log("hash(%s) --- ", s);
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	//runtime_log("hashval is: %d\n", hashval);
	return hashval;
}

void init_table(MCHashTable** const table_p, unsigned initlevel)
{
	unsigned i;
	for (i = 0; i < mc_table_sizes[(*table_p)->level]; i++)
		((*table_p)->data)[i]=nil;
	(*table_p)->level = initlevel;
}

void init_class_table()
{
	size_t newsize = sizeof(MCHashTable) + mc_table_sizes[0]*sizeof(MCMethod*);
	mc_class_table = (MCHashTable*)malloc(newsize);
	init_table(&mc_class_table, 0);
}

void expand_table(MCHashTable** const table_p, unsigned tolevel)
{
	unsigned oldlevel = (*table_p)->level;
	size_t newsize = sizeof(MCHashTable) + mc_table_sizes[tolevel]*sizeof(MCMethod*);
	size_t oldsize = sizeof(MCHashTable) + mc_table_sizes[oldlevel]*sizeof(MCMethod*);
	//reallocation
	MCHashTable* newtable = (MCHashTable*)realloc((*table_p), newsize);
	init_table(&newtable, tolevel);
	mc_atomic_set_pointer(table_p, newtable);
	error_log("expand table: %d->%d\n", oldlevel, (*table_p)->level);
}

unsigned get_size_by_level(const unsigned level)
{
	return mc_table_sizes[level];
}

unsigned get_index_by_hash(const MCHashTable** table_p, const unsigned hashval, unsigned* resultlevel)
{
	unsigned index, level;
	for(level = 0; level<5; level++){
		index = hashval % mc_table_sizes[level];
		if((*table_p)->data[index] == nil){
			(*resultlevel) = level;
			return index;
		}
	}
	return 65535;
	//this should always success
}

unsigned get_index_by_name(const MCHashTable** table_p, const char* name, unsigned* resultlevel)
{
	unsigned hashval = hash(name);
	return get_index_by_hash(table_p, hashval, resultlevel);
}

unsigned set_method(MCHashTable** const table_p, MCMethod** const method_p, BOOL isOverride)
{
	unsigned level, oldlevel;
	oldlevel = (*table_p)->level;
	unsigned index = get_index_by_name(table_p, (*method_p)->name, &level);
	MCMethod* oldmethod;
	if((oldmethod=(*table_p)->data[index]) == nil){
		if(oldlevel < level)
			expand_table(table_p, level);
		mc_atomic_set_integer(&((*method_p)->index), index);
		mc_atomic_set_pointer(&((*table_p)->data[index]), (*method_p));
		runtime_log("binding a method[%s/%d]\n", (*method_p)->name, index);
		return index;
	}else{
		//if the method have already been setted. we free the old method
		if(mc_compareMethodName(oldmethod, (*method_p)->name) == 0){
			if(isOverride==NO){
				error_log("binding method [%s] already been setted, free temp method\n", (*method_p)->name);
				free(*method_p);
			}else{
				error_log("override method [%s] already been setted, replace old method\n", (*method_p)->name);
				free(oldmethod);
				mc_atomic_set_integer(&((*method_p)->index), index);
				mc_atomic_set_pointer(&((*table_p)->data[index]), (*method_p));
			}
			return index;
		}
	}
}

unsigned set_class(const MCClass* aclass)
{
	unsigned level;
	unsigned index = get_index_by_name(mc_class_table, aclass->name, &level);
	MCClass* oldclass;
	if((oldclass=mc_class_table->data[index]) == nil){
		if(mc_class_table->level < level)
			expand_table(&mc_class_table, level);
		mc_atomic_set_pointer(&(mc_class_table->data[index]), aclass);
		return index;
	}else{
		//clean old class ?
	}
}

MCMethod* get_method_by_name(const MCHashTable** table_p, const char* name)
{
	unsigned hashval = hash(name);
	//try get index
	return get_method_by_hash(table_p, hashval);
}

MCMethod* get_method_by_hash(const MCHashTable** table_p, const unsigned hashval)
{
	unsigned level;
	MCMethod* res;
	for(level = 0; level<5; level++){
		if((res=get_method_by_index(table_p, hashval % mc_table_sizes[level])) != nil)
			return res;
	}
	return nil;
}

MCMethod* get_method_by_index(const MCHashTable** table_p, const unsigned index)
{
	if(index > mc_table_sizes[(*table_p)->level])
		return nil;
	if((*table_p)->data[index] != nil)
		return (*table_p)->data[index];
	else
		return nil;
}

MCClass* get_class_by_name(const char* name)
{
	unsigned hashval = hash(name);
	//try get index
	return get_class_by_hash(hashval);
}

MCClass* get_class_by_hash(const unsigned hashval)
{
	unsigned level;
	MCClass* res;
	for(level = 0; level<5; level++){
		if((res=get_class_by_index(hashval % mc_table_sizes[level])) != nil)
			return res;
	}
	return nil;
}

MCClass* get_class_by_index(const unsigned index)
{
	if(index > mc_table_sizes[mc_class_table->level])
		return nil;
	if(mc_class_table->data[index] != nil)
		return mc_class_table->data[index];
	else
		return nil;
}

MCClass* _load(const char* name_in, loaderFP loader)
{
	unsigned level;
	unsigned index = get_index_by_name(&mc_class_table, name_in, &level);
	if(mc_class_table->data[index] == nil){
		//new a class object
		MCClass* aclass = (MCClass*)malloc(sizeof(MCClass));
		MCHashTable* atable = (MCHashTable*)malloc(sizeof(MCHashTable)
			+mc_table_sizes[0]*sizeof(MCMethod*));
		init_table(&atable, 0);
		aclass->table = atable;
		//setting
		mc_copyClassName(aclass, name_in);
		(*loader)(aclass);
		mc_atomic_set_pointer(&mc_class_table->data[index], aclass);
	}
	runtime_log("load a class[%s/index=%d/level=%d]\n", 
		mc_class_table->data[index]->name, index, mc_class_table->level);
	return mc_class_table->data[index];
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
	unsigned level;
	unsigned index = get_index_by_name(&mc_class_table, modename, &level);
	if(mc_class_table->data[index] != nil
	&&mc_class_table->data[index] == obj->mode)
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