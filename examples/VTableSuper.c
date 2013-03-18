#include "VTableSuper.h"

constructor(VTableSuper, xxx)
{
	link_class(VTableSuper, MCObject, nil)
	{
		binding(MSNA, VTableSuper, bye, xxx);
		binding(MS(3,I,I,P), VTableSuper, show, BOOL isPrint, char* str) returns(BOOL);
		binding(MS(4,P,I,D,P), VTableSuper, bmethod, int a, double b, char* c);
		binding(MS(4,P,I,D,P), VTableSuper, cmethod, int a, double b, char* c);
		#define BIND
		#include "DrawableProtocol.h"
	}
	
	this->main_color = "super-red";
	this->info="this is a VTableSuper info";

	this->a = 1;
	this->b = 2;
	this->c = 3;

	return this;
}

method(VTableSuper, show, BOOL isPrint, char* str)
{
	if (isPrint){
		debug_log("%s:%s\n", this->info, str);
		return YES;
	}else
		return NO;
}

method(VTableSuper, bmethod, int a, double b, char* c)
{
	debug_log("super method b1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("super method b2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

method(VTableSuper, cmethod, int a, double b, char* c)
{
	debug_log("super method c1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("super method c2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("super method c3: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

protocol(DrawableProtocol, draw, xxx)
{
	debug_log("%s:%s\n", "VTableSuper draw", This(VTableSuper)->main_color);
}

protocol(DrawableProtocol, erase, xxx)
{
	debug_log("%s:%s\n", "VTableSuper erase", This(VTableSuper)->main_color);
}

protocol(DrawableProtocol, redraw, xxx){
	debug_log("%s:%s\n", "VTableSuper redraw", This(VTableSuper)->main_color);
}

method(VTableSuper, bye, xxx)
{
	//do clean here
}

