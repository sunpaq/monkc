#ifndef __VTable__
#define __VTable__
#include "MCRuntime.h"
#include "VTableSuper.h"

MCInterface(VTable, VTableSuper);
	int a;
	int b;
	int c;
#define VAR
#include "DrawableProtocol.h"
MCInterfaceEnd(VTable, init, xxx);

method(VTable, amethod, xxx);
method(VTable, bmethod, int a, double b, char* c);
method(VTable, cmethod, int a, double b, char* c);
method(VTable, bye, xxx);

#define METHOD
#include "DrawableProtocol.h"
#endif