#include "Bird.h"

method_imp(Bird, bye, xxx)
{
	//debug_log("%s\n", "Bird: goodbye");
}
method_imp(Bird, fly, xxx)
{
	debug_log("%s\n", "Bird: default fly");
}
method_imp(Duck, fly, xxx)
{
	debug_log("%s\n", "Bird:Duck GuaGuaGua fly");
}
method_imp(Chicken, fly, xxx)
{
	debug_log("%s\n", "Bird:Chicken JiJiJi fly");
}

constructor_imp(Bird, int type)
{
	Chis(Bird, MCObject, nil);
	//bind
	if(set_class(this, "Bird", "MCObject")){
		bind(this, MK(fly), MV(Bird, fly));
		bind(this, MK(bye), MV(Bird, bye));
	}
	//override
	if(type==DUCK_TYPE){
		this->name="Bird:Duck";
		override(this, MK(fly), MV(Duck, fly));
	}else if(type==CHICKEN_TYPE){
		this->name="Bird:Chicken";
		override(this, MK(fly), MV(Chicken, fly));
	}
	//var init
	this->type=type;
}
