#include <string.h>
#include "MCContext.h"

#ifndef MCString_
#define MCString_

monkc(MCString);
	size_t length;
	size_t size; 
	char* buff;
end(MCString);

//length not include '\0'
//real size, include '\0'
//C89: char buff[1]
//C99: char buff[]
//the new "flexiable array" in C99 is actually useable in C89 code, just change your array size to 1

method(MCString, MCString*, initWithCString, char* str);
method(MCString, void, add, char* str);
method(MCString, void, print, xxx);
method(MCString, const char*, toCString, char const buff[]);
method(MCString, int, equalTo, MCString* stringToComp);
method(MCString, char, getOneChar, xxx);
method(MCString, void, getCharsUntilEnter, char resultString[]);
method(MCString, void, bye, xxx);

MCString* MCString_newWithCString(char* cstr);
MCString* MCString_newWithMCString(MCString* mcstr);
MCString* MCString_newForHttp(char* cstr, int isHttps);

#endif



