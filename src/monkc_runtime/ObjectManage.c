/*
Copyright (c) <2013-2015>, <Sun Yuli>
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

mc_block* alloc_mc_block()
{
	return (mc_block*)malloc(sizeof(mc_block));
}

mc_block* init_mc_block(mc_block* ablock, void* data)
{
	deref(ablock).data = data;
	deref(ablock).next = nil;
	return ablock;
}

mc_block* new_mc_block(void* data)
{
	return init_mc_block(alloc_mc_block(), data);
}

void package_by_block(mc_block* ablock, mc_object* aobject)
{
	deref(ablock).data = aobject;
	deref(aobject).block = ablock;
}

mc_blockpool* new_mc_blockpool()
{
	mc_blockpool* bpool = (mc_blockpool*)malloc(sizeof(mc_blockpool));
	bpool->lock = 0;
	bpool->tail = nil;
	return bpool;
}

void pushToTail(mc_blockpool* bpool, mc_block* ablock)
{
	mc_trylock(&(bpool->lock));
	deref(ablock).next = nil;
	if(MC_NO_NODE(bpool)){
		deref(bpool).tail = ablock;
		deref(ablock).next = ablock;
	}else{
		mc_block* head = bpool->tail->next;
		deref(deref(bpool).tail).next = ablock;
		deref(ablock).next = head;
		deref(bpool).tail = bpool->tail->next;
	}
	mc_unlock(&(bpool->lock));
}

mc_block* getFromHead(mc_blockpool* bpool)
{
	mc_block *target, *H, *HN;
	mc_trylock(&(bpool->lock));
	target = nil;
	if(MC_NO_NODE(bpool)){
		target=nil;
	}else if(MC_ONE_NODE(bpool)){
		target=bpool->tail;
		deref(bpool).tail = nil;
	}else{
		target=bpool->tail->next;
		H = bpool->tail->next;
		HN = H->next;
		deref(deref(bpool).tail).next = HN;
	}
	mc_unlock(&(bpool->lock));
	return target;
}

void empty(mc_blockpool* bpool)
{
	mc_block* target;
	while((target=getFromHead(bpool)) != nil){
		fs((mo)(target->data), bye, nil);
		free(target->data);
		free(target);
	}
}

int count(mc_blockpool* bpool)
{
	int i = 1;
	mc_block* H;
	if(deref(bpool).tail==nil)
		return 0;
	H = deref(bpool).tail->next;
	for(;H!=deref(bpool).tail ;H=H->next){
		i++;
	}
	return i;
}

//will output a new block
int cut(mc_blockpool* bpool, mc_block* ablock, mc_block** result)
{
	int res = 0;//success
	mc_block* NN;
	//assume parameter is all checked outside
	mc_trylock(&(bpool->lock));
 	if(MC_NO_NODE(bpool)){
		error_log("no node in used_pool but you request delete\n");
		deref(result)=nil;
		res=-1;//fail
	}else if(MC_ONE_NODE(bpool)){
		deref(bpool).tail=nil;
		deref(ablock).next=nil;
		deref(result)=ablock;
	}else if(MC_TWO_NODE(bpool)){//do not swap data
		if(deref(ablock).next==nil){
			error_log("block not in the pool, refuse to cut\n");
			res=-1;//fail
		}else{
			mc_block* H = deref(bpool).tail->next;
			mc_block* T = deref(bpool).tail;
			if(ablock==bpool->tail){//cut tail
				deref(T).next=nil;
				deref(result)=T;
				deref(bpool).tail=H;
				deref(H).next=H;
			}else{//cut head
				deref(H).next=nil;
				deref(result)=H;
				deref(T).next=T;
			}
		}
	}else{
		if(deref(ablock).next==nil){
			error_log("block not in the pool, refuse to cut\n");
			res=-1;//fail
		}else{
			if(deref(ablock).next==bpool->tail)//don not delete the tail!
				deref(bpool).tail = ablock;
			NN = ablock->next->next;
			//result
			deref(deref(ablock).next).next = nil;
			deref(result) = deref(ablock).next;
			//swap
			package_by_block(ablock, ablock->next->data);
			deref(ablock).next = NN;
		}
	}
	mc_unlock(&(bpool->lock));
	return res;
}

void mc_info(const char* classname, size_t size, loaderFP loader)
{
	mc_info_h(classname, size, loader, hash(classname));
}

void mc_info_h(const char* classname, size_t size, loaderFP loader, unsigned hashval)
{
	mc_class* aclass = _load_h(classname, size, loader, hashval);
	debug_log("----info[%s] used:%d/free:%d\n", 
		classname, count(aclass->used_pool), count(aclass->free_pool));
}

void mc_clear(const char* classname, size_t size, loaderFP loader)
{
	mc_clear_h(classname, size, loader, hash(classname));
}

void mc_clear_h(const char* classname, size_t size, loaderFP loader, unsigned hashval)
{
	mc_class* aclass = _load_h(classname, size, loader, hashval);
	if(aclass->used_pool!=nil && aclass->used_pool->tail!=nil)
		empty(aclass->used_pool);
	else
		runtime_log("class[%s] used_pool have no node. check free_pool\n", classname);
	if(aclass->free_pool->tail!=nil)
		empty(aclass->free_pool);
	else
		runtime_log("class[%s] free_pool also have no node. do not clear\n", classname);
	runtime_log("empty [%s] finish\n", classname);
}

//always return a object of size. packaged by a block.
mo mc_alloc(const char* classname, size_t size, loaderFP loader)
{
	return mc_alloc_h(classname, size, loader, hash(classname));
}

mo mc_alloc_h(const char* classname, size_t size, loaderFP loader, unsigned hashval)
{
	mc_class* aclass = _load_h(classname, size, loader, hashval);
	mc_blockpool* fp = aclass->free_pool;
	mc_blockpool* up = aclass->used_pool;
	mc_block* ablock = nil;
	mo aobject = nil;
	if((ablock=getFromHead(fp)) == nil){
		//new a object package by a block
		aobject = (mo)malloc(size);
		aobject->isa = aclass;
		aobject->saved_isa = aclass;
		//new a block
		ablock = new_mc_block(nil);
		package_by_block(ablock, aobject);
		runtime_log("----alloc[NEW:%s]: new alloc a block[%p obj[%p]]\n", 
			classname, ablock, ablock->data);
	}else{
		aobject = (mo)(ablock->data);
		runtime_log("----alloc[REUSE:%s]: find a block[%p obj[%p]]\n",
			classname, ablock, ablock->data);
	}
	pushToTail(up, ablock);
	return aobject;
}

void mc_dealloc(mc_object* aobject, int is_recycle)
{
	mc_block* blk = aobject->block;
	mc_class* cls = aobject->isa;
	mc_blockpool* fp = cls->free_pool;
	mc_blockpool* up = cls->used_pool;
	mc_block* nb = nil;

	if(aobject==nil){
		error_log("----dealloc(%s) obj is nil\n", nameof(aobject));
		return;
	}
	if(blk==nil){
		error_log("----dealloc(%s) obj->block is nil\n", nameof(aobject));
		return;
	}
	if(cls==nil){
		error_log("----dealloc(%s) obj->isa is nil\n", nameof(aobject));
		return;
	}
	if(fp==nil || up==nil){
		error_log("----dealloc(%s) obj->isa->pool is nil\n", nameof(aobject));
		return;
	}
	if(MC_NO_NODE(up)){
		error_log("----dealloc(%s) have no block used, but you request dealloc\n", nameof(aobject));
		return;
	}
	//dealloc start
	if(!cut(up, blk, &nb))//success
	{
		if(is_recycle==1){
			package_by_block(nb, aobject);
			pushToTail(fp, nb);
			runtime_log("----dealloc[BACK:%s]: push back a block[%p obj[%p]]\n", nameof(aobject), blk, aobject);
		}else{
            runtime_log("----dealloc[DEL:%s]: delete a block[%p obj[%p]]\n", nameof(aobject), blk, aobject);
			free(nb->data);
			free(nb);
		}
	}
}





