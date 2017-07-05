#include "MCContext.h"
#include <setjmp.h>
#include <string.h>

#ifndef _MCException
#define _MCException

#define __exception_try_not_called -1
extern jmp_buf exception_env;
extern volatile int exception_type;
void clean_exception_context(void);

#define __MCNoneException 0
#define __ECODE(name) __get_exception_code(#name)
unsigned __get_exception_code(char* key);

/* public API */

#define throws(etype)
#define throw(etype)  if(exception_type!=__exception_try_not_called)_longjmp(exception_env, __ECODE(etype))

#define try           clean_exception_context();if((exception_type = _setjmp(exception_env))==__MCNoneException)
#define catch(etype)  else if(exception_type==__ECODE(etype))
#define finally       if(exception_type!=__MCNoneException)

//512+256+...1
#define MAX_EXCEPTION_NUM 0x000001ff

MCObject* get_exception_data(char* key);
void      set_exception_data(char* key, MCObject* e);

#endif

/*
this is a wrapper of setjmp.h
to support exception handling

"goto" can only jump inside a function
but _longjmp can jump between functions

longjmp: restore signal...
_longjmp: did not restore signal

longjmp will return the PC
to the line above setjmp, and setjmp will return the value longjmp have passed
*/
