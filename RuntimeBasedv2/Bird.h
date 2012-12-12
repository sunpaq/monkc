#include "MCContext.h"

#ifndef _Bird
#define _Bird _MCObject;\
	char* name;\
	int type;\

constructor(Bird, int type);

method(Bird, bye, xxx);
method(Bird, fly, xxx);

#define DUCK_TYPE 0
#define CHICKEN_TYPE 1
#define NONE 2

#endif