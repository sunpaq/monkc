#include <string.h>
#include "MCContext.h"

#ifndef _MCString
#define _MCString _MCObject;\
	String str;

class(MCString);
method(MCString, print, xxx);
method(MCString, getOneChar, xxx);
method(MCString, getCharsUntilEnter, char const resultString[]);
constructor(MCString, String str);

char get_one_char();
void get_chars_until_enter(char resultString[]);

#endif