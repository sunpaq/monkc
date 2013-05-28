#include "BirdGrandFather.h"

initer(BirdGrandFather)
{
	debug_logt(nameof(this), "[%p] init called\n", this);
	this->age = 50;
}

method(BirdGrandFather, bye, xxx)
{
	debug_logt(nameof(this), "[%p] bye called\n", this);
	
}

method(BirdGrandFather, flyhigh, xxx)
{
	debug_logt(nameof(this), "i fly very high\n");
}

method(BirdGrandFather, fly, xxx)
{
	debug_logt(nameof(this), "i fly\n");
}

method(BirdGrandFather, singAsong, char* asong)
{
	debug_logt(nameof(this), "lalala: %s\n", asong);
}

loader(BirdGrandFather)
{
	debug_logt(nameofc(class), "load called\n");
	binding(BirdGrandFather, bye, xxx);
	binding(BirdGrandFather, flyhigh, xxx);
	binding(BirdGrandFather, fly, xxx);
	binding(BirdGrandFather, singAsong, char* asong);
}