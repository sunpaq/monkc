#ifndef __Menifest__
#define __Menifest__
#include "OOP_MACROS.h"

Interface 
	#include "Base.i"
InterfaceEnd(Base,xxx)

Interface
	#include "Base.i"
	#include "ClassA.i"
	Base* base_handler;
InterfaceEnd(ClassA,xxx)

#endif
