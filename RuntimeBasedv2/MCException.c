#include "MCException.h"

jmp_buf exception_env={};
int exception_type=__exception_try_not_called;

/* copy form << The C Programming language >> */
static inline unsigned _hash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % MAX_EXCEPTION_NUM;
}

static unsigned _exception_list[MAX_EXCEPTION_NUM];
static unsigned _exception_store[MAX_EXCEPTION_NUM];

//call this at the very begining
static BOOL isCleared=NO;
static void _clear_exception_list()
{
	if(isCleared==YES)return;
	int i;
	for (i = 0; i < MAX_EXCEPTION_NUM; ++i)
		_exception_list[i]=0;
		_exception_store[i]=nil;
	isCleared=YES;
	//init the system builtin exceptions here
}

static unsigned _define_exception(char* s)
{
	_clear_exception_list();

	unsigned val = _hash(s);
	if(_exception_list[val]==1){
		error_log("your exception name:%s is conflicted please change another name\n", s);
		exit(-1);
	}
	_exception_list[val]=1;
	return val;
}

unsigned __get_exception_code(char* s)
{
	unsigned val = _hash(s);
	if (_exception_list[val]==1)
		return (unsigned)val;
	else
		return (unsigned)_define_exception(s);
}

id get_exception_data(char* key)
{
	return _exception_store[_hash(key)];
}

void set_exception_data(char* key, id e)
{
	id exp_obj = _exception_store[_hash(key)];
	if(exp_obj!=nil)release(exp_obj);//auto release the old one
	_exception_store[_hash(key)]=e;
}
