#include "BirdGrandFather.h"

initer(BirdGrandFather)
{
	obj->super = nil;
	obj->age = 50;
	debug_logt(nameof((mo)obj), "[%p] init called\n", obj);
	return obj;
}

method(BirdGrandFather, void, bye, xxx)
{
	debug_logt(nameof((mo)obj), "[%p] bye called\n", obj);
}

method(BirdGrandFather, void, flyhigh, xxx)
{
	debug_logt(nameof((mo)obj), "i fly very high\n");
}

method(BirdGrandFather, void, fly, xxx)
{
	debug_logt(nameof((mo)obj), "i fly\n");
}

method(BirdGrandFather, void, singAsong, char* asong)
{
	debug_logt(nameof((mo)obj), "lalala: %s\n", asong);
}

loader(BirdGrandFather)
{
	binding(BirdGrandFather, void, bye, xxx);
	binding(BirdGrandFather, void, flyhigh, xxx);
	binding(BirdGrandFather, void, fly, xxx);
	binding(BirdGrandFather, void, singAsong, char* asong);
	debug_logt(nameofc(claz), "load called\n");
	return claz;
}