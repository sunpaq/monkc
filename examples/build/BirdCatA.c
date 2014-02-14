#include "BirdCatA.h"

initer(BirdCatA)
{
	//change something here
	return obj;
}

method(Bird, void, catmethodA, xxx)
{
	debug_logt(nameof((mo)obj), "BirdCatA - catmethodA\n");
}

method(Bird, void, catmethodB, xxx)
{
	debug_logt(nameof((mo)obj), "BirdCatA - catmethodB\n");
}

method(Bird, void, catmethodC, xxx)
{
	debug_logt(nameof((mo)obj), "BirdCatA - catmethodC\n");
}

method(Bird, void, catmethodD, xxx)
{
	debug_logt(nameof((mo)obj), "BirdCatA - catmethodD\n");
}

loader(BirdCatA)
{
	debug_logt(nameofc(claz), "BirdCatA - loader called\n");
	hinding(Bird, void, catmethodA, 4048645866, xxx);
	hinding(Bird, void, catmethodB, 4048645867, xxx);
	hinding(Bird, void, catmethodC, 4048645868, xxx);
	hinding(Bird, void, catmethodD, 4048645869, xxx);
	return claz;
}
