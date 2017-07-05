#include <string.h>
#include "MCContext.h"

#ifndef MCString_
#define MCString_

class(MCString, MCObject,
	size_t length;
	size_t size;
    size_t cursor;
	char* buff;
)

//length not include '\0'
//real size, include '\0'

method(MCString, MCString*, initWithCString, const char* str);
method(MCString, void, add, char* str);
method(MCString, const char*, toCString, char const buff[]);
method(MCString, int, equalTo, MCString* stringToComp);
method(MCString, void, getCharsUntilEnter, char resultString[]);
method(MCString, char, getOneChar, voida);
method(MCString, void, print, voida);
method(MCString, void, bye, voida);
method(MCString, MCBool, startWith, const char* str);
method(MCString, double, getFloat, char** endptr);

MCString* MCString_newWithCString(const char* cstr);
MCString* MCString_newWithMCString(MCString* mcstr);
MCString* MCString_newForHttp(char* cstr, int isHttps);

utility(MCString, size_t, replace, const char* str, const char* withstr, const char* instr, char (*buff)[]);
utility(MCString, size_t, reverse, const char* str, char (*buff)[]);

utility(MCString, const char*, baseFromPath, const char* path, char (*buff)[]);
utility(MCString, const char*, filenameFromPath, const char* path, char (*buff)[]);

utility(MCString, const char*, filenameTrimExtension, const char* name, char (*buff)[]);
utility(MCString, const char*, extensionFromFilename, const char* name, char (*buff)[]);

utility(MCString, const char*, concate, const char** strings, size_t count, char (*buff)[]);
utility(MCString, const char*, concateWith, const char* sp, const char* path1, const char* path2, char (*buff)[]);
utility(MCString, const char*, concatePath, const char* path1, const char* path2, char (*buff)[]);

#endif



