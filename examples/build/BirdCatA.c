#include "BirdCatA.h"

initer(BirdCatA)
{
	//change something here
}

method(Bird, catmethodA, xxx)
{
	debug_logt(nameof(this), "BirdCatA - catmethodA\n");
}

method(Bird, catmethodB, xxx)
{
	debug_logt(nameof(this), "BirdCatA - catmethodB\n");
}

method(Bird, catmethodC, xxx)
{
	debug_logt(this->isa->item->key, "BirdCatA - catmethodC\n");
}

method(Bird, catmethodD, xxx)
{
	debug_logt(this->isa->item->key, "BirdCatA - catmethodD\n");
}

loader(BirdCatA)
{
	debug_logt(class->item->key, "BirdCatA - loader called\n");

	binding(Bird, catmethodA, xxx);
	binding(Bird, catmethodB, xxx);
	binding(Bird, catmethodC, xxx);
	binding(Bird, catmethodD, xxx);
}
