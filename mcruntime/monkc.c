/*
Copyright (c) <2013-2016>, <Sun Yuli>
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
 Log
 */
#ifdef MC_LOG_USE_COLOR
#define LOG_COLOR_NONE "\033[0m"
#define LOG_COLOR_BLACK "\033[0;30m"
#define LOG_COLOR_DARK_GRAY "\033[1;30m"
#define LOG_COLOR_BLUE "\033[0;34m"
#define LOG_COLOR_LIGHT_BLUE "\033[1;34m"
#define LOG_COLOR_GREEN "\033[0;32m"
#define LOG_COLOR_LIGHT_GREEN "\033[1;32m"
#define LOG_COLOR_CYAN "\033[0;36m"
#define LOG_COLOR_LIGHT_CYAN "\033[1;36m"
#define LOG_COLOR_RED "\033[0;31m"
#define LOG_COLOR_LIGHT_RED "\033[1;31m"
#define LOG_COLOR_PURPLE "\033[0;35m"
#define LOG_COLOR_LIGHT_PURPLE "\033[1;35m"
#define LOG_COLOR_BROWN "\033[0;33m"
#define LOG_COLOR_YELLOW "\033[1;33m"
#define LOG_COLOR_LIGHT_GRAY "\033[0;37m"
#define LOG_COLOR_WHITE "\033[1;37m"
#define LOG_FMT "%s%s\033[0m"
#else
#define LOG_COLOR_NONE ""
#define LOG_COLOR_BLACK ""
#define LOG_COLOR_DARK_GRAY ""
#define LOG_COLOR_BLUE ""
#define LOG_COLOR_LIGHT_BLUE ""
#define LOG_COLOR_GREEN ""
#define LOG_COLOR_LIGHT_GREEN ""
#define LOG_COLOR_CYAN ""
#define LOG_COLOR_LIGHT_CYAN ""
#define LOG_COLOR_RED ""
#define LOG_COLOR_LIGHT_RED ""
#define LOG_COLOR_PURPLE ""
#define LOG_COLOR_LIGHT_PURPLE ""
#define LOG_COLOR_BROWN ""
#define LOG_COLOR_YELLOW ""
#define LOG_COLOR_LIGHT_GRAY ""
#define LOG_COLOR_WHITE ""
#define LOG_FMT "%s%s"
#endif

//fonts color
#define FBLACK      "\033[30;"
#define FRED        "\033[31;"
#define FGREEN      "\033[32;"
#define FYELLOW     "\033[33;"
#define FBLUE       "\033[34;"
#define FPURPLE     "\033[35;"
#define D_FGREEN    "\033[6;"
#define FWHITE      "\033[7;"
#define FCYAN       "\x1b[36m"

//background color
#define BBLACK      "40m"
#define BRED        "41m"
#define BGREEN      "42m"
#define BYELLOW     "43m"
#define BBLUE       "44m"
#define BPURPLE     "45m"
#define D_BGREEN    "46m"
#define BWHITE      "47m"

//end color
#define NONE        "\033[0m"

/*
	Logs with color tags
	we use the same syntex with printf
 */
static int LOG_LEVEL = MC_DEBUG;
extern void MCLogTypeSet(MCLogType type)
{
    LOG_LEVEL = type;
}

#ifndef __ANDROID__

static const char* FCOLOR = FRED;
static const char* BCOLOR = BBLACK;

int printc(const char* fmt, ...)
{
    int ret;
    char log_buf[LINE_MAX];
    
    va_list ap;
    va_start(ap, fmt);
    log_buf[vsprintf(log_buf, fmt, ap)]='\0';
    ret = printf("%s%s%s%s", FCOLOR, BCOLOR, log_buf, NONE);
    va_end(ap);
    return ret;
}

void error_log(const char* fmt, ...)
{
    va_list ap;
    char log_buf[LINE_MAX];
    
    if(LOG_LEVEL != MC_SILENT){
        printf(LOG_FMT, LOG_COLOR_RED, "[Error] - ");
        va_start(ap, fmt);
        log_buf[vsprintf(log_buf, fmt, ap)]='\0';
        printf("%s", log_buf);
        va_end(ap);
    }
}

void debug_log(const char* fmt, ...)
{
    va_list ap;
    char log_buf[LINE_MAX];
    
    if(LOG_LEVEL != MC_SILENT
       &&LOG_LEVEL != MC_ERROR_ONLY){
        printf(LOG_FMT, LOG_COLOR_LIGHT_BLUE, "[Debug] - ");
        va_start(ap, fmt);
        log_buf[vsprintf(log_buf, fmt, ap)]='\0';
        printf("%s", log_buf);
        va_end(ap);
    }
}

void runtime_log(const char* fmt, ...)
{
    va_list ap;
    char log_buf[LINE_MAX];
    
    if(LOG_LEVEL != MC_SILENT
       &&LOG_LEVEL != MC_ERROR_ONLY
       &&LOG_LEVEL != MC_DEBUG){
        printf(LOG_FMT, LOG_COLOR_DARK_GRAY, "[RTime] - ");
        va_start(ap, fmt);
        log_buf[vsprintf(log_buf, fmt, ap)]='\0';
        printf("%s", log_buf);
        va_end(ap);
    }
}

void error_logt(const char* tag, const char* fmt, ...)
{
    va_list ap;
    char log_buf[LINE_MAX];
    
    if(LOG_LEVEL != MC_SILENT){
        printf(LOG_FMT, LOG_COLOR_RED, "[Error] - ");
        printf(LOG_FMT, LOG_COLOR_DARK_GRAY, tag);
        va_start(ap, fmt);
        log_buf[vsprintf(log_buf, fmt, ap)]='\0';
        printf("%s", log_buf);
        va_end(ap);
    }
}

void debug_logt(const char* tag, const char* fmt, ...)
{
    va_list ap;
    char log_buf[LINE_MAX];
    
    if(LOG_LEVEL != MC_SILENT
       &&LOG_LEVEL != MC_ERROR_ONLY){
        printf(LOG_FMT, LOG_COLOR_LIGHT_BLUE, "[Debug] - ");
        printf(LOG_FMT, LOG_COLOR_DARK_GRAY, tag);
        va_start(ap, fmt);
        log_buf[vsprintf(log_buf, fmt, ap)]='\0';
        printf("%s", log_buf);
        va_end(ap);
    }
}

void runtime_logt(const char* tag, const char* fmt, ...)
{
    va_list ap;
    char log_buf[LINE_MAX];
    
    if(LOG_LEVEL != MC_SILENT
       &&LOG_LEVEL != MC_ERROR_ONLY
       &&LOG_LEVEL != MC_DEBUG){
        printf(LOG_FMT, LOG_COLOR_DARK_GRAY, "[RTime] - ");
        printf(LOG_FMT, LOG_COLOR_DARK_GRAY, tag);
        va_start(ap, fmt);
        log_buf[vsprintf(log_buf, fmt, ap)]='\0';
        printf("%s", log_buf);
        va_end(ap);
    }
}
#endif

//private data
static mc_hashtable* mc_global_classtable = mull;

void trylock_global_classtable()
{
	mc_trylock(&(mc_global_classtable->lock));
}

void unlock_global_classtable()
{
	mc_unlock(&(mc_global_classtable->lock));
}

/*
for method binding
*/

MCHashTableIndex _binding(mc_class* const aclass, const char* methodname, MCFuncPtr value)
{
	return _binding_h(aclass, methodname, value, hash(methodname));
}

MCHashTableIndex _binding_h(mc_class* const aclass, const char* methodname, MCFuncPtr value, MCHash hashval)
{
	if(aclass==mull){
		error_log("_binding_h(mc_class* aclass) aclass is nill return 0\n");
		return 0;
	}
	MCHashTableIndex res = set_item(&(aclass->table),
		new_item_h(methodname, (MCGeneric)value, hashval),
		1, 0, nameofc(aclass));//will override
	return res;
}

static inline mc_class* findclass(const char* name, const MCHash hashval)
{
	mc_hashitem* item = mull;
	//create a class hashtable
	if(mc_global_classtable == mull)
		mc_global_classtable = new_table(MCHashTableLevel1);
	item=get_item_byhash(mc_global_classtable, hashval, name);
	if (item == mull)
		return mull;
	else
		runtime_log("findClass item key:%s, value:%p\n", item->key, item->value.mcptr);
	return (mc_class*)(item->value.mcptr);
}

mc_class* _load(const char* name, size_t objsize, MCLoaderPointer loader)
{
	return _load_h(name, objsize, loader, hash(name));
}

mc_class* _load_h(const char* name, size_t objsize, MCLoaderPointer loader, MCHash hashval)
{
	mc_class* aclass = findclass(name, hashval);
	//try lock spin lock
	trylock_global_classtable();
	if(aclass == mull){
		//new a item
		aclass = alloc_mc_class(objsize);
        mc_hashitem* item = new_item(name, (MCGeneric){.mcptr=mull});//nil first
		package_by_item(item, aclass);
		(*loader)(aclass);
		//set item
        //MCBool isOverride, MCBool isFreeValue
		set_item(&mc_global_classtable, item, MCFalse, MCTrue, (char*)name);
		runtime_log("load a class[%s]\n", name);
	}else{
		runtime_log("find a class[%s]\n", name);
	}
	//unlock
	unlock_global_classtable();
	return aclass;
}

mo _new(mo const obj, MCIniterPointer initer)
{
	//block, isa, saved_isa is setted at _alloc()
    obj->nextResponder = mull;
	obj->ref_count = 1;
	(*initer)(obj);
	return obj;
}

static int ref_count_down(mo const this)
{

	for(;;){
		if(this == mull){
			error_log("recycle/release(mull) do nothing.\n");
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
		if(this->isa == mull){
			error_log("recycle/release(obj) obj have no class linked. do nothing.\n");
			return REFCOUNT_ERR;
		}
#ifdef NO_ATOMIC
        this->ref_count--; break;
#else
        int oldcount, newcount;
        int *addr;
        addr = &(this->ref_count);
        oldcount = mc_atomic_get_integer(addr);
        newcount = oldcount;
        if(newcount > 0)
            newcount--;
        if(!mc_atomic_set_integer(addr, oldcount, newcount))
            break;
#endif
	}
	return this->ref_count;
}

void _recycle(mo const this)
{
	if(ref_count_down(this) == 0){
        fs(this, bye, 0);                             //call the "bye" method on object
        mc_dealloc(this, 1);                          //free memory
	}
}

void _release(mo const this)
{
    if(ref_count_down(this) == 0){
        fs(this, bye, 0);
        mc_dealloc(this, 0);
	}
}

mo _retain(mo const this)
{

	for(;;){
		if(this == mull){
			error_log("retain(nil) do nothing.\n");
			return this;
		}
		if(this->ref_count == REFCOUNT_NO_MM){
			debug_log("ref_count is REFCOUNT_NO_MM manage by runtime. do nothing\n");
			return this;
		}
		if(this->isa == mull){
			error_log("release(obj) obj have no class linked. do nothing.\n");
			return this;
		}
#ifdef NO_ATOMIC
        this->ref_count++; break;
#else
        int* rcountaddr;
        int oldcount;
		rcountaddr = &(this->ref_count);
		oldcount = mc_atomic_get_integer(rcountaddr);
		if(!mc_atomic_set_integer(rcountaddr, oldcount, oldcount+1))
			break;
#endif
	}
	runtime_log("%s - ref_count:%d\n", nameof(this), this->ref_count);
	return this;
}

/*
 Lock
 */
void mc_trylock(volatile int* lock_p)
{
    if(lock_p==mull){
        error_log("mc_trylock(int* lock_p) lock_p is nil\n");
        return;
    }
#ifdef NO_ATOMIC
    (*lock_p) = 1;
#else
    for(;;){
        if(mc_atomic_get_integer(lock_p) != 0)
            continue;
        if(!mc_atomic_set_integer(lock_p, 0, 1))
            break;
    }
#endif
}

void mc_unlock(volatile int* lock_p)
{
    if(lock_p==mull){
        error_log("mc_unlock(int* lock_p) lock_p is nil\n");
        return;
    }
    
    (*lock_p) = 0;
}

/*
 HashTable
 */
mc_hashtable* new_table(const MCHashTableLevel initlevel)
{
    //alloc
    mc_hashtable* atable = (mc_hashtable*)malloc(sizeof(mc_hashtable)
                                                 +get_tablesize(initlevel)*sizeof(mc_hashitem*));
    //init
    atable->lock = 0;
    atable->level = initlevel;
    atable->table_item_count = 0;
    //set all the slot to nil
    for (int i = 0; i < get_tablesize(initlevel); i++)
        atable->items[i] = mull;
    return atable;
}

static inline void copy_table(mc_hashtable* dest, mc_hashtable* src)
{
    MCHashTableSize srccount = get_tablesize(src->level);
    //don't copy lock, level
    int i;
    for (i=0; i<srccount; i++) {
        dest->items[i] = src->items[i];
    }
    dest->table_item_count = src->table_item_count;
}

static inline void expand_table(mc_hashtable** const table_p, MCHashTableLevel tolevel)
{
    //realloc
    mc_hashtable* newtable = new_table(tolevel);
    mc_hashtable* oldtable = (*table_p);
    copy_table(newtable, oldtable);
    debug_log("expand table: %d->%d\n", oldtable->level, newtable->level);
    free(*table_p);
    (*table_p) = newtable;
}

mc_hashitem* new_item(const char* key, MCGeneric value)
{
    return new_item_h(key, value, hash(key));
}

mc_hashitem* new_item_h(const char* key, MCGeneric value, const MCHash hashval)
{
    mc_hashitem* aitem = (mc_hashitem*)malloc(sizeof(mc_hashitem));
    if (aitem != mull) {
        aitem->next = mull;
        aitem->hash = hashval;
        aitem->index = 0;
        aitem->level = MCHashTableLevel1;
        //strcpy(aitem->key, key);
        //aitem->key[MAX_KEY_CHARS] = '\0';
        aitem->key = (char*)key;
        aitem->value = value;
        return aitem;
    }else{
        error_log("Monk-C HashTable new_item failed, key=%s\n", key);
        exit(-1);
    }
}



MCHashTableIndex set_item(mc_hashtable** const table_p, mc_hashitem* const item,
                          MCBool isOverride, MCBool isFreeValue, const char* classname)
{
    if(table_p==mull || table_p==mull){
        error_log("set_item(mc_hashtable** table_p) table_p or *table_p is nill return 0\n");
        return 0;
    }
    
    MCHash hashval = item->hash;
    MCHashTableIndex index = hashval % get_tablesize((*table_p)->level);
    
    mc_hashitem* olditem = (*table_p)->items[index];
    if(olditem == mull){
        item->level = (*table_p)->level;
        item->index = index;
        (*table_p)->items[index] = item;
        runtime_log("[%s]:set-item[%d/%s]\n", classname, item->index, item->key);
        return index;
    }else{
        //if the item have already been setted. we free the old one
        if(mc_compare_key(olditem->key, item->key) == 0){
            if(isOverride == MCFalse){
                runtime_log("[%s]:set-item key[%s] already been setted, free temp item\n", classname, item->key);
                if(isFreeValue == MCTrue)free(item->value.mcfuncptr);
                free(item);
                (*table_p)->items[index] = mull;
                return index;
            }else{
                runtime_log("[%s]:reset-item key[%s] already been setted, replace old item\n", classname, item->key);
                if(isFreeValue == MCTrue)free(olditem->value.mcfuncptr);
                item->level = (*table_p)->level;
                item->index = index;
                (*table_p)->items[index] = item;
                return index;
            }
            
            //conflict with other item. we expand the table and try again. until success
        }else{
            //report the conflict type
            if(olditem->hash == item->hash)
                error_log("[%s]:hash conflict new[%s/%d]<->old[%s/%d]\n",
                          classname, item->key, item->hash, olditem->key, olditem->hash);
            else
                error_log("[%s]:index conflict new[%s/%d]<->old[%s/%d]\n",
                          classname, item->key, index, olditem->key, index);
            //solve the conflict
            if((*table_p)->level < MCHashTableLevelCount){//Max=5 Count=6
                expand_table(table_p, (*table_p)->level+1);
                set_item(table_p, item, isOverride, isFreeValue, mull);//recursive
                return index;
            }else{
                //tmplevel = 5, table_p must have been expanded to level 4
                //there still a item, use link list.
                error_log("[%s]:item key conflict can not be solved. link the new one[%s] behind the old[%s]\n",
                          classname, item->key, olditem->key);
                item->level = MCHashTableLevelMax;
                item->index = index;
                olditem->next = item;
                return index;
            }
        }
    }
}

mc_hashitem* get_item_bykey(mc_hashtable* const table_p, const char* key)
{
    if(table_p==mull){
        error_log("get_item_bykey(table_p) table_p is nil return nil\n");
        return mull;
    }
    //try get index
    return get_item_byhash(table_p, hash(key), key);
}

mc_hashitem* get_item_byhash(mc_hashtable* const table_p, const MCHash hashval, const char* refkey)
{
    if(table_p==mull){
        error_log("get_item_byhash(table_p) table_p is nil return nil\n");
        return mull;
    }
    
    //level<MCHashTableLevelMax
    MCHashTableLevel level = MCHashTableLevel1;
    mc_hashitem* res=mull;
    for(level = MCHashTableLevel1; level<MCHashTableLevelMax; level++){
        if((res=get_item_byindex(table_p, hashval % get_tablesize(level))) == mull) {
            continue;
        }
        if(res->level != level) {
            continue;
        }
        if(res->hash != hashval) {
            continue;
        }
        //pass all the check
        return res;
    }
    //level=MCHashTableLevelMax
    if((res=get_item_byindex(table_p, hashval % get_tablesize(MCHashTableLevelMax))) == mull)
        return mull;
    if(res->level != MCHashTableLevelMax)
        return mull;
    if(res->hash != hashval)
        return mull;
    if(res->next == mull)
        return mull;
    //pass all the check. search conflicted item
    for(; res!=mull; res=res->next)
        if(mc_compare_key(res->key, refkey) == 0){
            runtime_log("key hit a item [%s/%d/%d]\n", 
                        res->key, res->index, MCHashTableLevelMax);
            return res;
        }
    //no matched item
    return mull;
}

mc_hashitem* get_item_byindex(mc_hashtable* const table_p, const MCHashTableIndex index)
{
    if(table_p==mull){
        error_log("get_item_byindex(table_p) table_p is nil return nil\n");
        return mull;
    }
    if(index > get_tablesize(table_p->level))
        return mull;
    if(table_p->items[index] != mull)
        return table_p->items[index];
    else
        return mull;
}


/*
 ObjectManage
 */

//	Memory Allocators
// 
//	alternative allocators in APUE
//	1. libmalloc
//	2. vmalloc
//	3. quick-fit
//	4. alloca ---> can alloc mem on stack

void pushToTail(mc_blockpool* bpool, mc_block* ablock)
{
    mc_trylock(&(bpool->lock));
    deref(ablock).next = mull;
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
    target = mull;
    if(MC_NO_NODE(bpool)){
        target=mull;
    }else if(MC_ONE_NODE(bpool)){
        target=bpool->tail;
        deref(bpool).tail = mull;
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
    while((target=getFromHead(bpool)) != mull){
        fs((mo)(target->data), bye, mull);
        free(target->data);
        free(target);
    }
}

int count(mc_blockpool* bpool)
{
    int i = 1;
    mc_block* H;
    if(deref(bpool).tail==mull)
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
        deref(result)=mull;
        res=-1;//fail
    }else if(MC_ONE_NODE(bpool)){
        deref(bpool).tail=mull;
        deref(ablock).next=mull;
        deref(result)=ablock;
    }else if(MC_TWO_NODE(bpool)){//do not swap data
        if(deref(ablock).next==mull){
            error_log("block not in the pool, refuse to cut\n");
            res=-1;//fail
        }else{
            mc_block* H = deref(bpool).tail->next;
            mc_block* T = deref(bpool).tail;
            if(ablock==bpool->tail){//cut tail
                deref(T).next=mull;
                deref(result)=T;
                deref(bpool).tail=H;
                deref(H).next=H;
            }else{//cut head
                deref(H).next=mull;
                deref(result)=H;
                deref(T).next=T;
            }
        }
    }else{
        if(deref(ablock).next==mull){
            error_log("block not in the pool, refuse to cut\n");
            res=-1;//fail
        }else{
            if(deref(ablock).next==bpool->tail)//don not delete the tail!
                deref(bpool).tail = ablock;
            NN = ablock->next->next;
            //result
            deref(deref(ablock).next).next = mull;
            deref(result) = deref(ablock).next;
            //swap
            package_by_block(ablock, ablock->next->data);
            deref(ablock).next = NN;
        }
    }
    mc_unlock(&(bpool->lock));
    return res;
}

void mc_info(const char* classname, size_t size, MCLoaderPointer loader)
{
    mc_info_h(classname, size, loader, hash(classname));
}

void mc_info_h(const char* classname, size_t size, MCLoaderPointer loader, MCHash hashval)
{
    mc_class* aclass = _load_h(classname, size, loader, hashval);
    debug_log("----info[%s] used:%d/free:%d\n",
              classname, count(&aclass->used_pool), count(&aclass->free_pool));
}

void mc_clear(const char* classname, size_t size, MCLoaderPointer loader)
{
    mc_clear_h(classname, size, loader, hash(classname));
}

void mc_clear_h(const char* classname, size_t size, MCLoaderPointer loader, MCHash hashval)
{
    mc_class* aclass = _load_h(classname, size, loader, hashval);
    if(aclass->used_pool.tail!=mull)
        empty(&aclass->used_pool);
    else
        runtime_log("class[%s] used_pool have no node. check free_pool\n", classname);
    if(aclass->free_pool.tail!=mull)
        empty(&aclass->free_pool);
    else
        runtime_log("class[%s] free_pool also have no node. do not clear\n", classname);
    runtime_log("empty [%s] finish\n", classname);
}

//always return a object of size. packaged by a block.
mo mc_alloc(const char* classname, size_t size, MCLoaderPointer loader)
{
    return mc_alloc_h(classname, size, loader, hash(classname));
}

mo mc_alloc_h(const char* classname, size_t size, MCLoaderPointer loader, MCHash hashval)
{
#if defined(NO_RECYCLE) && NO_RECYCLE
    mc_class* aclass = _load_h(classname, size, loader, hashval);
    mo aobject = mull;
    //new a object package by a block
    aobject = (mo)malloc(size);
    if (aobject != mull) {
        aobject->isa = aclass;
        aobject->saved_isa = aclass;
        runtime_log("----alloc[NEW:%s]: new alloc\n", classname);
        return aobject;
    }else{
        error_log("----alloc[NEW:%s]: new alloc FAILED\n", classname);
        exit(-1);
    }
    
#else
    mc_class* aclass = _load_h(classname, size, loader, hashval);
    mc_blockpool* fp = &aclass->free_pool;
    mc_blockpool* up = &aclass->used_pool;
    mc_block* ablock = mull;
    mo aobject = mull;
    if((ablock=getFromHead(fp)) == mull){
        //new a object package by a block
        aobject = (mo)malloc(size);
        aobject->isa = aclass;
        aobject->saved_isa = aclass;
        //new a block
        ablock = new_mc_block(mull);
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
#endif
}

void mc_dealloc(MCObject* aobject, int is_recycle)
{
#if defined(NO_RECYCLE) && NO_RECYCLE
    if(aobject==mull){
        error_log("----dealloc(%s) obj is mull\n", nameof(aobject));
        return;
    }
    runtime_log("----dealloc[DEL:%s]: delete a obj[%p]\n", nameof(aobject), aobject);
    free(aobject);
#else
    mc_block* blk = aobject->block;
    mc_class* cls = aobject->isa;
    mc_blockpool* fp = &cls->free_pool;
    mc_blockpool* up = &cls->used_pool;
    
    if(aobject==mull){
        error_log("----dealloc(%s) obj is mull\n", nameof(aobject));
        return;
    }
    if(blk==mull){
        error_log("----dealloc(%s) obj->block is mull\n", nameof(aobject));
        return;
    }
    if(cls==mull){
        error_log("----dealloc(%s) obj->isa is mull\n", nameof(aobject));
        return;
    }
    if(fp==mull || up==mull){
        error_log("----dealloc(%s) obj->isa->pool is mull\n", nameof(aobject));
        return;
    }
    if(MC_NO_NODE(up)){
        error_log("----dealloc(%s) have no block used, but you request dealloc\n", nameof(aobject));
        return;
    }
    
    mc_block* nb = mull;
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
    }else{
        exit(-1);
    }
#endif
}

/*
 Messaging
 */
mc_message _self_response_to(const mo obj, const char* methodname)
{
    return _self_response_to_h(obj, methodname, hash(methodname));
}

mc_message _self_response_to_h(const mo obj, const char* methodname, MCHash hashval)
{
    //we will return a struct
    mc_hashitem* res = mull;
    mc_message tmpmsg = {mull, mull};
    
    if(obj == mull){
        //no need to warning user
        return tmpmsg;
    }
    if(obj->isa == mull){
        error_log("_self_response_to(obj, '%s') obj->isa is mull. return {mull, mull}\n", methodname);
        return tmpmsg;
    }
    
    if((res=get_item_byhash(obj->isa->table, hashval, methodname)) != mull){
        tmpmsg.object = obj;
        tmpmsg.address = res->value.mcfuncptr;
        //runtime_log("return a message[%s/%s]\n", nameof(obj), methodname);
        return tmpmsg;
    }else{
        if (obj->nextResponder != mull) {
            return _self_response_to_h(obj->nextResponder, methodname, hashval);
        }else{
            runtime_log("self_response_to class[%s] can not response to method[%s]\n", nameof(obj), methodname);
            if (MC_STRICT_MODE == 1) {
                printf("Monk-C: %s can not response %s\n", nameof(obj), methodname);
                exit(-1);
            }else{
                return tmpmsg;
            }
        }
    }
}

mc_message _response_to(const mo obj, const char* methodname, int strict)
{
    return _response_to_h(obj, methodname, hash(methodname), strict);
}

mc_message _response_to_h(const mo obj, const char* methodname, MCHash hashval, int strict)
{
    return _self_response_to_h(obj, methodname, hashval);
}
/*
	MCObject* obj_iterator = obj;
	MCObject* obj_first_hit = mull;
	mc_hashitem* met_first_hit = mull;
	mc_hashitem* met_item = mull;
	int hit_count = 0;
	int iter_count = 0;
	//int max_iter = get_tablesize(5);
	int max_iter = 10000;
 
	mc_message tmpmsg = {mull, mull};
	if(obj == mull || obj->isa == mull){
 error_log("_response_to(obj) obj is mull or obj->isa is mull. return {mull, mull}\n");
 return tmpmsg;
	}
 
	for(obj_iterator = obj;
 obj_iterator!= mull;
 obj_iterator = obj_iterator->super){
 if(iter_count++ > max_iter){
 error_log("iter_count>max but class still can not response to method\n");
 break;
 }
 if((met_item=get_item_byhash(&(obj_iterator->isa->table), hashval, methodname)) != mull) {
 runtime_log("hit a method [%s/%d] to match [%s]\n",
 met_item->key, met_item->index, methodname);
 hit_count++;
 tmpmsg.object = obj_iterator;
 tmpmsg.address = met_item->value.mcfuncptr;
 if(obj_first_hit==mull)obj_first_hit = obj_iterator;
 if(met_first_hit==mull)met_first_hit = met_item;
 //for the method key have conflicted with some super class in inherit tree
 if(hit_count>1){
 if(hit_count==2){
 //to support the "overide" feature of oop
 if(mc_compare_key(met_first_hit->key, methodname) == 0){
 tmpmsg.object = obj_first_hit;
 tmpmsg.address = met_first_hit->value.mcfuncptr;
 runtime_log("[first hit]return a message[%s/%s(%p/%p)]\n",
 tmpmsg.object->isa->item->key,
 methodname,
 tmpmsg.object,
 tmpmsg.address);
 return tmpmsg;}
 }
 if(mc_compare_key(met_item->key, methodname) == 0){
 tmpmsg.object = obj_iterator;
 runtime_log("[string equal]return a message[%s/%s]\n", tmpmsg.object->isa->item->key, methodname);
 return tmpmsg;}
 }
 }
	}
	if(hit_count==1)
 runtime_log("return a message[%s/%s]\n", nameof(tmpmsg.object), methodname);
	else if(hit_count==0)
 {
 if (strict!=2) error_log("class[%s] can not response to method[%s]\n", nameof(obj), methodname);
 if (strict==1) exit(1);
 }
	else
 {
 if (strict!=2) error_log("hit_count>1 but class still can not response to method\n");
 if (strict==1) exit(1);
 }
	return tmpmsg;
 }
 */

