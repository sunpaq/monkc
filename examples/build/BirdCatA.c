#include "BirdCatA.h"

initer(BirdCatA)
{
	//change something here
}

method(Bird, void, catmethodA, xxx)
{
	debug_logt(nameof(this), "BirdCatA - catmethodA\n");
}

method(Bird, void, catmethodB, xxx)
{
	debug_logt(nameof(this), "BirdCatA - catmethodB\n");
}

method(Bird, void, catmethodC, xxx)
{
	debug_logt(nameof(this), "BirdCatA - catmethodC\n");
}

method(Bird, void, catmethodD, xxx)
{
	debug_logt(nameof(this), "BirdCatA - catmethodD\n");
}

loader(BirdCatA)
{
	debug_logt(nameofc(class), "BirdCatA - loader called\n");
	hinding(Bird, void, catmethodA, 4048645866, xxx);
	hinding(Bird, void, catmethodB, 4048645867, xxx);
	hinding(Bird, void, catmethodC, 4048645868, xxx);
	hinding(Bird, void, catmethodD, 4048645869, xxx);
}
