#include "monkc.h"
#include "BirdGrandFather.h"

#ifndef BirdFather_
#define BirdFather_

class(BirdFather);
	int age;
end(BirdFather);

method(BirdFather, void, bye, xxx);
method(BirdFather, void, flyhigh, xxx);
method(BirdFather, void, fly, xxx);
method(BirdFather, void, singAsong, char* asong);

#endif