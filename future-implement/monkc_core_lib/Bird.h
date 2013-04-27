#include "MCRuntime.h"
#include "BirdFather.h"

#ifndef Bird_
#define Bird_

implements(Flyable);
extends(BirdFather);
class(Bird);
	char* name;
	int type;
end(Bird);

method(Bird, bye, xxx);
method(Bird, initWithType, int type);
method(Bird, fly, xxx);
method(Bird, fatherAge, xxx);

#endif
