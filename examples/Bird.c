#include "Bird.h"

constructor(Bird, int type)
{
	link_class(Bird, MCObject, nil)
	{
		have_method(Bird, bye, xxx);
		have_method(Bird, fly, xxx);
	}

	//override
	if(type==DUCK_TYPE){
		this->name="Bird:Duck";
		override(this, MK(fly), MV(Duck, fly));
	}else if(type==CHICKEN_TYPE){
		this->name="Bird:Chicken";
		override(this, MK(fly), MV(Chicken, fly));
	}else if(type==NONE){
		override(this, MK(fly), MV(Bird, fly));
	}
	//var init
	this->type=type;

	return this;
}

method(Bird, bye, xxx)
{
	//debug_log("%s\n", "Bird: goodbye");
}
method(Bird, fly, xxx)
{
	debug_log("%s\n", "Bird: default fly");
}
moption(Bird, Duck, fly, xxx)
{
	debug_log("%s\n", "Bird:Duck GuaGuaGua fly");
}
moption(Bird, Chicken, fly, xxx)
{
	debug_log("%s\n", "Bird:Chicken JiJiJi fly");
}


