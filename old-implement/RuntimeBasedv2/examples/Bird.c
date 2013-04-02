#include "Bird.h"

constructor(Bird, int type)
{
	link_class(Bird, MCObject, nil)
	{
		binding(MSNA, Bird, bye, xxx);
		binding(MSNA, Bird, fly, xxx);

	}

	//override
	if(type==DUCK_TYPE){
		this->name="Bird:Duck";
		override(MSNA, Duck, fly, xxx);
	}else if(type==CHICKEN_TYPE){
		this->name="Bird:Chicken";
		override(MSNA, Chicken, fly, xxx);
	}else if(type==NONE){
		override(MSNA, Bird, fly, xxx);
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


