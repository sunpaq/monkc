#include "monkc.h"

#ifndef BirdGrandFather_ 
#define BirdGrandFather_

monkc(BirdGrandFather);
	int age;
end(BirdGrandFather);

method(BirdGrandFather, void, bye, xxx);
method(BirdGrandFather, void, flyhigh, xxx);
method(BirdGrandFather, void, fly, xxx);
method(BirdGrandFather, void, singAsong, char* asong);

#endif