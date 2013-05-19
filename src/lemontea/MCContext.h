#include "MCRuntime.h"
#include "string.h"

#ifndef MCContext_
#define MCContext_

class(MCContext);
	int argc;
	char** argv;
	char selectionChar;
end(MCContext);

method(MCContext, newWithArgs, int argc, char** argv)					returns(MCContext*);
method(MCContext, bye, xxx);
method(MCContext, dumpParas, xxx);
method(MCContext, getPara, int index) 									returns(char*);
method(MCContext, isIndexedParaEqualTo, int index, char* para) 			returns(BOOL);
method(MCContext, isHavePara, char* para) returns(BOOL);
method(MCContext, showMenuAndGetSelectionChar, int count, ...) 			returns(char);
method(MCContext, showConfirmAndGetBOOL, const char* confirm) 			returns(BOOL);
method(MCContext, getUserInputString, char resultString[]);

method(MCContext, getEnvironmentVar, const char* key) returns(char*);
method(MCContext, setEnvironmentVar, const char* key, const char* value, BOOL isOverwrite) returns(RES);
method(MCContext, clearEnvironmentVar, const char* key) returns(RES);

extern char **environ;

#endif

/*
#include <stdlib.h>
char *getenv(const char *name);
int putenv(char *str); //need "key=value"
int setenv(const char *name, const char *value, int rewrite);
int unsetenv(const char *name);
*/

