#include "MCContext.h"
#include "VTableSuper.h"

#ifndef _VTable 
#define _VTable _VTableSuper;\
	double d;\
	double e;\

class_begin(VTable);
	int a;
	int b;
	int c;
class_end(VTable);

constructor(VTable, xxx);
method(VTable, bye, xxx);
method(VTable, amethod, xxx) 							returns(int);
method(VTable, amethod2, char* srt, int index);
method(VTable, bmethod, int a, vector b, char* c);
method(VTable, cmethod, int a, vector b, char* c);

VTable* VTable_getInstance();
void VTable_releaseInstance();

#define METHOD
#include "DrawableProtocol.h"
#endif