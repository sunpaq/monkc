#include "VTableSuper.h"

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

constructor(VTableSuper, xxx)
{
	super_init(this, MCObject, nil);

	if(set_class(this, "VTableSuper", "MCObject")){
		bind(this, MK(show), MV(VTableSuper, show));
		bind(this, MK(bmethod), MV(VTableSuper, bmethod));
		bind(this, MK(cmethod), MV(VTableSuper, cmethod));
		bind(this, MK(bye), MV(VTableSuper, bye));
		#define BIND
		#include "DrawableProtocol.h"
	}
	
	this->main_color = "super-red";
	this->info="this is a VTableSuper info";

	return this;
}