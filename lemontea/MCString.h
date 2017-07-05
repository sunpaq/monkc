#include <string.h>
#include "MCContext.h"
#include "MCLexer.h"

#ifndef MCString_
#define MCString_

class(MCString, MCObject,
	size_t length;
	size_t size;
    size_t cursor;
	char* buff;
)

//length not include NUL
//real size, include NUL include empty space in buffer

method(MCString, MCString*, initWithCString, const char* str);
method(MCString, void, add, char* str);
method(MCString, const char*, toCString, char const buff[]);
method(MCString, int, equalTo, MCString* stringToComp);
method(MCString, void, getCharsUntilEnter, char resultString[]);
method(MCString, char, getOneChar, voida);
method(MCString, void, print, MCBool withNewline);
method(MCString, void, bye, voida);
method(MCString, MCBool, startWith, const char* str);
method(MCString, double, toDoubleValue, char** endptr);
method(MCString, MCString*, copyCompressedString, voida);
method(MCString, MCString*, copyExtractedString, voida);

MCString* MCString_newWithCString(const char* cstr);
MCString* MCString_newWithMCString(MCString* mcstr);
MCString* MCString_newForHttp(char* cstr, int isHttps);

utility(MCString, MCBool, contains, const char* str, const char* instr);
utility(MCString, size_t, replace, const char* str, const char* withstr, const char* instr, char (*buff)[]);
utility(MCString, size_t, reverse, const char* str, char *buff);

utility(MCString, const char*, percentEncode, const char* str, char *buff);
utility(MCString, const char*, percentDecode, const char* str, char *buff);

utility(MCString, const char*, baseFromPath, const char* path, char (*buff)[]);
utility(MCString, const char*, filenameFromPath, const char* path, char (*buff)[]);

utility(MCString, size_t, extensionFromFilename, const char* name, char* basebuff, char* extbuff);

utility(MCString, const char*, concate, const char** strings, size_t count, char (*buff)[]);
utility(MCString, const char*, concateWith, const char* sp, const char* path1, const char* path2, char (*buff)[]);
utility(MCString, const char*, concatePath, const char* path1, const char* path2, char (*buff)[]);

utility(MCString, const char*, compressToCharCount, const char* source, char* buff);
utility(MCString, const char*, extractFromCharCount, const char* source, char* buff);

utility(MCString, void, printPermutationOf, char str[]);

MCInline char* MCStringFill(char* dest, const char* src) {
    char* res = strcpy(dest, src);
    dest[strlen(src)] = NUL;
    return res;
}

MCInline MCBool MCStringEqualN(const char* A, const char* B, size_t n) {
    if (strncmp(A, B, n) == 0) {
        return true;
    }else{
        return false;
    }
}

MCInline MCBool MCStringEqual(const char* A, const char* B) {
    if (strcmp(A, B) == 0) {
        return true;
    }else{
        return false;
    }
}

#endif



