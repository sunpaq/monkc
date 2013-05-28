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

/*
	Memory Allocators

	alternative allocators in APUE
	1. libmalloc
	2. vmalloc
	3. quick-fit
	4. alloca ---> can alloc mem on stack
*/

// typedef struct mc_block_struct
// {
// 	struct mc_block_struct* next;
// 	void* data;
// }mc_block;

inline mc_block* alloc_mc_block()
{
	return (mc_block*)malloc(sizeof(mc_block));
}

mc_block* init_mc_block(mc_block* ablock, void* data)
{
	ablock->data = data;
	ablock->next = nil;
	return ablock;
}

mc_block* new_mc_block(void* data)
{
	return init_mc_block(alloc_mc_block(), data);
}

mc_block* new_block_withobject(mc_object* aobject)
{
	mc_block* ablock = new_mc_block(aobject);
	aobject->block = ablock;
	return ablock;
}

// typedef struct mc_blockpool_struct
// {
// 	int lock;
// 	mc_block* head;
// 	mc_block* first;
// 	mc_block* tail;
// }mc_blockpool;

mc_blockpool* new_mc_blockpool()
{
	mc_blockpool* bpool = (mc_blockpool*)malloc(sizeof(mc_blockpool));
	bpool->lock = 0;
	bpool->head = nil;
	bpool->first = nil;
	bpool->tail = nil;
	return bpool;
}

//FIXME
static void* bpool_alloc(mc_blockpool* bpool)
{
	//try lock spin lock
	mc_trylock(&(bpool->lock));
	void* data;
	if(bpool->head!=nil && (bpool->head!=bpool->first)){
		mc_block* target = bpool->head;
		bpool->head = bpool->head->next;
		bpool->tail->next = target;
		bpool->tail = bpool->tail->next;
		data = target->data;
	}else{
		data=nil;
	}
	mc_unlock(&(bpool->lock));
	return data;
}

static void bpool_dealloc(mc_object* aobject)
{
	if(aobject==nil){
		error_log("bpool_dealloc(obj) obj is nil\n");
		return;
	}
	if(aobject->block==nil){
		error_log("bpool_dealloc(obj) obj->block is nil\n");
		return;
	}
	if(aobject->isa==nil){
		error_log("bpool_dealloc(obj) obj->isa is nil\n");
		return;
	}
	if(aobject->isa->pool==nil){
		error_log("bpool_dealloc(obj) obj->isa->pool is nil\n");
		return;
	}

	mc_class* aclass = aobject->isa;
	mc_blockpool* bpool = aclass->pool;
	mc_block* ablock = aobject->block;
	//try lock spin lock
	mc_trylock(&(bpool->lock));
	if(ablock==bpool->first){
		if(ablock->next == nil){
			bpool->first = nil;
			bpool->tail = ablock;
		}else{
			bpool->first = ablock->next;
		}
	}else{
		mc_block* target = ablock;
		ablock->data = bpool->first->data;
		bpool->first->data = target->data;
		bpool->first = ablock->next;
	}
	mc_unlock(&(bpool->lock));
	return;
}

static void* bpool_insert(mc_blockpool* bpool, mc_block* ablock)
{
	mc_trylock(&(bpool->lock));
	if(bpool->head == nil){
		//set the block
		bpool->head = ablock;
		bpool->first = ablock;
		bpool->tail = ablock;
		mc_unlock(&(bpool->lock));
		return ablock->data;
	}else{
		bpool->tail->next = ablock;
		bpool->tail = ablock;
		mc_unlock(&(bpool->lock));
		return ablock->data;
	}
}

static void bpool_freeall(mc_blockpool* bpool)
{
	mc_trylock(&(bpool->lock));
		mc_block* hb=bpool->head;
		mc_block* tb=bpool->tail;
		mc_block* fb=bpool->first;
		mc_block* tmp;

		for(;hb!=tb; hb=hb->next){
			tmp = hb;
			mc_object* obj = (mc_object*)tmp->data;
			_push_jump(_self_response_to(obj, "bye"), nil);
			//if(obj!=nil)free(obj);
			//if(tmp!=nil)free(tmp);
		}
	mc_unlock(&(bpool->lock));
}

mc_object* new_mc_object(mc_class* const aclass)
{
	mc_object* aobject = (mc_object*)malloc(aclass->objsize);
	aobject->ref_count = 1;
	aobject->isa = aclass;
	return aobject;
}

void* _alloc(const char* classname, size_t size, loaderFP loader)
{
	mc_class* aclass = _load(classname, size, loader);
	void* reused;
	if((reused=bpool_alloc(aclass->pool)) == nil){
		mc_object* aobject = new_mc_object(aclass);
		mc_block* ablock = new_block_withobject(aobject);
		bpool_insert(aclass->pool, ablock);
		reused = (void*)aobject;
		runtime_log("----alloc[%p/NEW]: new alloc a instance[%s]\n", reused, classname);
	}else{
		runtime_log("----alloc[%p]: find a instance to reuse[%s]\n", reused, classname);
	}
	return reused;
}

void _dealloc(mc_object* aobject)
{
	runtime_log("----dealloc[%p]: push back a instance[%s]\n", aobject, nameof(aobject));
	bpool_dealloc(aobject);
}

void _clear(const char* classname, size_t size, loaderFP loader)
{
	mc_class* aclass = _load(classname, size, loader);
	bpool_freeall(aclass->pool);
}


