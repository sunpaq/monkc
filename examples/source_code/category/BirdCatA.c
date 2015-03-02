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
	binding(Bird, void, catmethodA, xxx);
	binding(Bird, void, catmethodB, xxx);
	binding(Bird, void, catmethodC, xxx);
	binding(Bird, void, catmethodD, xxx);
	return claz;
}
