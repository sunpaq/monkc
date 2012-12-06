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
method_imp(Bird, init, int type)
{
	This(Bird);
	setting_start(this, "Bird");
		this->type=type;
		bind(this, MT(fly), MA(Bird, fly));
		if(type==DUCK_TYPE){
			this->name="Bird:Duck";
			override(this, MT(fly), MA(Duck, fly));
		}
		else if(type==CHICKEN_TYPE){
			this->name="Bird:Chicken";
			override(this, MT(fly), MA(Chicken, fly));
		}
	setting_end(this, MA(Bird, bye));
}
