#ifndef __Node__
#define __Node__
#include "OOP_MACROS.h"

MCInterface(Node)
#include "RC.protocol"
	//String info;
	id data;
	struct Node_tag *next;
	struct Node_tag *prev;
MCInterfaceEnd(Node,id data)

#endif