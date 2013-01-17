#include "Bird.h"

method(Bird, bye, xxx)
{
	//debug_log("%s\n", "Bird: goodbye");
}
method(Bird, fly, xxx)
{
	debug_log("%s\n", "Bird: default fly");
}
method(Bird, duck_fly, xxx)
{
	debug_log("%s\n", "Bird:Duck GuaGuaGua fly");
}
method(Bird, chicken_fly, xxx)
{
	debug_log("%s\n", "Bird:Chicken JiJiJi fly");
}

constructor(Bird, int type)
{
	super_init(this, MCObject, nil);
	//bind
	if(set_class(this, "Bird", "MCObject")){
		bind_method(this, MK(fly), MV(Bird, fly));
		bind_method(this, MK(bye), MV(Bird, bye));
	}
	//override
	if(type==DUCK_TYPE){
		this->name="Bird:Duck";
		override(this, MK(fly), MV(Bird, duck_fly));
	}else if(type==CHICKEN_TYPE){
		this->name="Bird:Chicken";
		override(this, MK(fly), MV(Bird, chicken_fly));
	}else if(type==NONE){
		override(this, MK(fly), MV(Bird, fly));
	}
	//var init
	this->type=type;

	return this;
}
