#include "Bird.h"

constructor(Bird, int type)
{
	link_class(Bird, MCObject, nil)
	{
		binding(Bird, bye, xxx);
		binding(Bird, fly, xxx);

	}

	//override
	if(type==DUCK_TYPE){
		this->name="Bird:Duck";
		override(Duck, fly, xxx);
	}else if(type==CHICKEN_TYPE){
		this->name="Bird:Chicken";
		override(Chicken, fly, xxx);
	}else if(type==NONE){
		override(Bird, fly, xxx);
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


