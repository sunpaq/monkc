#include "MCContext.h"
#include "VTableSuper.h"

#ifndef _VTable 
#define _VTable _VTableSuper;\
	double d;\
	Float e;\

class(VTable);
method(VTable, bye, xxx);
method(VTable, amethod, xxx) 							returns(int);
method(VTable, amethod2, char* srt, int index);
method(VTable, bmethod, int a, double b, char* c);
method(VTable, cmethod, int a, double b, char* c);
constructor(VTable, xxx);

Handle(VTable) VTable_getInstance();
void VTable_releaseInstance();

#define METHOD
#include "DrawableProtocol.h"
#endif