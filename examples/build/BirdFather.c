#include "BirdFather.h"

initer(BirdFather)
{
	debug_logt(nameof(this), "[%p] init called\n", this);
	this->super = new(BirdGrandFather);
	this->age = 50;
}

method(BirdFather, bye, xxx)
{
	debug_logt(nameof(this), "[%p] bye called\n", this);
	release(&(this->super));
}

method(BirdFather, flyhigh, xxx)
{
	debug_logt(nameof(this), "i fly very high\n");
}

method(BirdFather, fly, xxx)
{
	debug_logt(nameof(this), "i fly\n");
}

method(BirdFather, singAsong, char* asong)
{
	debug_logt(nameof(this), "lalala: %s\n", asong);
}

loader(BirdFather)
{
	debug_logt(nameofc(class), "load called\n");
	binding(BirdFather, bye, xxx);
	binding(BirdFather, flyhigh, xxx);
	binding(BirdFather, fly, xxx);
	binding(BirdFather, singAsong, char* asong);
}