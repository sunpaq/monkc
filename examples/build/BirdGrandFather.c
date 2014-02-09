#include "BirdGrandFather.h"

initer(BirdGrandFather)
{
	obj->super = nil;
	obj->age = 50;
	debug_logt(nameof(obj), "[%p] init called\n", obj);
	return obj;
}

method(BirdGrandFather, void, bye, xxx)
{
	debug_logt(nameof(obj), "[%p] bye called\n", obj);
}

method(BirdGrandFather, void, flyhigh, xxx)
{
	debug_logt(nameof(obj), "i fly very high\n");
}

method(BirdGrandFather, void, fly, xxx)
{
	debug_logt(nameof(obj), "i fly\n");
}

method(BirdGrandFather, void, singAsong, char* asong)
{
	debug_logt(nameof(obj), "lalala: %s\n", asong);
}

loader(BirdGrandFather)
{
	hinding(BirdGrandFather, void, bye, 98030, xxx);
	hinding(BirdGrandFather, void, flyhigh, 3537959061, xxx);
	hinding(BirdGrandFather, void, fly, 101491, xxx);
	binding(BirdGrandFather, void, singAsong, char* asong);
	debug_logt(nameofc(claz), "load called\n");
	return claz;
}