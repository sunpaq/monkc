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
method(MCContext, getPara, int index);
method(MCContext, isIndexedParaEqualTo, int index, char* para);
method(MCContext, isHavePara, char* para);
method(MCContext, showMenuAndGetSelectionChar, int count, ...);
method(MCContext, showConfirmAndGetBOOL, const char* confirm);
method(MCContext, getUserInputString, char resultString[]);

constructor(MCContext, int argc, char** argv);

/*start your code in this function!*/
int MCContext_runloop(MCContext* const context);

#endif
