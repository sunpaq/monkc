#include "VTableSuper.h"

method_imp(VTableSuper, show, BOOL isPrint, char* str)
{
	if (isPrint){
		debug_log("%s\n", str);
		return YES;
	}else
		return NO;
}

method_imp(VTableSuper, bmethod, int a, double b, char* c)
{
	debug_log("super method b1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("super method b2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

method_imp(VTableSuper, cmethod, int a, double b, char* c)
{
	debug_log("super method c1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("super method c2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("super method c3: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

#define IMPLEMENT
#include "DrawableProtocol.h"
protocol_imp(VTableSuper, draw, xxx)
{
	This(VTableSuper);
	debug_log("%s:%s\n", "VTableSuper draw", this->main_color);
}

protocol_imp(VTableSuper, erase, xxx)
{
	This(VTableSuper);
	debug_log("%s:%s\n", "VTableSuper erase", this->main_color);
}

method_imp(VTableSuper, bye, xxx)
{
	This(VTableSuper);
	//do clean here
}

method_imp(VTableSuper, init, xxx)
{
	This(VTableSuper);
	setting_start(this, "VTableSuper");
		this->main_color = "super-red";

		bind(this, MT(show), MA(VTableSuper, show));
		bind(this, MT(bmethod), MA(VTableSuper, bmethod));
		bind(this, MT(cmethod), MA(VTableSuper, cmethod));

		#define BIND
		#include "DrawableProtocol.h"
		override(this, MT(draw), MA(VTableSuper, draw));
		override(this, MT(erase), MA(VTableSuper, erase));

	setting_end(this, MA(VTableSuper, bye));
}