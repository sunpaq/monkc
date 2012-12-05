#include "MCRuntime.h"

#ifdef VAR
	char* main_color;
#undef VAR
#endif
//----------------------------------------------------------
#ifdef METHOD 
protocol(DrawableProtocol, draw, xxx);
protocol(DrawableProtocol, erase, xxx);
protocol(DrawableProtocol, redraw, xxx);
#undef METHOD
#endif
//-----------------------------------------------------------
#ifdef IMPLEMENT
MCCast(DrawableProtocol);
	char* main_color;
MCCastEnd(DrawableProtocol);

protocol_imp(DrawableProtocol, draw, xxx)
{
	This(DrawableProtocol);
	this->main_color = "default-red";
	printf("%s:%s\n", "DrawableProtocol default draw", this->main_color);
}
protocol_imp(DrawableProtocol, erase, xxx)
{
	This(DrawableProtocol);
	this->main_color = "default-yellow";
	printf("%s:%s\n", "DrawableProtocol default erase", this->main_color);
}
protocol_imp(DrawableProtocol, redraw, xxx)
{
	This(DrawableProtocol);
	this->main_color = "default-blue";
	printf("%s:%s\n", "DrawableProtocol default redraw", this->main_color);
}
#undef IMPLEMENT
#endif
//----------------------------------------------------------
#ifdef BIND
bind(this, MT(draw), MA(DrawableProtocol, draw));
bind(this, MT(erase), MA(DrawableProtocol, erase));
bind(this, MT(redraw), MA(DrawableProtocol, redraw));
#undef BIND
#endif