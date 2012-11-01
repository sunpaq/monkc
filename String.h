#ifndef __String__
#define __String__
#include "OOP_MACROS.h"

MCInterface(String)
#include "RC.protocol"
	char* charseq;
	method(void, show, xxx);
	method(void, append, struct String_tag *str);
	method(bool, equal, struct String_tag *str);
MCInterfaceEnd(String, char* charseq_in)

#endif