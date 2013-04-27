#include "Bird.h"

initer(Bird)
{
	this->super = new(BirdFather);
	this->type = 3;
	debug_logt("Bird", "[%p] init called\n", this);
}

method(Bird, bye, xxx)
{
	debug_logt(this->isa->name, "[%p] bye called\n", this);

	release(this->super);
}

void funcA(Bird* this, int arg1)
{
	debug_log("i am local function A\n");
}

protocol(Flyable, duckFly, xxx)
{
	debug_log("%s\n", "Bird:Duck GuaGuaGua fly");
}

protocol(Flyable, chickenFly, xxx)
{
	debug_log("%s\n", "Bird:Chicken JiJiJi fly");
}

method(Bird, initWithType, int type)
{
	this->type = type;
	return this;
}

method(Bird, fatherAge, xxx)
{
	debug_logt(this->isa->name, "my father age is: %d\n", Cast(BirdFather, this->super)->age);
}

method(Bird, fly, xxx)
{
	debug_log("Bird[%p->%p]: default fly type %d\n", this, this->super, this->type);
	funcA(this, 100);
}

loader(Bird)
{
	debug_logt(class->name, "load called\n");
	#include "Flyable.p"

	binding(Bird, initWithType, int type);
	binding(Bird, bye, xxx);
	binding(Bird, fly, xxx);
	binding(Bird, fatherAge, xxx);
}


