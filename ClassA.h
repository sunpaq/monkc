#ifndef __ClassA__
#define __ClassA__

#define CLASS ClassA
#include "OOP_MACROS.h"

Interface(ClassA)
	int i;
	int dcl(open)arg(tail);
	void dcl(onnew)arg(tail);
	void dcl(onbye)arg(tail);
IEnd(ClassA,tail)

#endif