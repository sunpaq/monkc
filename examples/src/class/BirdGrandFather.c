#include "BirdGrandFather.h"

initer(BirdGrandFather)
{
	this->super = nil;
	this->age = 50;
	debug_logt(nameof(this), "[%p] init called\n", this);
	return this;
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
	binding(BirdGrandFather, void, bye, xxx);
	binding(BirdGrandFather, void, flyhigh, xxx);
	binding(BirdGrandFather, void, fly, xxx);
	binding(BirdGrandFather, void, singAsong, char* asong);
	debug_logt(nameofc(class), "load called\n");
	return class;
}