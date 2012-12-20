#include "MCContext.h"

#ifndef _Bird
#define _Bird _MCObject;\
	char* name;\
	int type;\

class(Bird);
method(Bird, bye, xxx);
method(Bird, fly, xxx);
constructor(Bird, int type);

#define DUCK_TYPE 0
#define CHICKEN_TYPE 1
#define NONE 2

#endif
