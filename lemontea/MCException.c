#include "MCException.h"

//init define
jmp_buf exception_env = {};
volatile int exception_type = __exception_try_not_called;

static int _exception_list[MAX_EXCEPTION_NUM];
static mo _exception_store[MAX_EXCEPTION_NUM];

void clean_exception_context()
{
	//void *memset(void *s, int c, size_t n);
	memset(cast(void*, &exception_env), 0, sizeof(jmp_buf));
	exception_type = __exception_try_not_called;
	//clear list
	int i;
	for (i = 0; i < MAX_EXCEPTION_NUM; i++){
		_exception_list[i] = 0;
		_exception_store[i] = mull;
	}
	//init the system builtin exceptions here
}

/* copy form << The C Programming language >> */
static inline unsigned _ehash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return (hashval % MAX_EXCEPTION_NUM);
}

static unsigned _define_exception(char* s)
{
	unsigned val = _ehash(s);
	if(_exception_list[val] == 1){
		error_log("your exception name:%s is conflicted please change another name\n", s);
		exit(-1);
	}
	_exception_list[val] = 1;
	return val;
}

unsigned __get_exception_code(char* s)
{
	unsigned val = _ehash(s);
	if (_exception_list[val] == 1){
		return (unsigned)val;
	}
	else{
		return (unsigned)_define_exception(s);
	}
}

mo get_exception_data(char* key)
{
	unsigned val = _ehash(key);
	if (_exception_list[val] == 0)
	{
		error_log("there is no exception: %s. return nil\n", key);
		return mull;
	}
	mo res = _exception_store[val];
	return res;
}

void set_exception_data(char* key, mo e)
{
	unsigned val = _ehash(key);
	//e->ref_count = -1;//memery manage here

	mo exp_obj = _exception_store[val];
	if(exp_obj != mull){
		release(&exp_obj);

	}//auto release the old one
	_exception_store[val] = e;
}
