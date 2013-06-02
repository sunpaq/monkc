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

mc_block* alloc_mc_block()
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

void package_by_block(mc_block** ablock_p, mc_object** aobject_p)
{
	deref(ablock_p)->data = deref(aobject_p);
	deref(aobject_p)->block = deref(ablock_p);
}

mc_blockpool* new_mc_blockpool()
{
	mc_blockpool* bpool = (mc_blockpool*)malloc(sizeof(mc_blockpool));
	bpool->lock = 0;
	bpool->tail = nil;
	return bpool;
}

#define NO_NODE(bpool) (bpool->tail==nil)
#define ONE_NODE(bpool) (bpool->tail->next==bpool->tail) 
#define TWO_NODE(bpool) (bpool->tail->next->next==bpool->tail)

static void pushToTail(mc_blockpool* bpool, mc_block* ablock)
{
	mc_trylock(&(bpool->lock));
	ablock->next=nil;
	if(NO_NODE(bpool)){
		bpool->tail=ablock;
		ablock->next=ablock;
	}else{
		mc_block* head = bpool->tail->next;
		bpool->tail->next=ablock;
		ablock->next=head;
		bpool->tail=bpool->tail->next;
	}
	mc_unlock(&(bpool->lock));
}

static mc_block* getFromHead(mc_blockpool* bpool)
{
	mc_trylock(&(bpool->lock));
	mc_block* target = nil;
	if(NO_NODE(bpool)){
		target=nil;
	}else if(ONE_NODE(bpool)){
		target=bpool->tail;
		bpool->tail=nil;
	}else{
		target=bpool->tail->next;
		mc_block* H = bpool->tail->next;
		mc_block* HN = H->next;
		bpool->tail->next = HN;
	}
	mc_unlock(&(bpool->lock));
	return target;
}

static void empty(mc_blockpool* bpool)
{
	mc_block* target;
	while((target=getFromHead(bpool)) != nil){
		fs((id)(target->data), bye, nil);
		free(target->data);
		free(target);
	}
}

static int count(mc_blockpool* bpool)
{
	mc_block* T = bpool->tail;
	if(T==nil)
		return 0;
	mc_block* H = T->next;
	int i = 1;
	for(;H!=T ;H=H->next){
		i++;
	}
	return i;
}

//will output a new block
static int cut(mc_blockpool* bpool, mc_block* ablock, mc_block** result)
{
	mc_trylock(&(bpool->lock));
	int res;
	if(NO_NODE(bpool)){
		error_log("no node in used_pool but you request delete\n");
		*result=nil;
		res=-1;//fail
	}else if(ONE_NODE(bpool)){
		bpool->tail=nil;
		*result=ablock;
		res=0;//success
	}else if(TWO_NODE(bpool)){
		if(ablock==bpool->tail){//cut tail
			*result=bpool->tail;
			bpool->tail=ablock->next;
			bpool->tail->next=bpool->tail;
		}else{//cut head
			*result=bpool->tail->next;
			bpool->tail->next=bpool->tail;
		}
	}else{
		if(ablock->next==bpool->tail)//don not delete the tail!
			bpool->tail=ablock;
		mc_block* B = ablock;
		mc_block* N = B->next;
		mc_block* NN = N->next;
		//swap data
		void* tmpdata = B->data;
		B->data = N->data;
		N->data = tmpdata;
		//cut target
		B->next = NN;
		*result=N;
		res=0;//success
	}
	mc_unlock(&(bpool->lock));
	return res;
}

void _info(const char* classname, size_t size, loaderFP loader)
{
	mc_class* aclass = _load(classname, size, loader);
	debug_log("----info[%s] used:%d/free:%d\n", 
		classname, count(aclass->used_pool), count(aclass->free_pool));
}

void _clear(const char* classname, size_t size, loaderFP loader)
{
	runtime_log("empty [%s] ...\n", classname);
	mc_class* aclass = _load(classname, size, loader);
	if(aclass->used_pool==nil){
		error_log("class[%s] used_pool is nil. do not clear\n", classname);
		return;
	}
	if(aclass->used_pool->tail==nil){
		error_log("class[%s] used_pool have no node. do not clear\n", classname);
		return;
	}else{
		empty(aclass->used_pool);
	}
	if(aclass->free_pool->tail==nil){
		runtime_log("class[%s] free_pool have no node. do not clear\n", classname);
		return;
	}else{
		empty(aclass->free_pool);
	}
	runtime_log("empty [%s] finish\n", classname);
}

//always return a object of size. packaged by a block.
id _alloc(const char* classname, size_t size, loaderFP loader)
{
	mc_class* aclass = _load(classname, size, loader);
	mc_blockpool* fp = aclass->free_pool;
	mc_blockpool* up = aclass->used_pool;
	mc_block* ablock = nil;
	id aobject = nil;
	if((ablock=getFromHead(fp)) == nil){
		//new a object package by a block
		aobject = (id)malloc(size);
		aobject->isa = aclass;
		aobject->saved_isa = aclass;
		//new a block
		ablock = new_mc_block(nil);
		package_by_block(&ablock, &aobject);
		runtime_log("----alloc[NEW:%s]: new alloc a block[%p obj[%p]]\n", 
			classname, ablock, ablock->data);
	}else{
		aobject = (id)(ablock->data);
		runtime_log("----alloc[REUSE:%s]: find a block[%p obj[%p]]\n",
			classname, ablock, ablock->data);
	}
	pushToTail(up, ablock);
	return aobject;
}

void _dealloc(mc_object* aobject)
{
	mc_block* blk = aobject->block;
	mc_class* cls = aobject->isa;
	mc_blockpool* fp = cls->free_pool;
	mc_blockpool* up = cls->used_pool;
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
	if(NO_NODE(up)){
		error_log("----dealloc(%s) have no block used, but you request dealloc\n", nameof(aobject));
		return;
	}
	runtime_log("----dealloc[BACK:%s]: push back a block[%p obj[%p]]\n", nameof(aobject), blk, aobject);
	//dealloc start
	mc_block* nb;
	if(!cut(up, blk, &nb))//success
		pushToTail(fp, nb);
}

void test_blockpool()
{
	mc_blockpool* pool = new_mc_blockpool();
	mc_block *b1, *b2, *b3, *b4, *b5, *b6, *tb;
	b1=new_mc_block(nil);
	b2=new_mc_block(nil);
	b3=new_mc_block(nil);
	b4=new_mc_block(nil);
	b5=new_mc_block(nil);
	b6=new_mc_block(nil);

//test getFromHead
	pushToTail(pool, b1);
	pushToTail(pool, b2);
	pushToTail(pool, b3);
	pushToTail(pool, b4);

	error_log("pool count should be 4:%d\n", count(pool));
	getFromHead(pool);
	error_log("pool count should be 3:%d\n", count(pool));
	getFromHead(pool);
	error_log("pool count should be 2:%d\n", count(pool));	
	getFromHead(pool);
	error_log("pool count should be 1:%d\n", count(pool));
	getFromHead(pool);
	error_log("pool count should be 0:%d\n", count(pool));
//test cut
	empty(pool);
	pushToTail(pool, b1);
	pushToTail(pool, b2);
	pushToTail(pool, b3);
	pushToTail(pool, b4);

	error_log("pool count should be 4:%d\n", count(pool));
	cut(pool, b1, &tb);
	error_log("pool count should be 3:%d\n", count(pool));
	cut(pool, b2, &tb);
	error_log("pool count should be 2:%d\n", count(pool));	
	cut(pool, b3, &tb);
	error_log("pool count should be 1:%d\n", count(pool));
	cut(pool, b4, &tb);
	error_log("pool count should be 0:%d\n", count(pool));
//test cut
	empty(pool);
	pushToTail(pool, b1);
	pushToTail(pool, b2);
	pushToTail(pool, b3);
	pushToTail(pool, b4);

	error_log("pool count should be 4:%d\n", count(pool));
	cut(pool, b4, &tb);
	error_log("pool count should be 3:%d\n", count(pool));
	cut(pool, b3, &tb);
	error_log("pool count should be 2:%d\n", count(pool));	
	cut(pool, b2, &tb);
	error_log("pool count should be 1:%d\n", count(pool));
	cut(pool, b1, &tb);
	error_log("pool count should be 0:%d\n", count(pool));

}



