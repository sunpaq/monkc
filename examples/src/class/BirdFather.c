#include "BirdFather.h"

initer(BirdFather)
{
	this->super = new(BirdGrandFather);
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
binding(BirdFather, void, bye, xxx);
binding(BirdFather, void, flyhigh, xxx);
binding(BirdFather, void, fly, xxx);
binding(BirdFather, void, singAsong, char* asong);
	debug_logt(nameofc(class), "load called\n");
}