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
	debug_logt(this->isa->name, "my father age is: %d\n", cast(BirdFather, this->super)->age);
}

method(Bird, fly, xxx)
{
	debug_log("Bird[%p->%p]: default fly type %d\n", this, this->super, this->type);
	funcA(this, 100);
}

//
method(Bird, fly1, xxx){}
method(Bird, fly2, xxx){}
method(Bird, fly3, xxx){}
method(Bird, fly4, xxx){}
method(Bird, fly5, xxx){}
method(Bird, fly6, xxx){}
method(Bird, fly7, xxx){}
method(Bird, fly8, xxx){}
method(Bird, fly9, xxx){}
method(Bird, fly10, xxx){}
method(Bird, fly11, xxx){}
method(Bird, fly12, xxx){}
method(Bird, fly13, xxx){}
method(Bird, fly14, xxx){}
method(Bird, fly15, xxx){}
method(Bird, fly16, xxx){}
method(Bird, fly17, xxx){}
method(Bird, fly18, xxx){}
method(Bird, fly19, xxx){}
method(Bird, fly20, xxx){}
method(Bird, fly21, xxx){}
method(Bird, fly22, xxx){}
method(Bird, fly23, xxx){}
method(Bird, fly24, xxx){}
method(Bird, fly25, xxx){}
method(Bird, fly26, xxx){}
method(Bird, fly27, xxx){}
method(Bird, fly28, xxx){}
method(Bird, fly29, xxx){}
method(Bird, fly30, xxx){}
method(Bird, fly31, xxx){}
method(Bird, fly32, xxx){}
method(Bird, fly33, xxx){}
method(Bird, fly34, xxx){}
method(Bird, fly35, xxx){}
method(Bird, fly36, xxx){}
method(Bird, fly37, xxx){}
method(Bird, fly38, xxx){}
method(Bird, fly39, xxx){}
method(Bird, fly40, xxx){}
method(Bird, fly41, xxx){}
method(Bird, fly42, xxx){}
method(Bird, fly43, xxx){}
method(Bird, fly44, xxx){}
method(Bird, fly45, xxx){}
method(Bird, fly46, xxx){}
method(Bird, fly47, xxx){}
method(Bird, fly48, xxx){}
method(Bird, fly49, xxx){}
method(Bird, fly50, xxx){}



loader(Bird)
{
	debug_logt(class->name, "load called\n");
	#include "Flyable.p"

	binding(Bird, initWithType, int type);
	binding(Bird, bye, xxx);
	binding(Bird, bye, xxx);
	binding(Bird, fly, xxx);
	binding(Bird, fatherAge, xxx);

	binding(Bird, fly1, xxx);
	binding(Bird, fly2, xxx);
	binding(Bird, fly3, xxx);
	binding(Bird, fly4, xxx);
	binding(Bird, fly5, xxx);
	binding(Bird, fly6, xxx);
	binding(Bird, fly7, xxx);
	binding(Bird, fly8, xxx);
	binding(Bird, fly9, xxx);
	binding(Bird, fly10, xxx);
	binding(Bird, fly11, xxx);
	binding(Bird, fly12, xxx);
	binding(Bird, fly13, xxx);
	binding(Bird, fly14, xxx);
	binding(Bird, fly15, xxx);
	binding(Bird, fly16, xxx);
	binding(Bird, fly17, xxx);
	binding(Bird, fly18, xxx);
	binding(Bird, fly19, xxx);
	binding(Bird, fly20, xxx);
	binding(Bird, fly21, xxx);
	binding(Bird, fly22, xxx);
	binding(Bird, fly23, xxx);
	binding(Bird, fly24, xxx);
	binding(Bird, fly25, xxx);
	binding(Bird, fly26, xxx);
	binding(Bird, fly27, xxx);
	binding(Bird, fly28, xxx);
	binding(Bird, fly29, xxx);
	binding(Bird, fly30, xxx);
	binding(Bird, fly31, xxx);
	binding(Bird, fly32, xxx);
	binding(Bird, fly33, xxx);
	binding(Bird, fly34, xxx);
	binding(Bird, fly35, xxx);
	binding(Bird, fly36, xxx);
	binding(Bird, fly37, xxx);
	binding(Bird, fly38, xxx);
	binding(Bird, fly39, xxx);
	binding(Bird, fly40, xxx);
	binding(Bird, fly41, xxx);
	binding(Bird, fly42, xxx);
	binding(Bird, fly43, xxx);
	binding(Bird, fly44, xxx);
	binding(Bird, fly45, xxx);
	binding(Bird, fly46, xxx);
	binding(Bird, fly47, xxx);
	binding(Bird, fly48, xxx);
	binding(Bird, fly49, xxx);
	binding(Bird, fly50, xxx);
}


