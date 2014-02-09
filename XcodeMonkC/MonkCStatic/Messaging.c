#include "monkc.h"


mc_message make_msg(mo const this, const void* entry)
{
	//we will return a struct
	mc_message tmpmsg = {nil, nil};
	tmpmsg.object = this;
	tmpmsg.addr = entry;
	return tmpmsg;
}

mc_message _self_response_to(const mo obj, const char* methodname)
{
	return _self_response_to_h(obj, methodname, hash(methodname));
}

//mc_hashitem* get_item_byhash(const mc_hashtable** table_p, const unsigned hashval, const char* refkey);

mc_message _self_response_to_h(const mo obj, const char* methodname, unsigned hashval)
{
	//we will return a struct
	mc_message tmpmsg = {nil, nil};
	if(obj == nil){
		error_log("_self_response_to(obj) obj is nil. return {nil, nil}\n");
		return tmpmsg;
	}
	if(obj->isa == nil){
		error_log("_self_response_to(obj) obj->isa is nil. return {nil, nil}\n");
		return tmpmsg;
	}

	mc_hashitem* res;
	if((res=get_item_byhash(&(obj->isa->table), hashval, methodname)) != nil){
		tmpmsg.object = obj;
		tmpmsg.addr = res->value;
		runtime_log("return a message[%s/%s]\n", nameof(tmpmsg.object), methodname);
		return tmpmsg;
	}else{
		runtime_log("self_response_to class[%s] can not response to method[%s]\n", nameof(obj), methodname);
		return tmpmsg;
	}
}

mc_message _response_to(const mo obj, const char* methodname, int strict)
{
	return _response_to_h(obj, methodname, hash(methodname), strict);
}

mc_message _response_to_h(const mo obj, const char* methodname, unsigned hashval, int strict)
{
	mc_message tmpmsg = {nil, nil};
	if(obj == nil || obj->isa == nil){
		error_log("_response_to(obj) obj is nil or obj->isa is nil. return {nil, nil}\n");
		return tmpmsg;
	}

	mc_object* obj_iterator = obj;
	mc_object* obj_first_hit = nil;
	mc_hashitem* met_first_hit = nil;
	mc_hashitem* met_item = nil;
	int hit_count = 0;
	int iter_count = 0;
	//int max_iter = get_tablesize(5);
	int max_iter = 10000;

	for(obj_iterator = obj;
		obj_iterator!= nil;
		obj_iterator = obj_iterator->super){
		if(iter_count++ > max_iter){
			error_log("iter_count>max but class still can not response to method\n");
			break;
		}
		if((met_item=get_item_byhash(&(obj_iterator->isa->table), hashval, methodname)) != nil) {
			runtime_log("hit a method [%s/%d] to match [%s]\n", 
				met_item->key, met_item->index, methodname);
			hit_count++;
			tmpmsg.object = obj_iterator;
			tmpmsg.addr = met_item->value;
			if(obj_first_hit==nil)obj_first_hit = obj_iterator;
			if(met_first_hit==nil)met_first_hit = met_item;
			//for the method key have conflicted with some super class in inherit tree
			if(hit_count>1){
				if(hit_count==2){
					//to support the "overide" feature of oop
					if(mc_compare_key(met_first_hit->key, methodname) == 0){
						tmpmsg.object = obj_first_hit;
						runtime_log("return a message[%s/%s]\n", tmpmsg.object->isa->item->key, methodname);
						return tmpmsg;}
				}
				if(mc_compare_key(met_item->key, methodname) == 0){
					tmpmsg.object = obj_iterator;
					runtime_log("return a message[%s/%s]\n", tmpmsg.object->isa->item->key, methodname);
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

