#include <string.h>
#include "MCContext.h"

#ifndef _MCString
#define _MCString _MCObject;\
	size_t length;\
	size_t size;\  
	id next;\
	char buff[1];\

//length not include '\0'
//real size, include '\0'

class(MCString);
method(MCString, add, CString str);
method(MCString, print, xxx);
method(MCString, toCString, char resultString[]);
method(MCString, equalTo, MCString* stringToComp) 							returns(BOOL);
method(MCString, getOneChar, xxx);
method(MCString, getCharsUntilEnter, char const resultString[]);
method(MCString, bye, xxx);
constructor(MCString, CString str);

MCString* MCString_newWithCString(char* cstr);
MCString* MCString_newWithMCString(MCString* mcstr);
MCString* MCString_newForHttp(char* cstr, BOOL isHttps);

char get_one_char();
void get_chars_until_enter(char resultString[]);

#endif