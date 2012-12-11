#ifndef __MCContext__
#define __MCContext__
#include "MCRuntime.h"
#include "MCString.h"

MCInterface(MCContext, root);
	int argc;
	char** argv;
	char selectionChar;
MCInterfaceEnd(MCContext, init, int argc, char** argv);

method(MCContext, bye, xxx);
method(MCContext, dump, xxx);
method(MCContext, getPara, int index);
method(MCContext, paraEqual, int index, char* para);
method(MCContext, havePara, char* para);
method(MCContext, showMenuAndGetSelectionChar, int count, ...);
method(MCContext, showConfirmAndGetBOOL, const char* confirm);
method(MCContext, getUserInputString, char resultString[]);

int MCContext_runloop(MCContext* const context);

#endif
