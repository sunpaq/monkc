#include "MCRuntime.h"
#include "MCContext.h"
//default we set log level to debug
LOG_LEVEL = DEBUG;
//log colors
static char* LOG_FMT = "%s%s\033[0m";
static char* LOG_COLOR_NONE="\033[0m";
static char* LOG_COLOR_BLACK="\033[0;30m";
static char* LOG_COLOR_DARK_GRAY="\033[1;30m";
static char* LOG_COLOR_BLUE="\033[0;34m";
static char* LOG_COLOR_LIGHT_BLUE="\033[1;34m";
static char* LOG_COLOR_GREEN="\033[0;32m";
static char* LOG_COLOR_LIGHT_GREEN="\033[1;32m";
static char* LOG_COLOR_CYAN="\033[0;36m";
static char* LOG_COLOR_LIGHT_CYAN="\033[1;36m";
static char* LOG_COLOR_RED="\033[0;31m";
static char* LOG_COLOR_LIGHT_RED="\033[1;31m";
static char* LOG_COLOR_PURPLE="\033[0;35m";
static char* LOG_COLOR_LIGHT_PURPLE="\033[1;35m";
static char* LOG_COLOR_BROWN="\033[0;33m";
static char* LOG_COLOR_YELLOW="\033[1;33m";
static char* LOG_COLOR_LIGHT_GRAY="\033[0;37m";
static char* LOG_COLOR_WHITE="\033[1;37m";

//global var set in _init_class_list
static unsigned _init_method_hashkey;
static unsigned _hash(char *s);
static unsigned _classobj_hash(char *s);
static void _nil_check(MCObject* const self, 
	char* log1, char* log2, char* log3, 
	char* log4, char* log5, char* log6);
static void _clear_method_list(id const self_in);
static void _init_class_list();
static void _clear_class_list();
static MCClass* mc_classobj_pool[MAX_CLASS_NUM];
static const int NOT_RESPONSE = -1;
static int _response_to_method(id const self_in, char *key);
static void _destroy(id const instance);

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
		LOG_LEVEL = VERBOSE;
		New(MCContext, context, argc, argv);
		LOG_LEVEL = VERBOSE;
			int res = MCContext_runloop(context);
		release(context);
	_clear_class_list();
	return res;
}

id MCObject_init(void* const self, char* cmd, xxx)
{
	//do nothing
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

MCClass* load_class(const char* name_in, const char* super_class)
{
	//char* str;
	//error_color_log(str,"load class\n");

	int super_hashkey = _classobj_hash(super_class);
	if(super_hashkey>MAX_CLASS_NUM){
		error_log("%s hashkey is out of bound\n",super_class);
		exit(-1);
	}

	MCClass* superclass = mc_classobj_pool[super_hashkey];
	if(superclass==nil){
		error_log("there is no %s classobj.please load it first!\n", super_class);
		exit(-1);
	}

	MCClass* class = (MCClass*)malloc(sizeof(MCClass));

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
		error_log("class: %s - name hash value conflict.\nplease change a name\n", name_in);
		exit(-1);
	}
	mc_classobj_pool[hashkey]=class;
	return class;
}

MCClass* get_class(const char* name_in)
{
	int hashkey = _classobj_hash(name_in);
	return mc_classobj_pool[hashkey];
}

BOOL set_class(MCObject* const self_in, const char* classname, const char* superclassname)
{
	if (self_in==nil)
	{
		error_log("set_class(obj, classname).\nobj should not be nil");
		exit(-1);
	}
	runtime_log("set_class(obj, class:%s, super:%s)\n", classname ,superclassname);
	self_in->ref_count = 1;

	//load class
	MCClass* class;
	if((class=get_class(classname))!=nil){
		runtime_log("class: %s already loaded\n",classname);
		self_in->isa = class;
		return NO;
	}else{
		runtime_log("new load a class: %s\n", classname);
		class = load_class(classname, superclassname);
		self_in->isa = class;
		return YES;
	}
}

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
		ff(this, MK(bye), nil);
		_destroy(this);
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
		"please call set_class() at the very begin of init method.");

	this->ref_count++;
	runtime_log("%s - ref_count:%d\n", this->isa->name, this->ref_count);
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

	unsigned hashkey = _hash(key);
	if(self->isa->method_list[hashkey]!=0){
		error_log("%s_%s:\n%s\n%s\n",
			self->isa->name, key,
			"the method already binded, you should call override() instead.",
			"or your method name hash conflict with other method, change a name please");
		exit(-1);
	}

	if(self->isa->method_count > MAX_METHOD_NUM-1){
		error_log("method index out of bound\n");
		exit(-1);
	}
	self->isa->method_list[hashkey] = mptr;
	self->isa->method_count++;
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

	unsigned hashkey = _hash(key);
	if(self->isa->method_count > MAX_METHOD_NUM-1){
		error_log("method index out of bound\n");
		exit(-1);
	}
	self->isa->method_list[hashkey] = mptr;
	self->isa->method_count++;
	runtime_log("add a method, hash index:%d\n",hashkey);
	return hashkey;
}

BOOL response(id const self_in, char *key)
{
	MCObject* obj = (MCObject*)self_in;
	_nil_check(obj,
		"response(obj, key)",
		"obj is nil, the key is:",
		key,
		"response(obj, key)",
		"obj have no class object linked. please call setting_start(). the key is:",
		key);

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
				"no such method! are you forget to bind_method()? MC_call return");
			return NO;
		}
	}

	obj->isa = cls_save;
	return YES;
}

/* ff is short for [fire function] */
id ff(id const self_in, char *key, ...)
{
	MCObject* obj = (MCObject*)self_in;
	_nil_check(obj,
		"ff(obj, key, ...)",
		"obj is nil, the key is:",
		key,
		"ff(obj, key, ...)",
		"obj have no class object linked. please call set_class(). the key is:",
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
				"no such method! are you forget to bind()? MC_call return");
			return;
		}
	}

	obj->isa = cls_save;

	runtime_log("%s\n", "Call method");
	result = __builtin_apply(cls->method_list[res], args, 96);

	if((res < MAX_METHOD_NUM) && (cls_save->method_list[res]==0))
		cls_save->method_list[res]=cls->method_list[res];//new cache logic

	if(result)
		__builtin_return(result);
	else
		return;
}

/* copy form << The C Programming language >> */
static unsigned _hash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % MAX_METHOD_NUM;
}

static unsigned _classobj_hash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % MAX_CLASS_NUM;
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

static void _clear_method_list(id const self_in)
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

	MCClass* class = (MCClass*)malloc(sizeof(MCClass));
	class->name = ROOT_CLASS_NAME;
	class->super=nil;
	mc_classobj_pool[_classobj_hash(ROOT_CLASS_NAME)]=class;
	//for init method judgement
	_init_method_hashkey=_hash(INIT_METHOD_NAME);
}

static void _clear_class_list()
{
	int i;
	for (i = 0; i < MAX_CLASS_NUM; ++i){
		MCClass* tmp = mc_classobj_pool[i];
		if(tmp!=nil)free(tmp);
	}
}

static int _response_to_method(id const self_in, char *key)
{
	MCObject* self = (MCObject*)self_in;

	unsigned hashkey = _hash(key);
	if(self->isa->method_list[hashkey]==0)
		return NOT_RESPONSE;
	else
		return hashkey;
}

static void _destroy(id const instance)
{
	MCObject* this = (MCObject*) instance;
	_nil_check(this,
		"destroy(obj).",
		"obj is nil.",
		"please check your code.",
		"destroy(obj)",
		"obj have no class object linked.",
		"please call set_class() at the very begin of init method.");

	runtime_log("----Bye: %s goodbye!\n", this->isa->name);
	free(this);//free instance
}