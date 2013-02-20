#ifndef __VTableSuper__
#define __VTableSuper__
#include "MCRuntime.h"

#define VTableSuper_field int a;\
	int b;\
	int c;\
	char* info;\

MCInterface(VTableSuper, root);
	VTableSuper_field
#define VAR
#include "DrawableProtocol.h"
MCInterfaceEnd(VTableSuper, init, xxx);
method(VTableSuper, bye, xxx);

method(VTableSuper, show, BOOL isPrint, char* str);
method(VTableSuper, bmethod, int a, double b, char* c);
method(VTableSuper, cmethod, int a, double b, char* c);

#define METHOD
#include "DrawableProtocol.h"
#endif