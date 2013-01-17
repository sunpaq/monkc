#include "MCRuntime.h"
#include "MCContext.h"
//default we set log level to debug
LOG_LEVEL = DEBUG;

//global var set in _init_class_list
static unsigned _init_method_hashkey;
static unsigned _hash(char *s);
static unsigned _classobj_hash(char *s);
static void _nil_check(id const self, 
	char* log1, char* log2, char* log3, 
	char* log4, char* log5, char* log6, pthread_mutex_t* lock);
static void _clear_method_list(id const self_in);
static void _init_class_list();
static void _clear_class_list();
static MCClass* mc_classobj_pool[MAX_CLASS_NUM];
static const int NOT_RESPONSE = -1;
static int _response_to_method(MCClass* const self_in, char *key);
static void _destroy(id this);
static inline MCClass* get_class(const char* name_in);
void* mc_malloc(size_t size);
void* mc_realloc(void* ptr, size_t size);
void  mc_free(void* ptr);

//C-main

int main(int argc, char const *argv[])
{
	#ifndef __GNUC__
	printf("%s\n%s\n%s\n%s\n%s\n%s\n",
	"I am sorry, as the Mocha use some GNU C extentions which is very important.",
	"your code complied in non-gcc complier will not run correctlly.",
	"so i stop at here. please consider to use gcc. I construct Mocha use gcc-4.6.1",
	"if you are using a new Mac. you can install a gcc from here:",
	"",
	"https://github.com/kennethreitz/osx-gcc-installer");
	exit(-1);
	#endif

	_init_class_list();
		LOG_LEVEL = DEBUG;
		MCContext* context = new(MCContext, argc, argv);
		LOG_LEVEL = DEBUG;

		int res = MCContext_runloop(context);

		LOG_LEVEL = DEBUG;
		release(context);
	_clear_class_list();
	//end point for pthread
	//main() is blocked here
	//and the whole process will not shutdown to support the other
	//running threads
	pthread_exit(nil);
	return res;
}

id MCObject_doNothing(id const this, char* cmd, xxx)
{
	//do nothing
}

id MCObject_bye(id this, char* cmd, xxx)
{
	//do nothing
}

id MCObject_init(id const this, char* cmd, xxx)
{
	//do nothing
}

id MCObject_whatIsYourClassName(id const this, char* cmd, xxx)
{
	if(this!=nil&&this->isa!=nil)printf("My class name is:%s\n", this->isa->name);
}

void error_log(char* fmt, ...)
{
	if(LOG_LEVEL!=SILENT){

		void *args;
		args = __builtin_apply_args();
		printf(LOG_FMT, LOG_COLOR_RED, "[Error] - ");
		//printf("%s", "[Error] - ");
		__builtin_apply(printf, args, 96);
	}
}

void debug_log(char* fmt, ...)
{
	if(LOG_LEVEL!=SILENT
	 &&LOG_LEVEL!=ERROR_ONLY){

		void *args;
		args = __builtin_apply_args();
		printf(LOG_FMT, LOG_COLOR_LIGHT_BLUE, "[Debug] - ");
		//printf("%s", "[Debug] - ");
		__builtin_apply(printf, args, 96);
	}
}

void runtime_log(char* fmt, ...)
{
	if(LOG_LEVEL!=SILENT
	 &&LOG_LEVEL!=ERROR_ONLY
	 &&LOG_LEVEL!=DEBUG){

		void *args;
		args = __builtin_apply_args();
		printf(LOG_FMT, LOG_COLOR_DARK_GRAY, "[RTime] - ");
		//printf("%s", "[RTime] - ");
		__builtin_apply(printf, args, 96);
	}
}

pthread_mutex_t _mc_runtime_mutex = PTHREAD_MUTEX_INITIALIZER;
static MCClass* load_class(const char* name_in, const char* super_class)
{
	//pthread_mutex_lock(&_mc_runtime_mutex);
	MCClass* old;
	if ((old=get_class(name_in))!=nil)
	 	return old;

	int super_hashkey = _classobj_hash(super_class);
	if(super_hashkey>MAX_CLASS_NUM){
		error_log("%s hashkey is out of bound\n",super_class);
		exit(-1);
	}

	MCClass* superclass = mc_classobj_pool[super_hashkey];
	if(superclass==nil){
		error_log("there is no superclass %s.please load it first!\n", super_class);
		exit(-1);
	}

	MCClass* class = (MCClass*)mc_malloc(sizeof(MCClass));

	int i;
	for (i = 0; i < MAX_METHOD_NUM; ++i)
		class->method_list[i]==0;
	//set the class name
	class->name = name_in;
	class->super = superclass;
	class->method_count = 0;

	//conflict check
	int hashkey = _classobj_hash(name_in);
	if(mc_classobj_pool[hashkey]!=nil){
		error_log("load_class(%s, %s) - name hash value conflict.\nplease change a name\n", name_in, super_class);
		exit(-1);
	}
	mc_classobj_pool[hashkey]=class;
	//pthread_mutex_unlock(&_mc_runtime_mutex);
	return class;
}

static inline MCClass* get_class(const char* name_in)
{
	int hashkey = _classobj_hash(name_in);
	return mc_classobj_pool[hashkey];
}

BOOL set_class(id const self_in, const char* classname, const char* superclassname)
{
	pthread_mutex_lock(&_mc_runtime_mutex);
	if (self_in==nil)
	{
		error_log("set_class(obj, classname).\nobj should not be nil");
		exit(-1);
	}

	runtime_log("set_class(obj, class:%s, super:%s)\n", classname ,superclassname);
	//init the obj vars
	self_in->ref_count = 1;

	//load class
	MCClass* class=get_class(classname);

	if(self_in->need_bind_method!=YES){
		runtime_log("super_init: %s no need bind methods\n",classname);
		pthread_mutex_unlock(&_mc_runtime_mutex);
		return NO;
	}

	if(class!=nil){
		runtime_log("class: %s already loaded\n",classname);
		self_in->isa = class;
		pthread_mutex_unlock(&_mc_runtime_mutex);
		return NO;
	}else{
		runtime_log("new load a class: %s\n", classname);
		class = load_class(classname, superclassname);
		self_in->isa = class;
		pthread_mutex_unlock(&_mc_runtime_mutex);
		return YES;
	}
}

pthread_mutex_t _mc_mm_mutex = PTHREAD_MUTEX_INITIALIZER;
void release(id this)
{
	pthread_mutex_lock(&_mc_mm_mutex);

	if(this==nil){
		error_log("%s\n", "release(nil) do nothing.");
		pthread_mutex_unlock(&_mc_mm_mutex);
		return;
	}
	if(this->isa==nil){
		error_log("release(%d) twice. do nothing.\n", this);
		pthread_mutex_unlock(&_mc_mm_mutex);
		return;
	}
	if((this!=nil)&&(this->ref_count>0))
	{
		this->ref_count--;
		runtime_log("%s - ref_count:%d\n", this->isa->name, this->ref_count);
	}

	pthread_mutex_unlock(&_mc_mm_mutex);

	if(this->ref_count==0)
	{
		ff(this, MK(bye), nil);
		_destroy(this);
	}
}

void retain(id const this)
{
	pthread_mutex_lock(&_mc_mm_mutex);
	_nil_check(this,
		"retain(obj).",
		"obj is nil.",
		"please check your code.",
		"retain(obj)",
		"obj have no class object linked.",
		"please call set_class() at the very begin of init method.", &_mc_mm_mutex);

	this->ref_count++;
	runtime_log("%s - ref_count:%d\n", this->isa->name, this->ref_count);
	pthread_mutex_unlock(&_mc_mm_mutex);
}

int bind_method(id const self, char *key, _FunctionPointer(value))
{
	pthread_mutex_lock(&_mc_runtime_mutex);
	_nil_check(self,
		"bind(obj, key, MA)",
		"obj is nil, the key is:",
		key,
		"bind(obj, key, MA)",
		"obj have no class object linked. please call set_class(). the key is:",
		key, &_mc_runtime_mutex);

	unsigned hashkey = _hash(key);
	if(self->isa->method_list[hashkey]!=0){
		error_log("%s_%s(%d):\n%s\n%s\n%s\n",
			self->isa->name, key, hashkey,
			"1. are the child called set_class()? please call bind() in if(set_class()){ }",
			"2. the method already binded, you should call override() instead.",
			"3. or your method name hash conflict with other method, change a name please");
		pthread_mutex_unlock(&_mc_runtime_mutex);
		exit(-1);
	}

	if(self->isa->method_count > MAX_METHOD_NUM-1){
		error_log("method index out of bound\n");
		pthread_mutex_unlock(&_mc_runtime_mutex);
		exit(-1);
	}
	self->isa->method_list[hashkey] = value;
	self->isa->method_count++;
	runtime_log("add a method, hash index:%d  [ %s ]\n",hashkey, key);
	pthread_mutex_unlock(&_mc_runtime_mutex);
	return hashkey;
}

int override(id const self, char *key, _FunctionPointer(value))
{
	pthread_mutex_lock(&_mc_runtime_mutex);
	_nil_check(self,
		"override(obj, key, MA)",
		"obj is nil, the key is:",
		key,
		"override(obj, key, MA)",
		"obj have no class object linked. please call setting_start(). the key is:",
		key, &_mc_runtime_mutex);

	unsigned hashkey = _hash(key);
	if(self->isa->method_count > MAX_METHOD_NUM-1){
		error_log("method index out of bound\n");
		pthread_mutex_unlock(&_mc_runtime_mutex);
		exit(-1);
	}
	self->isa->method_list[hashkey] = value;
	self->isa->method_count++;
	runtime_log("add a method, hash index:%d\n",hashkey);
	pthread_mutex_unlock(&_mc_runtime_mutex);
	return hashkey;
}

BOOL response(id const obj, char *key)
{
	pthread_mutex_lock(&_mc_runtime_mutex);
	_nil_check(obj,
		"response(obj, key)",
		"obj is nil, the key is:",
		key,
		"response(obj, key)",
		"obj have no class object linked. please call set_class(). the key is:",
		key, &_mc_runtime_mutex);

	MCClass* cls_save = obj->isa;
	MCClass* cls = obj->isa;

	int res;
	while((res=_response_to_method(obj, key))==NOT_RESPONSE){
		if(cls->super != nil){
			cls = cls->super;
			obj->isa = cls;
			//runtime_log("%s\n", "continue to my super");
		}else{
			runtime_log("%s_%s: %s\n", cls->name, key, 
				"no such method! are you forget to bind()? MC_call return");
			pthread_mutex_unlock(&_mc_runtime_mutex);
			return NO;
		}
	}

	obj->isa = cls_save;
	pthread_mutex_unlock(&_mc_runtime_mutex);
	return YES;
}

/* ff is short for [fire function] */
id ff(const id obj, const char *key, ...)
{
	runtime_log("ff start\n");

	_nil_check(obj,
		"ff(obj, key, ...)",
		"obj is nil, the key is:",
		key,
		"ff(obj, key, ...)",
		"obj have no class object linked. please call set_class(). the key is:",
		key, &_mc_runtime_mutex);

	MCClass* cls_save = obj->isa;
	MCClass* cls = obj->isa;

	runtime_log("ff before loop obj:%d, cls:%d, cls_save:%d\n", obj, cls, cls_save);

	int res;
	while((res=_response_to_method(cls, key))==NOT_RESPONSE){
		if(cls->super != nil){
			cls = cls->super;
			runtime_log("%s\n", "continue to my super");
		}else{
			runtime_log("[%s] reach the root class: %s return\n", key, cls->name);
			return;
		}
	}

	pthread_mutex_lock(&_mc_runtime_mutex);
	runtime_log("%s obj->isa:%d\n", "ff middle", obj->isa);
	if((res < MAX_METHOD_NUM) && (cls_save->method_list[res]==0)){
		runtime_log("----Cache method: %s+%s\n", cls_save->name, key);
		cls_save->method_list[res]=cls->method_list[res];//new cache logic
	}
	pthread_mutex_unlock(&_mc_runtime_mutex);

	runtime_log("----Call method: %s+%s\n", cls_save->name, key);
	void *args, *result;
	args = __builtin_apply_args();

	runtime_log("%s args:%u cls:%u, cls->method_list:%u\n", "ff unlocked", args, cls, cls->method_list);
	result = __builtin_apply(cls->method_list[res], args, 96);

	if(result)
		__builtin_return(result);
	else
		return;
}

/* ff-release, for the fr(New(Class, nil), MK(method), nil)*/
id fr(const id obj, const char *key, ...)
{
	//copy from ff
	_nil_check(obj,
		"ff(obj, key, ...)",
		"obj is nil, the key is:",
		key,
		"ff(obj, key, ...)",
		"obj have no class object linked. please call set_class(). the key is:",
		key, &_mc_runtime_mutex);

	MCClass* cls_save = obj->isa;
	MCClass* cls = obj->isa;

	int res;
	while((res=_response_to_method(cls, key))==NOT_RESPONSE){
		if(cls->super != nil){
			cls = cls->super;
			//runtime_log("%s\n", "continue to my super");
		}else{
			runtime_log("%s_%s: %s\n", cls->name, key, 
				"no such method! are you forget to bind()? MC_call return");
			return;
		}
	}

	pthread_mutex_lock(&_mc_runtime_mutex);
	if((res < MAX_METHOD_NUM) && (cls_save->method_list[res]==0)){
		cls_save->method_list[res]=cls->method_list[res];//new cache logic
		runtime_log("----Cache method: %s+%s\n", cls_save->name, key);
	}
	pthread_mutex_unlock(&_mc_runtime_mutex);

	runtime_log("----Call method: %s+%s\n", cls_save->name, key);
	void *args, *result;
	args = __builtin_apply_args();
	result = __builtin_apply(cls->method_list[res], args, 96);

release(obj);

	if(result)
		__builtin_return(result);
	else
		return;
}

/* copy form << The C Programming language >> */
static inline unsigned _hash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % MAX_METHOD_NUM;
}

static inline unsigned _classobj_hash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % MAX_CLASS_NUM;
}

static inline void _nil_check(id const self, 
	char* log1, char* log2, char* log3, 
	char* log4, char* log5, char* log6,
	pthread_mutex_t* lock){
	if(self==nil){
		error_log("%s:\n%s\n%s\n", log1, log2, log3);
		if(lock!=nil)pthread_mutex_unlock(lock);
		exit(-1);
	}
	if(self->isa==nil){
		error_log("%s:\n%s\n%s\n", log4, log5, log6);
		if(lock!=nil)pthread_mutex_unlock(lock);
		exit(-1);
	}
}

static inline void _clear_method_list(id const self_in)
{
	MCObject* self = (MCObject*)self_in;
	int i;
	for (i = 0; i < MAX_METHOD_NUM; ++i)
		self->isa->method_list[i]==0;
}

static void _init_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; ++i)
		mc_classobj_pool[i]==nil;

	MCClass* class = (MCClass*)mc_malloc(sizeof(MCClass));
	class->name = "MCObject";
	class->super=nil;
	//bind the builtin MCObject methods
	class->method_list[_hash("doNothing")] = MCObject_doNothing;
	class->method_list[_hash("bye")] = MCObject_bye;
	class->method_list[_hash("whatIsYourClassName")] = MCObject_whatIsYourClassName;
	//load the MCObject class
	mc_classobj_pool[_classobj_hash("MCObject")]=class;
	//for init method judgement
	_init_method_hashkey=_hash("init");
}

static void _clear_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; ++i){
		MCClass* tmp = mc_classobj_pool[i];
		if(tmp!=nil)mc_free(tmp);
	}
}

static inline int _response_to_method(MCClass* const cls, char *key)
{
	unsigned hashkey = _hash(key);
	if((cls->method_list!=nil)&&(cls->method_list[hashkey]==0)){
		return NOT_RESPONSE;
	}
	else{
		return hashkey;
	}
}

//call _destroy(this) twice the same address will cause SegmentFault
static void _destroy(id this)
{
	// _nil_check(this,
	// 	"destroy(obj).",
	// 	"obj is nil.",
	// 	"please check your code.",
	// 	"destroy(obj)",
	// 	"obj have no class object linked.",
	// 	"please call set_class() at the very begin of init method.", nil);

	if((this!=nil) && (this->isa!=nil)){
		//runtime_log("----Bye: %s goodbye!\n", this->isa->name);
		this->isa=nil;//unlink to the class
		runtime_log("----Bye: goodbye!\n");
		free(this);
		this=nil;
	}else{
		error_log("release twice\n");
	}
}

pthread_mutex_t _mc_alloc_mutex = PTHREAD_MUTEX_INITIALIZER;
void* mc_malloc(size_t size)
{
	pthread_mutex_lock(&_mc_alloc_mutex);

	void* ret = malloc(size);

	pthread_mutex_unlock(&_mc_alloc_mutex);
	return ret;
}

void* mc_realloc(void* ptr, size_t size)
{
	pthread_mutex_lock(&_mc_alloc_mutex);

	void* ret = realloc(ptr, size);

	pthread_mutex_unlock(&_mc_alloc_mutex);
	return ret;
}

pthread_mutex_t _mc_free_mutex = PTHREAD_MUTEX_INITIALIZER;
void mc_free(void *ptr)
{
	pthread_mutex_lock(&_mc_free_mutex);

	free(ptr);

	pthread_mutex_unlock(&_mc_free_mutex);
}