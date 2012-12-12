#include "MCContext.h"
#include "VTableSuper.h"

#ifndef _VTable
#define _VTable _VTableSuper;\
	double d;\
	Float e;\

constructor(VTable, xxx);

method(VTable, bye, xxx);
method(VTable, amethod, xxx);
method(VTable, amethod2, char* srt, int index);

method(VTable, bmethod, int a, double b, char* c);
method(VTable, cmethod, int a, double b, char* c);

#define METHOD
#include "DrawableProtocol.h"
#endif