#include "BirdFather.h"

initer(BirdFather)
{
	debug_logt("BirdFather", "[%p] init called\n", this);
	this->super = new(BirdGrandFather);
	this->age = 50;
}

method(BirdFather, bye, xxx)
{
	debug_logt(this->isa->name, "[%p] bye called\n", this);
}

method(BirdFather, flyhigh, xxx)
{
	debug_logt(this->isa->name, "i fly very high\n");
}

method(BirdFather, fly, xxx)
{
	debug_logt(this->isa->name, "i fly\n");
}

method(BirdFather, singAsong, char* asong)
{
	debug_logt(this->isa->name, "lalala: %s\n", asong);
}

loader(BirdFather)
{
	debug_logt("BirdFather", "load called\n");
	binding(BirdFather, bye, xxx);
	binding(BirdFather, flyhigh, xxx);
	binding(BirdFather, fly, xxx);
	binding(BirdFather, singAsong, char* asong);
}