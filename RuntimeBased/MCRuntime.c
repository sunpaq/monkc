#include "MCRuntime.h"
#include "MCContext.h"
//default we set log level to debug
LOG_LEVEL = DEBUG;

int main(int argc, char const *argv[])
{
	LOG_LEVEL = SILENT;
	New(MCContext, context, argc, argv);
	LOG_LEVEL = DEBUG;
	int res = MCContext_runloop(context);
	release(context);
	return res;
}

/* global runtime functions */
//error log will always output
void error_log(char* fmt, ...)
{
	if(LOG_LEVEL!=SILENT){

		void *args;
		args = __builtin_apply_args();
		__builtin_apply(printf, args, 96);
	}
}

void debug_log(char* fmt, ...)
{
	if(LOG_LEVEL!=SILENT
	 &&LOG_LEVEL!=ERROR_ONLY){

		void *args;
		args = __builtin_apply_args();
		__builtin_apply(printf, args, 96);
	}
}

//you can shutdown the runtime log by RUNTIME_LOG_OFF = YES
void runtime_log(char* fmt, ...)
{
	if(LOG_LEVEL!=SILENT
	 &&LOG_LEVEL!=ERROR_ONLY
	 &&LOG_LEVEL!=DEBUG){

		void *args;
		args = __builtin_apply_args();
		__builtin_apply(printf, args, 96);
	}
}

static void _nil_check(MCObject* const self, 
	char* log1, char* log2, char* log3, 
	char* log4, char* log5, char* log6){
	if(self==nil){
		error_log("%s:\n%s\n%s\n", log1, log2, log3);
		exit(-1);
	}
	if(self->isa==nil){
		error_log("%s:\n%s\n%s\n", log4, log5, log6);
		exit(-1);
	}
}

void set_super(id const child_in, id const father_in)
{
	MCObject* child = (MCObject*) child_in;
	MCObject* father = (MCObject*) father_in;
	_nil_check(child, 
		"set_super(child, father)", 
		"child is nil.",
		"please check your code.",
		"set_super(child, father).",
		"child have no class object linked.",
		"please call setting_start() at the very begin of child init method.");
	_nil_check(father,
		"set_super(child, father)", 
		"father is nil.",
		"please check your code.",
		"set_super(child, father).",
		"father have no class object linked.",
		"please call setting_start() at the very begin of father init method.");

	child->isa->super = father->isa;//link class node
	child->super_instance = father;//set member instance
}

static void _clear_method_list(id const self_in)
{
	MCObject* self = (MCObject*)self_in;
	int i;
	for (i = 0; i < MAX_METHOD_NUM; ++i)
		self->isa->method_list[i]==0;
}

void setting_start(id const self_in, char* name_in)
{
	MCObject* self = (MCObject*)self_in;
	MCClass* class = (MCClass*)malloc(sizeof(MCClass));
	self->isa = class;
	self->ref_count = 1;
	self->super_instance = nil;
	self->isa->super = nil;
	self->isa->method_index = 0;
	self->isa->cached_index = 0;
	self->isa->cached_method_tag = nil;
	self->isa->cached_method = nil;
	self->isa->name = name_in;
	_clear_method_list(self);
}

void setting_end(id const self_in, funcptr(bye_mptr))
{
	MCObject* self = (MCObject*)self_in;
	_nil_check(self,
		"setting_end(obj, bye_method_address).",
		"obj is nil.",
		"please check your code.",
		"setting_end(obj, bye_method_address).",
		"obj have no class object linked.",
		"please call setting_start() at the very begin of init method.");

	bind(self, MT(bye), bye_mptr);
}

/*you can not call this!*/
static void destroy(id const instance)
{
	MCObject* this = (MCObject*) instance;
	_nil_check(this,
		"destroy(obj).",
		"obj is nil.",
		"please check your code.",
		"destroy(obj)",
		"obj have no class object linked.",
		"please call setting_start() at the very begin of init method.");

	runtime_log("----Bye: %s goodbye!\n", this->isa->name);
	free(this->isa);//free class obj
	free(this);//free instance
}

//void release(id const instance, funcptr(bye_callback))
void release(id const instance)
{
	MCObject* this = (MCObject*) instance;
	_nil_check(this,
		"release(obj).",
		"obj is nil.",
		"please check your code.",
		"release(obj)",
		"obj have no class object linked.",
		"are you release obj twice?.");

	if(this->ref_count>0)
	{
		this->ref_count--;
		runtime_log("%s - ref_count:%d\n", this->isa->name, this->ref_count);
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
	MCObject* this = (MCObject*) instance;
	_nil_check(this,
		"retain(obj).",
		"obj is nil.",
		"please check your code.",
		"retain(obj)",
		"obj have no class object linked.",
		"please call setting_start() at the very begin of init method.");

	this->ref_count++;
	runtime_log("%s - ref_count:%d\n", this->isa->name, this->ref_count);
}

int bind_method(id const self_in, funcptr(mptr))
{
	MCObject* self = (MCObject*)self_in;

	if(self->isa->method_index > MAX_METHOD_NUM-1){
		error_log("method index out of bound\n");
		return -1;
	}
	self->isa->method_list[self->isa->method_index] = mptr;
	self->isa->method_index++;
	error_log("add a method, index:%d\n",self->isa->method_index-1);
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
			error_log("%s\n", "continue to my super");
		}else{
			error_log("%s\n", "no such method! are you forget to bind_method()? MC_call return");
			return;
		}
	}

	if (res==CACHED){
		error_log("%s\n", "call cached method");
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
	_nil_check(self,
		"bind(obj, key, MA)",
		"obj is nil, the key is:",
		key,
		"bind(obj, key, MA)",
		"obj have no class object linked. please call setting_start(). the key is:",
		key);

	unsigned hashkey = hash(key);
	if(self->isa->method_list[hashkey]!=0){
		error_log("%s_%s:\n%s\n%s\n",
			self->isa->name, key,
			"the method already binded, you should call override() instead.",
			"or your method name hash conflict with other method, change a name please");
		exit(-1);
	}

	if(self->isa->method_index > MAX_METHOD_NUM-1){
		error_log("method index out of bound\n");
		exit(-1);
	}
	self->isa->method_list[hashkey] = mptr;
	self->isa->method_index++;
	runtime_log("add a method, hash index:%d\n",hashkey);
	return hashkey;
}

int override(id const self_in, char *key, funcptr(mptr))
{
	MCObject* self = (MCObject*)self_in;
	_nil_check(self,
		"override(obj, key, MA)",
		"obj is nil, the key is:",
		key,
		"override(obj, key, MA)",
		"obj have no class object linked. please call setting_start(). the key is:",
		key);

	unsigned hashkey = hash(key);
	if(self->isa->method_index > MAX_METHOD_NUM-1){
		error_log("method index out of bound\n");
		exit(-1);
	}
	self->isa->method_list[hashkey] = mptr;
	self->isa->method_index++;
	//runtime_log("add a method, hash index:%d\n",hashkey);
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
	_nil_check(self,
		"response(obj, key)",
		"obj is nil, the key is:",
		key,
		"response(obj, key)",
		"obj have no class object linked. please call setting_start(). the key is:",
		key);

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
	_nil_check(obj,
		"ff(obj, key, ...)",
		"obj is nil, the key is:",
		key,
		"ff(obj, key, ...)",
		"obj have no class object linked. please call setting_start(). the key is:",
		key);

	MCClass* cls_save = obj->isa;
	MCClass* cls = obj->isa;

	void *args, *result;
	args = __builtin_apply_args();

	int res;
	while((res=_response_to_method(obj, key))==NOT_RESPONSE){
		if(cls->super != nil){
			cls = cls->super;
			obj->isa = cls;
			//runtime_log("%s\n", "continue to my super");
		}else{
			runtime_log("%s_%s: %s\n", cls->name, key, 
				"no such method! are you forget to bind_method()? MC_call return");
			return;
		}
	}

	obj->isa = cls_save;
	if (res==CACHED){
		runtime_log("%s\n", "Call cached method");
		result = __builtin_apply(cls_save->cached_method, args, 96);
	}else{
		runtime_log("%s\n", "Call method");
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