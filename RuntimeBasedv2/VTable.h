#ifndef __VTable__
#define __VTable__
#include "MCContext.h"
#include "VTableSuper.h"

#define VTable_field VTableSuper_field\
	double d;\
	Float e;\

MCInterface(VTable, VTableSuper);
	//copy the super vars here!
	
	//my vars
	VTable_field
#define VAR
#include "DrawableProtocol.h"
MCInterfaceEnd(VTable, init, xxx);
method(VTable, bye, xxx);

method(VTable, amethod, xxx);
method(VTable, bmethod, int a, double b, char* c);
method(VTable, cmethod, int a, double b, char* c);

#define METHOD
#include "DrawableProtocol.h"
#endif