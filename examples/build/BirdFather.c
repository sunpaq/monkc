#include "BirdFather.h"

initer(BirdFather)
{
	this->super = hew(BirdGrandFather, 302479087);
	this->age = 50;
	debug_logt(nameof(this), "[%p] init called\n", this);
}

method(BirdFather, void, bye, xxx)
{
	recycle(this->super);
	debug_logt(nameof(this), "[%p] bye called\n", this);
}

method(BirdFather, void, flyhigh, xxx)
{
	debug_logt(nameof(this), "i fly very high\n");
}

method(BirdFather, void, fly, xxx)
{
	debug_logt(nameof(this), "i fly\n");
}

method(BirdFather, void, singAsong, char* asong)
{
	debug_logt(nameof(this), "lalala: %s\n", asong);
}

loader(BirdFather)
{
hinding(BirdFather, void, bye, 98030, xxx);
hinding(BirdFather, void, flyhigh, 3537959061, xxx);
hinding(BirdFather, void, fly, 101491, xxx);
binding(BirdFather, void, singAsong, char* asong);
	debug_logt(nameofc(class), "load called\n");
}