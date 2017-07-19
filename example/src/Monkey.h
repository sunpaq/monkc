#ifndef Monkey_
#define Monkey_

#include "monkc.h"

class(Monkey, MCObject,
	const char* name;
	MCInt age);

method(Monkey, void, info, voida);
method(Monkey, void, showname, voida);
method(Monkey, void, showage, voida);
//Flyable

#endif

