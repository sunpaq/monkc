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
unsigned set_method(MCHashTable** const table_p, MCMethod* const method, BOOL isOverride);
unsigned set_class(MCClass* const aclass);
unsigned get_size_by_level(const unsigned level);
MCMethod* get_method_by_name(const MCHashTable** table_p, const char* name);
MCMethod* get_method_by_hash(const MCHashTable** table_p, const unsigned hashval, const char* refname);
MCMethod* get_method_by_index(const MCHashTable** table_p, const unsigned index);
MCClass* get_class_by_name(const char* name);
MCClass* get_class_by_hash(const unsigned hashval, const char* refname);
MCClass* get_class_by_index(const unsigned index);

//private
static MCHashTable* mc_class_table;
static unsigned mc_table_sizes[5] = {100, 200, 1000, 4000, 10000};

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
	newtable->level = tolevel;
	unsigned i;
	for(i=mc_table_sizes[oldlevel]+1; i<mc_table_sizes[tolevel]; i++)
		newtable->data[i]=nil;
	mc_atomic_set_pointer(table_p, newtable);
	error_log("expand table: %d->%d\n", oldlevel, (*table_p)->level);
}

unsigned get_size_by_level(const unsigned level)
{
	return mc_table_sizes[level];
}

unsigned set_method(MCHashTable** const table_p, MCMethod* const method, BOOL isOverride)
{
	unsigned hashval = method->hash;
	unsigned index = hashval % mc_table_sizes[(*table_p)->level];
	MCMethod* oldmethod;
	if((oldmethod=(*table_p)->data[index]) == nil){
		mc_atomic_set_integer(&(method->index), index);
		mc_atomic_set_pointer(&((*table_p)->data[index]), method);
		runtime_log("binding a method[%s/%d]\n", method->name, index);
		method->level = (*table_p)->level;
		method->index = index;
		return index;
	}else{
		//if the method have already been setted. we free the old method
		if(mc_compareMethodName(oldmethod, method->name) == 0){
			if(isOverride==NO){
				error_log("binding method [%s] already been setted, free temp method\n", method->name);
				free(method);
			}else{
				error_log("override method [%s] already been setted, replace old method\n", method->name);
				free(oldmethod);
				mc_atomic_set_integer(&(method->index), index);
				mc_atomic_set_pointer(&((*table_p)->data[index]), method);
			}
			method->level = (*table_p)->level;
			method->index = index;
			return index;
		//conflict with other method. we expand the table and try again. until success
		}else{
			if(oldmethod->hash == method->hash){
				error_log("hash conflict new[%s/%d]<->old[%s/%d]\n", 
					method->name, method->hash,
					oldmethod->name, oldmethod->hash);
			}else{
				error_log("index conflict new[%s/%d]<->old[%s/%d]\n",
					method->name, index,
					oldmethod->name, index);
			}
			unsigned tmplevel = (*table_p)->level+1;
			if(tmplevel<5){
				expand_table(table_p, tmplevel);
				set_method(table_p, method, isOverride);
			}else{
				//tmplevel = 5, table_p must have been expanded to level 4
				//there still a oldmethod, use link list.
				error_log("method name conflict can not be soloved. link the new one behind the old\n");
				method->level = 4;
				method->index = index;
				oldmethod->next = method;
				return index;
			}
		}
	}
}

unsigned set_class(MCClass* const aclass)
{
	unsigned hashval = aclass->hash;
	unsigned index = hashval % mc_table_sizes[mc_class_table->level];
	MCClass* oldclass;
	if((oldclass=mc_class_table->data[index]) == nil){
		mc_atomic_set_pointer(&(mc_class_table->data[index]), aclass);
		aclass->level = mc_class_table->level;
		aclass->index = index;
		return index;
	}else{
		//this class have already setted.
		if(mc_compareClassName(oldclass, aclass->name) == 0){
			error_log("class[%s] already been binded. do nothing\n", aclass->name);
			aclass->level = mc_class_table->level;
			aclass->index = index;
			return index;
		//conflict with other class. we expand class table until success.
		}else{
			if(oldclass->hash == aclass->hash){
				error_log("hash conflict new[%s/%d]<->old[%s/%d]\n", 
					aclass->name, aclass->hash,
					oldclass->name, oldclass->hash);
			}else{
				error_log("index conflict new[%s/%d]<->old[%s/%d]\n",
					aclass->name, index,
					oldclass->name, index);
			}
			unsigned tmplevel = aclass->level+1;
			if(tmplevel<5){
				expand_table(&mc_class_table, tmplevel);
				set_class(aclass);
			}else{
				//tmplevel = 5, table_p must have been expanded to level 4
				//there still a oldmethod, use link list.
				error_log("method name conflict can not be soloved. link the new one behind the old\n");
				aclass->level = 4;
				aclass->index = index;
				oldclass->next = aclass;
				return index;
			}
		}
	}
}

MCMethod* get_method_by_name(const MCHashTable** table_p, const char* name)
{
	unsigned hashval = hash(name);
	//try get index
	return get_method_by_hash(table_p, hashval, name);
}

MCMethod* get_method_by_hash(const MCHashTable** table_p, const unsigned hashval, const char* refname)
{
	unsigned level;
	MCMethod* res;
	//level<4
	for(level = 0; level<4; level++){
		if((res=get_method_by_index(table_p, hashval % mc_table_sizes[level])) == nil)
			continue;
		if(res->level != level)
			continue;
		if(res->hash != hashval)
			continue;
		//pass all the check
		return res;
	}
	//level=4
	if((res=get_method_by_index(table_p, hashval % mc_table_sizes[4])) == nil)
		return nil;
	if(res->level != 4)
		return nil;
	if(res->hash != hashval)
		return nil;
	if(res->next == nil)
		return nil;
	//pass all the check. search conflicted method
	for(; res!=nil; res=res->next)
		if(mc_compareMethodName(res, refname)==0){
			runtime_log("name hit a method [%s/%d/%d/%d]\n", 
			res->name, res->index, res->hash, 4);
			return res;
		}
	//no matched method
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
	return get_class_by_hash(hashval, name);
}

MCClass* get_class_by_hash(const unsigned hashval, const char* refname)
{
	unsigned level;
	MCClass* res;
	//level<4
	for(level = 0; level<4; level++){
		if((res=get_class_by_index(hashval % mc_table_sizes[level])) == nil)
			continue;
		if(res->level != level)
			continue;
		if(res->hash != hashval)
			continue;
		//pass all the check
		return res;
	}
	//level=4
	if((res=get_class_by_index(hashval % mc_table_sizes[4])) == nil)
		return nil;
	if(res->level != 4)
		return nil;
	if(res->hash != hashval)
		return nil;
	if(res->next == nil)
		return nil;
	//pass all the check. search conflicted method
	for(; res!=nil; res=res->next)
		if(mc_compareClassName(res, refname)==0){
			runtime_log("name hit a class [%s/%d/%d/%d]\n", 
			res->name, res->index, res->hash, 4);
			return res;
		}
	//no matched class
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
	MCClass* aclass;
	if((aclass=get_class_by_name(name_in)) == nil){
		//new a class object
		aclass = (MCClass*)malloc(sizeof(MCClass));
		MCHashTable* atable = (MCHashTable*)malloc(sizeof(MCHashTable)
			+mc_table_sizes[0]*sizeof(MCMethod*));
		init_table(&atable, 0);
		aclass->table = atable;
		aclass->hash = hash(name_in);
		aclass->next = nil;
		mc_copyClassName(aclass, name_in);
		(*loader)(aclass);
		set_class(aclass);
		runtime_log("load a class[%s]\n", name_in);
	}else{
		//runtime_log("already load class[%s]\n", name_in);
	}
	return aclass;
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

id _new_category(id const this, 
	const char* name_origin, loaderFP loader, initerFP initer,
	const char* name_cat, loaderFP loader_cat, initerFP initer_cat)
{
	this->isa = _load(name_origin, loader);
	(*loader_cat)(this->isa);
	this->saved_isa = this->isa;
	this->mode = nil;
	this->super = nil;
	(*initer)(this);
	(*initer_cat)(this);
	return this;
}


void _shift(id const obj, const char* modename, loaderFP loader)
{
	MCClass* aclass = _load(modename, loader);
	if(obj->mode != aclass)
		obj->mode = aclass;
	//switch to mode
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