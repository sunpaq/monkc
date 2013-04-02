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

static const int NOT_RESPONSE = -1;

static MCClass* mc_classobj_pool[MAX_CLASS_NUM];
static inline MCClass* get_class(const char* name_in);
static void _init_class_list();
static void _clear_class_list();

static void _nil_check(id const self, 
	char* log1, char* log2, char* log3, 
	char* log4, char* log5, char* log6, pthread_mutex_t* lock);
static void _clear_method_list(MCClass* const class);
static unsigned _response_to_method(MCClass* const self_in, unsigned hashkey);

//object pool for annoymous objects
static MCObject* mc_anony_pool[100];
static unsigned mc_anony_count = 0;
static void _init_anony_pool()
{
	int i;
	for (i = 0; i < 100; i++)
		mc_anony_pool[i]=nil;
}

static void _push_anony_obj(MCObject* anony)
{
	if(anony==nil)return;

	mc_anony_count++;
	if(mc_anony_count > 100) mc_anony_count=0;
	if(mc_anony_pool[mc_anony_count] != nil)
		relnil(mc_anony_pool[mc_anony_count]);
	
	mc_anony_pool[mc_anony_count] = anony;
}

//pop do not release the obj, when a anony obj is poped from pool
//you need manage it by retain/release manually
static void _pop_anony_obj(MCObject* anony)
{
	if(anony==nil)return;
	int i;
	for (i = 0; i < 100; i++)
		if(mc_anony_pool[i]==anony)mc_anony_pool[i]=nil;
}

void mc_init()
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

	//default we set log level to debug
	LOG_LEVEL = DEBUG;
	_init_class_list();
	//_init_float_pool();
}

void mc_end()
{
	//end point for pthread
	//main() is blocked here
	//and the whole process will not shutdown to support the other
	//running threads
	_clear_class_list();
}

void MCObject_doNothing(id const this, unsigned hashkey, xxx)
{
	//do nothing
}

void MCObject_bye(id this, unsigned hashkey, xxx)
{
	//do nothing
}

id MCObject_init(id const this, unsigned hashkey, xxx)
{
	//do nothing
	this->isa = get_class("MCObject");
	return this;
}

void MCObject_whatIsYourClassName(id const this, unsigned hashkey, xxx)
{
	if(this != nil && this->isa != nil)
		debug_log("My class name is:%s\n", this->isa->name);
}

static void load_root_class(){
	MCClass* class = (MCClass*)mc_malloc(sizeof(MCClass));
	class->name = "MCObject";
	class->super = nil;
	//bind the builtin MCObject methods
	class->method_list[_hash("doNothing")]=MCObject_doNothing;
	class->method_list[_hash("whatIsYourClassName")]=MCObject_whatIsYourClassName;
	class->method_list[_hash("bye")]=MCObject_bye;

	//load the MCObject class
	mc_classobj_pool[_chash("MCObject")] = class;
}

pthread_mutex_t _mc_runtime_mutex = PTHREAD_MUTEX_INITIALIZER;
static MCClass* load_class(const char* name_in, const char* super_class)
{
	//pthread_mutex_lock(&_mc_runtime_mutex);
	MCClass* oldclass;
	if ((oldclass=get_class(name_in)) != nil){
		error_log("class name:%s hash is conflict with class name:%s hash.\n", name_in, oldclass->name);
		exit(-1);
	}

	int super_hashkey = _chash(super_class);

	MCClass* superclass = mc_classobj_pool[super_hashkey];
	if(superclass == nil){
		error_log("there is no superclass %s.please load it first!\n", super_class);
		exit(-1);
	}

	MCClass* class = (MCClass*)mc_malloc(sizeof(MCClass));

	//set the class name
	class->name = name_in;
	class->super = superclass;
	class->method_count = 0;

	//conflict check
	int hashkey = _chash(name_in);
	if(mc_classobj_pool[hashkey] != nil){
		error_log("load_class(%s, %s) - name hash value conflict.\nplease change a name\n", name_in, super_class);
		exit(-1);
	}

	_clear_method_list(class);
	mc_classobj_pool[hashkey] = class;
	//pthread_mutex_unlock(&_mc_runtime_mutex);
	return class;
}

static inline MCClass* get_class(const char* name_in)
{
	int hashkey = _chash(name_in);
	return mc_classobj_pool[hashkey];
}

BOOL set_class(id const self_in, const char* classname, const char* superclassname)
{
	pthread_mutex_lock(&_mc_runtime_mutex);
	if (self_in == nil)
	{
		error_log("set_class(obj, classname).obj should not be nil\n");
		exit(-1);
	}

	if(self_in->need_bind_method != YES){
		runtime_log("super_init: %s no need bind methods\n",classname);
		pthread_mutex_unlock(&_mc_runtime_mutex);
		return NO;
	}

	runtime_log("set_class: %s->%s\n", classname ,superclassname);

	//load class
	MCClass* class;
	if ((class = get_class(classname)) != nil)
	{
		runtime_log("class: %s already loaded\n",classname);
		self_in->isa = class;
		pthread_mutex_unlock(&_mc_runtime_mutex);
		return NO;
	}else{
		runtime_log("load_class: %s\n", classname);
		class = load_class(classname, superclassname);
		self_in->isa = class;
		pthread_mutex_unlock(&_mc_runtime_mutex);
		return YES;
	}
}

pthread_mutex_t _mc_mm_mutex = PTHREAD_MUTEX_INITIALIZER;
void release(id const this)
{
	pthread_mutex_lock(&_mc_mm_mutex);

	if(this == nil){
		error_log("%s\n", "release(nil) do nothing.");
		pthread_mutex_unlock(&_mc_mm_mutex);
		return;
	}
	if(this->isa == nil){
		error_log("release(%d) twice. do nothing.\n", this);
		pthread_mutex_unlock(&_mc_mm_mutex);
		return;
	}
	if (this->ref_count == REFCOUNT_NO_MM)
	{
		debug_log("ref_count is -1 manage by runtime. do nothing\n");
		pthread_mutex_unlock(&_mc_mm_mutex);
		return;
	}
	if (this->ref_count == REFCOUNT_ANONY_OBJ)
	{
		//for anony object
		_pop_anony_obj(this);
		this->ref_count = 0;
	}
	if (this->ref_count > 0)
	{
		this->ref_count--;
		//runtime_log("%s - ref_count:%d\n", this->isa->name, this->ref_count);
	}

	pthread_mutex_unlock(&_mc_mm_mutex);

	if(this->ref_count == 0)
	{
		//call all the "bye" method on object: this
		//so that all the super clean work will be done
		MCClass* iterator = this->isa;
		while(iterator != nil){
			_FunctionPointer(bye_method) = iterator->method_list[_hash("bye")];
			if(bye_method!=nil) (*bye_method)(this, nil);
			iterator = iterator->super;
		}

		//destory the obj
		runtime_log("----Destroy: goodbye!\n");
		this->isa = nil;//unlink to the class
		mc_free(this);
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

	if (this->ref_count == REFCOUNT_NO_MM)
	{
		debug_log("ref_count is -1 manage by runtime. do nothing\n");
		pthread_mutex_unlock(&_mc_mm_mutex);
		return;
	}

	if (this->ref_count == REFCOUNT_ANONY_OBJ)
	{
		//for anony object
		_pop_anony_obj(this);
		this->ref_count = 0;
	}

	this->ref_count++;
	runtime_log("%s - ref_count:%d\n", this->isa->name, this->ref_count);
	pthread_mutex_unlock(&_mc_mm_mutex);
}

void _relnil(MCObject** const this)
{
	release(*this);
	(*this) = nil;
}

unsigned _binding(id const self, unsigned hashkey, _FunctionPointer(value))
{
	pthread_mutex_lock(&_mc_runtime_mutex);
	_nil_check(self,
		"binding(sign, obj, key, ...)",
		"obj is nil, the key is:",
		"",
		"binding(sign, obj, key, ...)",
		"obj have no class object linked. please call set_class(). the key is:",
		"", &_mc_runtime_mutex);

	//unsigned hashkey = _hash(key);
	if(self->isa->method_list[hashkey] != nil){
		error_log("%s(%d):\n%s\n%s\n%s\n",
			self->isa->name, hashkey,
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
	
	//_prepare_ffi_call(count, types, self->isa, hashkey, value);
	self->isa->method_list[hashkey]=value;
	self->isa->method_count++;
	//runtime_log("add a method, hash index:%d\n", hashkey);
	pthread_mutex_unlock(&_mc_runtime_mutex);
	return hashkey;
}

unsigned _override(id const self, unsigned hashkey, _FunctionPointer(value))
{
	pthread_mutex_lock(&_mc_runtime_mutex);
	_nil_check(self,
		"override(obj, key, MA)",
		"obj is nil, the key is:",
		"",
		"override(obj, key, MA)",
		"obj have no class object linked. please call setting_start(). the key is:",
		"", &_mc_runtime_mutex);

	if(self->isa->method_count > MAX_METHOD_NUM-1){
		error_log("method index out of bound\n");
		pthread_mutex_unlock(&_mc_runtime_mutex);
		exit(-1);
	}

	//_prepare_ffi_call(count, types, self->isa, hashkey, value);
	self->isa->method_list[hashkey]=value;
	self->isa->method_count++;
	//runtime_log("add a method, hash index:%d\n",hashkey);
	pthread_mutex_unlock(&_mc_runtime_mutex);
	return hashkey;
}

BOOL _response(id const obj, unsigned hashkey)
{
	pthread_mutex_lock(&_mc_runtime_mutex);
	_nil_check(obj,
		"response(obj, key)",
		"obj is nil, the key is:",
		"",
		"response(obj, key)",
		"obj have no class object linked. please call set_class(). the key is:",
		"", &_mc_runtime_mutex);

	MCClass* cls_iterator = obj->isa;
	unsigned res;
	while((res=_response_to_method(cls_iterator, hashkey))==NOT_RESPONSE){
		if(cls_iterator != nil){
			cls_iterator = cls_iterator->super;
			//runtime_log("continue to my super\n");
		}else{
			debug_log("%s can not response method[%d]\n", obj->isa->name, hashkey);
			pthread_mutex_unlock(&_mc_runtime_mutex);
			return NO;
		}
	}

	pthread_mutex_unlock(&_mc_runtime_mutex);
	return YES;
}

/* copy form << The C Programming language >> */
unsigned _hash(const char *s)
{
	//runtime_log("hash(%s) --- ", s);
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % MAX_METHOD_NUM;
}

//class obj hash
unsigned _chash(const char *s)
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
	if(self == nil){
		error_log("%s:\n%s\n%s\n", log1, log2, log3);
		if(lock != nil)pthread_mutex_unlock(lock);
		exit(-1);
	}
	if(self->isa == nil){
		error_log("%s:\n%s\n%s\n", log4, log5, log6);
		if(lock != nil)pthread_mutex_unlock(lock);
		exit(-1);
	}
}

static inline void _clear_method_list(MCClass* const class)
{
	int i;
	for (i = 0; i < MAX_METHOD_NUM; i++){
		class->method_list[i] = nil;
	}
}

static void _init_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; i++){
		mc_classobj_pool[i] = nil;
	}

	load_root_class();
}

static void _clear_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; i++){
		MCClass* tmp = mc_classobj_pool[i];
		if(tmp!=nil)mc_free(tmp);
	}
}

static inline unsigned _response_to_method(MCClass* const cls, unsigned hashkey)
{
	if(cls == nil) return NOT_RESPONSE;
	if((cls->method_list != nil)
	&&(cls->method_list[hashkey] == nil)){
		return NOT_RESPONSE;
	}
	else{
		return hashkey;
	}
}

pthread_mutex_t _mc_alloc_mutex = PTHREAD_MUTEX_INITIALIZER;
void* mc_malloc(size_t size)
{
	pthread_mutex_lock(&_mc_alloc_mutex);
		void* ret = malloc(size);
		((MCObject*)ret)->ref_count = 1;
	pthread_mutex_unlock(&_mc_alloc_mutex);
	return ret;
}

void* mc_malloc_anony(size_t size)
{
	pthread_mutex_lock(&_mc_alloc_mutex);
		void* ret = malloc(size);
		((MCObject*)ret)->ref_count = REFCOUNT_ANONY_OBJ;
		_push_anony_obj((MCObject*)ret);
	pthread_mutex_unlock(&_mc_alloc_mutex);
	return ret;
}

void* mc_calloc(size_t size)
{
	pthread_mutex_lock(&_mc_alloc_mutex);
		void* ret = calloc(1, size);
		((MCObject*)ret)->ref_count = 1;
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

/*
alternative allocators in APUE
1. libmalloc
2. vmalloc
3. quick-fit
4. alloca ---> can alloc mem on stack
*/

void* _resolve_method(id const obj, const unsigned hashkey)
{
	_nil_check(obj,
		"ff(obj, key, ...)",
		"obj is nil, the key is:",
		"",
		"ff(obj, key, ...)",
		"obj have no class object linked. please call set_class(). the key is:",
		"", nil);

	MCClass* cls_iterator = obj->isa;
	unsigned res;
	int count = 0;
	while((res=_response_to_method(cls_iterator, hashkey))==NOT_RESPONSE){
		if(cls_iterator != nil){
			cls_iterator = cls_iterator->super;
			//runtime_log("%s\n", "continue to my super");
		}else if(count++ >= MAX_CLASS_NUM){
			error_log("class count overflow\n");
			return nil;
		}else{
			error_log("[%s] have no method: [%d] reach the root class return\n", obj->isa->name, hashkey);
			return nil;
		}
	}
	//new cache logic. only do cache when there are no such method in child.
	pthread_mutex_lock(&_mc_runtime_mutex);
	if((res < MAX_METHOD_NUM) && (obj->isa->method_list[res] == nil)){
		runtime_log("----Cache method: %s[%d]\n", obj->isa->name, hashkey);
		obj->isa->method_list[res] = cls_iterator->method_list[res];
	}
	pthread_mutex_unlock(&_mc_runtime_mutex);
	runtime_log("----Call method: %s[%d]\n", obj->isa->name, hashkey);
	
	return cls_iterator->method_list[res];
}

static char log_buf[1024];
void error_log(char* fmt, ...)
{
	if(LOG_LEVEL != SILENT){
		printf(LOG_FMT, LOG_COLOR_RED, "[Error] - ");
		va_list ap;
		va_start(ap, fmt);
			vsprintf(log_buf, fmt, ap);
			printf("%s", log_buf);
		va_end(ap);
	}
}

void debug_log(char* fmt, ...)
{
	if(LOG_LEVEL != SILENT
	 &&LOG_LEVEL != ERROR_ONLY){
		printf(LOG_FMT, LOG_COLOR_LIGHT_BLUE, "[Debug] - ");
		va_list ap;
		va_start(ap, fmt);
			vsprintf(log_buf, fmt, ap);
			printf("%s", log_buf);
		va_end(ap);
	}
}

void runtime_log(char* fmt, ...)
{
	if(LOG_LEVEL != SILENT
	 &&LOG_LEVEL != ERROR_ONLY
	 &&LOG_LEVEL != DEBUG){
		printf(LOG_FMT, LOG_COLOR_DARK_GRAY, "[RTime] - ");
		va_list ap;
		va_start(ap, fmt);
			vsprintf(log_buf, fmt, ap);
			printf("%s", log_buf);
		va_end(ap);
	}
}

void error_logt(char* tag, char* fmt, ...)
{
	if(LOG_LEVEL != SILENT){
		printf(LOG_FMT, LOG_COLOR_RED, "[Error] - ");
		printf(LOG_FMT, LOG_COLOR_DARK_GRAY, tag);

		va_list ap;
		va_start(ap, fmt);
			vsprintf(log_buf, fmt, ap);
			printf("%s", log_buf);
		va_end(ap);
	}
}

void debug_logt(char* tag, char* fmt, ...)
{
	if(LOG_LEVEL != SILENT
	 &&LOG_LEVEL != ERROR_ONLY){
		printf(LOG_FMT, LOG_COLOR_LIGHT_BLUE, "[Debug] - ");
		printf(LOG_FMT, LOG_COLOR_DARK_GRAY, tag);

		va_list ap;
		va_start(ap, fmt);
			vsprintf(log_buf, fmt, ap);
			printf("%s", log_buf);
		va_end(ap);
	}
}

void runtime_logt(char* tag, char* fmt, ...)
{
	if(LOG_LEVEL != SILENT
	 &&LOG_LEVEL != ERROR_ONLY
	 &&LOG_LEVEL != DEBUG){
		printf(LOG_FMT, LOG_COLOR_DARK_GRAY, "[RTime] - ");
		printf(LOG_FMT, LOG_COLOR_DARK_GRAY, tag);

		va_list ap;
		va_start(ap, fmt);
			vsprintf(log_buf, fmt, ap);
			printf("%s", log_buf);
		va_end(ap);
	}
}