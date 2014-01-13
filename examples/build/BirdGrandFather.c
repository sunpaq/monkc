#include "BirdGrandFather.h"

initer(BirdGrandFather)
{
	this->super = nil;
	this->age = 50;
	debug_logt(nameof(this), "[%p] init called\n", this);
}

method(BirdGrandFather, void, bye, xxx)
{
	debug_logt(nameof(this), "[%p] bye called\n", this);
}

method(BirdGrandFather, void, flyhigh, xxx)
{
	debug_logt(nameof(this), "i fly very high\n");
}

method(BirdGrandFather, void, fly, xxx)
{
	debug_logt(nameof(this), "i fly\n");
}

method(BirdGrandFather, void, singAsong, char* asong)
{
	debug_logt(nameof(this), "lalala: %s\n", asong);
}

loader(BirdGrandFather)
{
hinding(BirdGrandFather, void, bye, 98030, xxx);
hinding(BirdGrandFather, void, flyhigh, 3537959061, xxx);
hinding(BirdGrandFather, void, fly, 101491, xxx);
binding(BirdGrandFather, void, singAsong, char* asong);
	debug_logt(nameofc(class), "load called\n");
}