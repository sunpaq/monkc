#ifndef __Bird__
#define __Bird__
#include "MCContext.h"

MCInterface(Bird, root);
	char* name;
	int type;
MCInterfaceEnd(Bird, init, int type);
method(Bird, bye, xxx);
method(Bird, fly, xxx);
method(Duck, fly, xxx);
method(Chicken, fly, xxx);

#define DUCK_TYPE 0
#define CHICKEN_TYPE 1
#define NONE 2

#endif