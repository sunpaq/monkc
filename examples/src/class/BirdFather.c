#include "BirdFather.h"

initer(BirdFather)
{
	this->super = new(BirdGrandFather);
	this->age = 50;
	debug_logt(nameof(this), "[%p] init called\n", this);
}

method(BirdFather, bye, xxx)
{
	release(&(this->super));
	debug_logt(nameof(this), "[%p] bye called\n", this);
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
	binding(BirdFather, bye, xxx);
	binding(BirdFather, flyhigh, xxx);
	binding(BirdFather, fly, xxx);
	binding(BirdFather, singAsong, char* asong);
	debug_logt(nameofc(class), "load called\n");
}