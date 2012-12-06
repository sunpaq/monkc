#ifndef __MCContext__
#define __MCContext__
#include "MCRuntime.h"

MCInterface(MCContext, root);
	int argc;
	char** argv;
MCInterfaceEnd(MCContext, init, int argc, char** argv);

method(MCContext, bye, xxx);
method(MCContext, dump, xxx);
method(MCContext, getPara, int index);
method(MCContext, paraEqual, int index, char* para);
method(MCContext, havePara, char* para);

int MCContext_runloop(MCContext* const context);

#endif
