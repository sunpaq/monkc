#include "MCRuntime.h"
#include "string.h"

#ifndef _MCContext
#define _MCContext _MCObject;\
	int argc;\
	char** argv;\
	char selectionChar;\

class(MCContext);

method(MCContext, bye, xxx);
method(MCContext, dumpParas, xxx);
method(MCContext, getPara, int index) 									returns(char*);
method(MCContext, isIndexedParaEqualTo, int index, char* para) 			returns(BOOL);
method(MCContext, isHavePara, char* para) returns(BOOL);
method(MCContext, showMenuAndGetSelectionChar, int count, ...) 			returns(char);
method(MCContext, showConfirmAndGetBOOL, const char* confirm) 			returns(BOOL);
method(MCContext, getUserInputString, char resultString[]);

constructor(MCContext, int argc, char** argv);

#endif
