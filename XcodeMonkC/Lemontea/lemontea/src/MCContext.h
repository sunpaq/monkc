#include "monkc.h"
#include "string.h"

#ifndef MCContext_
#define MCContext_

monkc(MCContext);
	int argc;
	char** argv;
	char selectionChar;
end(MCContext);

method(MCContext, MCContext*, newWithArgs, int argc, char** argv);
method(MCContext, void, bye, xxx);
method(MCContext, void, dumpParas, xxx);
method(MCContext, char*, getPara, int index);
method(MCContext, int, isIndexedParaEqualTo, int index, char* para);
method(MCContext, int, isHavePara, char* para);
method(MCContext, char, showMenuAndGetSelectionChar, int count, ...);
method(MCContext, int, showConfirmAndGetBOOL, const char* confirm);
method(MCContext, void, getUserInputString, char resultString[]);
method(MCContext, char*, getEnvironmentVar, const char* key);
method(MCContext, int, setEnvironmentVar, const char* key, const char* value, int isOverwrite);
method(MCContext, int, clearEnvironmentVar, const char* key);

extern char **environ;

#endif

/*
#include <stdlib.h>
char *getenv(const char *name);
int putenv(char *str); //need "key=value"
int setenv(const char *name, const char *value, int rewrite);
int unsetenv(const char *name);
*/

