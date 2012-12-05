#include "MCRuntime.h"

int main(int argc, char const *argv[])
{
	New(MCContext, context, argc, argv);
	return MCRuntime_runloop(context);
}

/* global runtime functions */

void set_super(id const child_in, id const father_in)
{
	MCObject* child = (MCObject*) child_in;
	MCObject* father = (MCObject*) father_in;

	child->isa->super = father->isa;//link class node
	child->super_instance = father;//set member instance
}

static void clear_method_list(id const self_in)
{
	MCObject* self = (MCObject*)self_in;
	int i;
	for (i = 0; i < MAX_METHOD_NUM; ++i)
		self->isa->method_list[i]==0;
}

void setting_start(id const self_in, char* name_in)
{
	MCObject* self = (MCObject*)self_in;

	Alloc(MCClass, class);
	self->isa = class;
	self->ref_count = 1;
	self->super_instance = nil;
	self->isa->super = nil;
	self->isa->method_index = 0;
	self->isa->cached_index = 0;
	self->isa->cached_method_tag = nil;
	self->isa->cached_method = nil;
	self->isa->name = name_in;
	clear_method_list(self);
}

/*you can not call this!*/
static void destroy(id const instance)
{
	if(instance!=nil){
		MCObject* this = (MCObject*) instance;
		if(this->isa==nil)return;
		printf("%s: goodbye!\n", this->isa->name);
		free(this->isa);//free class obj
		free(this);//free instance
	}else return;
}

//void release(id const instance, funcptr(bye_callback))
void release(id const instance)
{
	MCObject* this;
	if(instance!=nil){this = (MCObject*) instance;}
	else return;

	if(this->ref_count>0)
	{
		this->ref_count--;
		printf("%s - ref_count:%d\n", this->isa->name, this->ref_count);
	}
	if (this->ref_count==0)
	{
		//(*bye_callback)(this, nil);
		ff(this, MT(bye), nil);
		destroy(this);
	}
}

void retain(id const instance)
{
	MCObject* this;
	if(instance!=nil){MCObject* this = (MCObject*) instance;}
	else return;

	this->ref_count++;
	printf("%s - ref_count:%d\n", this->isa->name, this->ref_count);
}

int bind_method(id const self_in, funcptr(mptr))
{
	MCObject* self = (MCObject*)self_in;

	if(self->isa->method_index > MAX_METHOD_NUM-1){
		printf("method index out of bound\n");
		return -1;
	}
	self->isa->method_list[self->isa->method_index] = mptr;
	self->isa->method_index++;
	printf("add a method, index:%d\n",self->isa->method_index-1);
	return self->isa->method_index-1;
}

static const int CACHED = -2;
static const int NOT_RESPONSE = -1;
static int response_to_method(id const self_in, funcptr(name))
{
	MCObject* self = (MCObject*)self_in;

	if(name==self->isa->cached_method)return CACHED;

	int i;
	for (i = 0; i < (MAX_METHOD_NUM-1); ++i)
	{
		if(i > self->isa->method_index)return NOT_RESPONSE;
		if(self->isa->method_list[i]==name)return i;
	}
	return NOT_RESPONSE;
}

BOOL is_response(id const self_in, funcptr(name))
{
	MCObject* obj = (MCObject*)self_in;
	MCClass* cls_save = obj->isa;
	MCClass* cls = obj->isa;

	int res;
	while((res=response_to_method(obj, name))==NOT_RESPONSE){
		if(cls->super != nil){
			cls = cls->super;
			obj->isa = cls;
		}else{
			return NO;
		}
	}

	obj->isa = cls_save;
	return YES;
}

id call(id const self_in, funcptr(name), ...)
{
	MCObject* obj = (MCObject*)self_in;
	MCClass* cls_save = obj->isa;
	MCClass* cls = obj->isa;

	void *args, *result;
	args = __builtin_apply_args();

	int res;
	while((res=response_to_method(obj, name))==NOT_RESPONSE){
		if(cls->super != nil){
			cls = cls->super;
			obj->isa = cls;
			printf("%s\n", "continue to my super");
		}else{
			printf("%s\n", "no such method! are you forget to bind_method()? MC_call return");
			return;
		}
	}

	if (res==CACHED){
		printf("%s\n", "call cached method");
		result = __builtin_apply(cls_save->cached_method, args, 96);
	}else{
		result = __builtin_apply(cls->method_list[res], args, 96);
	}

	obj->isa = cls_save;
	obj->isa->cached_index = res;
	obj->isa->cached_method = name;

	if(result)
		__builtin_return(result);
	else
		return;
}

/* try some hash-based implementation */

/* copy form << The C Programming language >> */
unsigned hash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % MAX_METHOD_NUM;
}

BOOL strequal(char *str1, char *str2)
{
	int res = strcmp(str1, str2);
	if(res == 0)return YES;
	return NO;
}

int bind(id const self_in, char *key, funcptr(mptr))
{
	MCObject* self = (MCObject*)self_in;
	if(self->isa->method_list[0]!=0){
		printf("%s\n", "please call setting_start() at the begin of init method");
		return -1;
	}

	if(self->isa->method_index > MAX_METHOD_NUM-1){
		printf("method index out of bound\n");
		return -1;
	}
	unsigned hashkey = hash(key);
	self->isa->method_list[hashkey] = mptr;
	self->isa->method_index++;
	printf("add a method, hash index:%d\n",hashkey);
	return hashkey;
}

static int _response_to_method(id const self_in, char *key)
{
	MCObject* self = (MCObject*)self_in;
	if(self->isa->cached_method_tag!=nil){
		if(strcmp(key, self->isa->cached_method_tag)==0)
			return CACHED;
	}

	unsigned hashkey = hash(key);
	if(self->isa->method_list[hashkey]==0)
		return NOT_RESPONSE;
	else
		return hashkey;
}

BOOL response(id const self_in, char *key)
{
	MCObject* self = (MCObject*)self_in;
	if(self->isa->method_list[hash(key)]==0)
		return NO;
	else
		return YES;
}

/* ff is short for [fire function] */
static const int METHOD_NAME_BUFF_SIZE = 100;
id ff(id const self_in, char *key, ...)
{
	MCObject* obj = (MCObject*)self_in;
	MCClass* cls_save = obj->isa;
	MCClass* cls = obj->isa;

	void *args, *result;
	args = __builtin_apply_args();

	int res;
	while((res=_response_to_method(obj, key))==NOT_RESPONSE){
		if(cls->super != nil){
			cls = cls->super;
			obj->isa = cls;
			printf("%s\n", "continue to my super");
		}else{
			printf("%s_%s: %s\n", cls->name, key, 
				"no such method! are you forget to bind_method()? MC_call return");
			return;
		}
	}

	obj->isa = cls_save;
	if (res==CACHED){
		printf("%s\n", "Call cached method");
		result = __builtin_apply(cls_save->cached_method, args, 96);
	}else{
		printf("%s\n", "Call method");
		result = __builtin_apply(cls->method_list[res], args, 96);
		char buff[METHOD_NAME_BUFF_SIZE];
		strcpy(buff, key);
		cls_save->cached_method_tag = buff;
		cls_save->cached_index = res;
		cls_save->cached_method = cls->method_list[res];
	}

	if(result)
		__builtin_return(result);
	else
		return;
}