#include "VTable.h"

static void function(){
	//private function
}

method_imp(VTable, amethod, xxx)
{
	This(VTable);
	debug_log("VTable amethod\n");
	return 1;
}

method(VTable, amethod2, char* srt, int index)
{
	This(VTable);
	debug_log("VTable amethod2: %s\n", srt);
}

method_imp(VTable, bmethod, int a, double b, char* c)
{
	debug_log("method b1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("method b2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

method_imp(VTable, cmethod, int a, double b, char* c)
{
	debug_log("method c1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("method c2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("method c3: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

protocol_imp(DrawableProtocol, draw, xxx){
	This(VTable);
	debug_log("%s:%s\n", "VTable draw", this->main_color);
}

protocol_imp(DrawableProtocol, erase, xxx){
	This(VTable);
	debug_log("%s:%s\n", "VTable erase", this->main_color);
}

protocol_imp(DrawableProtocol, redraw, xxx){
	This(VTable);
	debug_log("%s:%s\n", "VTable redraw", this->main_color);
}

method_imp(VTable, bye, xxx)
{
	This(VTable);
	//do clean job
	//release(this->super_instance);
}

constructor_imp(VTable, xxx)
{
	Chis(VTable, VTableSuper, nil);
	if(set_class(this, MK(VTable), MK(VTableSuper))){
		bind(this, MK(amethod), MV(VTable, amethod));
		bind(this, MK(amethod2), MV(VTable, amethod2));
		bind(this, MK(bmethod), MV(VTable, bmethod));
		bind(this, MK(cmethod), MV(VTable, cmethod));
		bind(this, MK(bye), MV(VTable, bye));
		#define BIND
		#include "DrawableProtocol.h"
	}

	override(this, MK(draw), MV(DrawableProtocol, draw));

	this->main_color="sliver";
	//this->info="this is a VTable info";
}