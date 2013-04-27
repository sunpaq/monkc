#include "Bird_Engle.h"

//Engle Mode

method(Bird, engleFly, xxx)
{
	shift_back(this);
		ff(this, fly, nil);
	shift(this, Bird_Engle);

	debug_logt(this->isa->name, " engleFly gagaga\n");
}

method(Bird, engleFight, xxx)
{
	debug_logt(this->isa->name, " engleFight dadada\n");
}

method(Bird, engleEat, xxx)
{
	debug_logt(this->isa->name, " engleEat ...\n");
}

method(Bird, engleFatherAge, xxx)
{
	debug_logt(this->isa->name, " my father age is: %d\n", Cast(BirdFather, this->super)->age);
}

loader(Bird_Engle)
{
	debug_logt(class->name, "load called\n");
	binding(Bird, engleFly, xxx);
	binding(Bird, engleFight, xxx);
	binding(Bird, engleEat, xxx);
	binding(Bird, engleFatherAge, xxx);
}