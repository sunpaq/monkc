#include "BirdFather.h"

initer(BirdFather)
{
	obj->super = new(BirdGrandFather);
	obj->age = 50;
	debug_logt(nameof(obj), "[%p] init called\n", obj);
	return obj;
}

method(BirdFather, void, bye, xxx)
{
	recycle(obj->super);
	debug_logt(nameof(obj), "[%p] bye called\n", obj);
}

method(BirdFather, void, flyhigh, xxx)
{
	debug_logt(nameof(obj), "i fly very high\n");
}

method(BirdFather, void, fly, xxx)
{
	debug_logt(nameof(obj), "i fly\n");
}

method(BirdFather, void, singAsong, char* asong)
{
	debug_logt(nameof(obj), "lalala: %s\n", asong);
}

loader(BirdFather)
{
	binding(BirdFather, void, bye, xxx);
	binding(BirdFather, void, flyhigh, xxx);
	binding(BirdFather, void, fly, xxx);
	binding(BirdFather, void, singAsong, char* asong);
	debug_logt(nameofc(claz), "load called\n");
	return claz;
}