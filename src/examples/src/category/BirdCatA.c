#include "BirdCatA.h"

catiniter(Bird, CatA)
{
	//change something here
}

method(Bird, catmethodA, xxx)
{
	debug_logt(this->isa->name, "BirdCatA - catmethodA\n");
}

method(Bird, catmethodB, xxx)
{
	debug_logt(this->isa->name, "BirdCatA - catmethodB\n");
}

method(Bird, catmethodC, xxx)
{
	debug_logt(this->isa->name, "BirdCatA - catmethodC\n");
}

method(Bird, catmethodD, xxx)
{
	debug_logt(this->isa->name, "BirdCatA - catmethodD\n");
}

catloader(Bird, CatA)
{
	binding(Bird, catmethodA, xxx);
	binding(Bird, catmethodB, xxx);
	binding(Bird, catmethodC, xxx);
	binding(Bird, catmethodD, xxx);
}
