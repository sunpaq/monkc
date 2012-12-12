#include "VTableSuper.h"

method_imp(VTableSuper, show, BOOL isPrint, char* str)
{
	This(VTableSuper);
	if (isPrint){
		debug_log("%s:%s\n", this->info, str);
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

protocol_imp(DrawableProtocol, draw, xxx)
{
	This(VTableSuper);
	debug_log("%s:%s\n", "VTableSuper draw", this->main_color);
}

protocol_imp(DrawableProtocol, erase, xxx)
{
	This(VTableSuper);
	debug_log("%s:%s\n", "VTableSuper erase", this->main_color);
}

protocol_imp(DrawableProtocol, redraw, xxx){
	This(VTableSuper);
	debug_log("%s:%s\n", "VTableSuper redraw", this->main_color);
}

method_imp(VTableSuper, bye, xxx)
{
	This(VTableSuper);
	//do clean here
}

constructor_imp(VTableSuper, xxx)
{
	Chis(VTableSuper, MCObject, nil);

	if(set_class(this, "VTableSuper", "MCObject")){
		bind(this, MK(show), MV(VTableSuper, show));
		bind(this, MK(bmethod), MV(VTableSuper, bmethod));
		bind(this, MK(cmethod), MV(VTableSuper, cmethod));
		bind(this, MK(bye), MV(VTableSuper, bye));
		#define BIND
		#include "DrawableProtocol.h"
	}

	override(this, MK(draw), MV(DrawableProtocol, draw));
	override(this, MK(erase), MV(DrawableProtocol, erase));
	
	this->main_color = "super-red";
	this->info="this is a VTableSuper info";
}