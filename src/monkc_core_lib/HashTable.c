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

static const unsigned mc_hashtable_sizes[5] = {100, 200, 1000, 4000, 10000};
inline unsigned get_tablesize(const unsigned level)
{
	if(level>5){
		error_log("get_tablesize(level) level>5 return use level=5\n");
		return mc_hashtable_sizes[5];
	}
	return mc_hashtable_sizes[level];
}

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

// typedef struct mc_hashtable_struct
// {
// 	int lock;
// 	unsigned level;
// 	unsigned count;
// 	mc_hashitem* data[];
// }mc_hashtable;

static mc_hashtable* expand_table(mc_hashtable** const table_p, unsigned tolevel)
{
	unsigned oldlevel = (*table_p)->level;
	size_t newsize = sizeof(mc_hashtable) + get_tablesize(tolevel)*sizeof(mc_hashitem*);
	size_t oldsize = sizeof(mc_hashtable) + get_tablesize(oldlevel)*sizeof(mc_hashitem*);
	//realloc
	mc_hashtable* newtable = (mc_hashtable*)realloc((*table_p), newsize);
	newtable->level = tolevel;
	//fill new slots to nil
	unsigned i;
	for(i=get_tablesize(oldlevel)+1; i<get_tablesize(tolevel); i++)
		newtable->items[i]=nil;
	(*table_p) = newtable;
	error_log("expand table: %d->%d\n", oldlevel, (*table_p)->level);
	return (*table_p);
}

// typedef struct mc_hashitem_struct
// {
// 	struct mc_hashitem_struct* next;
// 	unsigned hash;
// 	unsigned index;
// 	unsigned level;
// 	void* value;
// 	char key[MAX_KEY_CHARS];
// }mc_hashitem;

mc_hashitem* new_item_withclass(const char* key, mc_class* aclass)
{
	mc_hashitem* item = new_item(key, aclass);
	aclass->item = item;
	return item;
}

mc_hashitem* new_item_withclass_h(const char* key, mc_class* aclass, unsigned hashval)
{
	mc_hashitem* item = new_item_h(key, aclass, hashval);
	aclass->item = item;
	return item;
}

mc_hashitem* new_item(const char* key, void* value)
{
	return new_item_h(key, value, hash(key));
}

mc_hashitem* new_item_h(const char* key, void* value, const unsigned hashval)
{
	mc_hashitem* aitem = (mc_hashitem*)malloc(sizeof(mc_hashitem));
	aitem->next = nil;
	aitem->hash = hashval;
	aitem->index = 0;
	aitem->level = 0;
	mc_copy_key(aitem->key, key);
	aitem->value = value;
	return aitem;
}

// typedef struct mc_hashtable_struct
// {
// 	int lock;
// 	unsigned level;
// 	unsigned count;
// 	mc_hashitem* items[];
// }mc_hashtable;

mc_hashtable* new_table(const unsigned initlevel)
{
	//alloc
	mc_hashtable* atable = (mc_hashtable*)malloc(sizeof(mc_hashtable)
		+get_tablesize(initlevel)*sizeof(mc_hashitem*));
	//init
	atable->lock = 0;
	atable->level = initlevel;
	atable->count = 0;
	//set all the slot to nil
	unsigned i;
	for (i = 0; i < get_tablesize(initlevel); i++)
		(atable->items)[i]=nil;
	return atable;
}

unsigned set_item(mc_hashtable** const table_p,
	mc_hashitem* const item, 
	BOOL isOverride, BOOL isFreeValue)
{
	if(table_p==nil || *table_p==nil){
		error_log("set_item(mc_hashtable** table_p) table_p or *table_p is nill return 0\n");
		return 0;
	}

	unsigned hashval = item->hash;
	unsigned index = hashval % get_tablesize((*table_p)->level);
	mc_hashitem* olditem;
	if((olditem=(*table_p)->items[index]) == nil){
		item->level = (*table_p)->level;
		item->index = index;
		(*table_p)->items[index] = item;
		runtime_log("set-item[%d/%s]\n", item->index, item->key);
		return index;
	}else{
		//if the item have already been setted. we free the old one
		if(mc_compare_key(olditem->key, item->key) == 0){
			if(isOverride == NO){
				error_log("set-item key[%s] already been setted, free temp item\n", item->key);
				if(isFreeValue == YES)free(item->value);
				free(item);
				return index;
			}else{
				error_log("reset-item key[%s] already been setted, replace old item\n", item->key);
				if(isFreeValue == YES)free(olditem->value);
				free(olditem);
				item->level = (*table_p)->level;
				item->index = index;
				(*table_p)->items[index] = item;
				return index;
			}

		//conflict with other item. we expand the table and try again. until success
		}else{
			if(olditem->hash == item->hash){
				error_log("hash conflict new[%s/%d]<->old[%s/%d]\n", 
					item->key, item->hash,
					olditem->key, olditem->hash);
			}else{
				error_log("index conflict new[%s/%d]<->old[%s/%d]\n",
					item->key, index,
					olditem->key, index);
			}
			unsigned tmplevel = (*table_p)->level+1;
			if(tmplevel<5){
				expand_table(table_p, tmplevel);
				set_item(table_p, item, isOverride, isFreeValue);
			}else{
				//tmplevel = 5, table_p must have been expanded to level 4
				//there still a item, use link list.
				error_log("item key conflict can not be soloved. link the new one behind the old\n");
				item->level = 4;
				item->index = index;
				olditem->next = item;
				return index;
			}
		}
	}
}

mc_hashitem* get_item_bykey(const mc_hashtable** table_p, const char* key)
{
	if((*table_p)==nil){
		error_log("get_item_bykey(table_p) table_p is nil return nil\n");
		return nil;
	}
	unsigned hashval = hash(key);
	//try get index
	return get_item_byhash(table_p, hashval, key);
}

mc_hashitem* get_item_byhash(const mc_hashtable** table_p, const unsigned hashval, const char* refkey)
{
	if((*table_p)==nil){
		error_log("get_item_byhash(table_p) table_p is nil return nil\n");
		return nil;
	}
	unsigned level;
	mc_hashitem* res;
	//level<4
	for(level = 0; level<4; level++){
		if((res=get_item_byindex(table_p, hashval % get_tablesize(level))) == nil)
			continue;
		if(res->level != level)
			continue;
		if(res->hash != hashval)
			continue;
		//pass all the check
		return res;
	}
	//level=4
	if((res=get_item_byindex(table_p, hashval % get_tablesize(4))) == nil)
		return nil;
	if(res->level != 4)
		return nil;
	if(res->hash != hashval)
		return nil;
	if(res->next == nil)
		return nil;
	//pass all the check. search conflicted item
	for(; res!=nil; res=res->next)
		if(mc_compare_key(res->key, refkey) == 0){
			runtime_log("key hit a item [%s/%d/%d]\n", 
			res->key, res->index, 4);
			return res;
		}
	//no matched item
	return nil;
}

mc_hashitem* get_item_byindex(const mc_hashtable** table_p, const unsigned index)
{
	if((*table_p)==nil){
		error_log("get_item_byindex(table_p) table_p is nil return nil\n");
		return nil;
	}
	if(index > get_tablesize((*table_p)->level))
		return nil;
	if((*table_p)->items[index] != nil)
		return (*table_p)->items[index];
	else
		return nil;
}



