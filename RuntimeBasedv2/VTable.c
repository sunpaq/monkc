#include "VTable.h"

static void function(){
	//private function
	printf("%s\n", "this is a private function");
}

method(VTable, amethod, xxx)
{
	debug_log("VTable amethod\n");
	return 1;
}

method(VTable, amethod2, char* srt, int index)
{
	debug_log("VTable amethod2: %s\n", srt);
}

method(VTable, bmethod, int a, double b, char* c)
{
	debug_log("method b1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("method b2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

method(VTable, cmethod, int a, double b, char* c)
{
	debug_log("method c1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("method c2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	debug_log("method c3: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

protocol(DrawableProtocol, erase, xxx){
	debug_log("%s:%s\n", "VTable erase", This(VTable)->main_color);
}

protocol(DrawableProtocol, draw, xxx){
	debug_log("%s:%s\n", "VTable draw", This(VTable)->main_color);
	call(this, DrawableProtocol, erase, nil);
	//ff(this, MK(erase), nil);
}

protocol(DrawableProtocol, redraw, xxx){
	//This(VTable);
	debug_log("%s:%s\n", "VTable redraw", This(VTable)->main_color);
}

method(VTable, bye, xxx)
{
	//do clean job
	//release(this->super_instance);
}

static Handle(VTable) instance=nil;

Handle(VTable) VTable_getInstance()
{
	if(instance==nil){
		//return new(VTable, nil);
		instance = new(VTable, nil);
		return instance;
		//printf("get single instance %s\n", instance->isa->name);
	}else
		return instance;
}

void VTable_releaseInstance()
{
	release(instance);
	instance=nil;
}

constructor(VTable, xxx)
{
	super_init(this, VTableSuper, nil);

	if(set_class(this, MK(VTable), MK(VTableSuper))){
		bind(this, MK(amethod), MV(VTable, amethod));
		bind(this, MK(amethod2), MV(VTable, amethod2));
		bind(this, MK(bmethod), MV(VTable, bmethod));
		bind(this, MK(cmethod), MV(VTable, cmethod));
		bind(this, MK(bye), MV(VTable, bye));
		#define BIND
		#include "DrawableProtocol.h"
	}
		
	this->main_color="sliver";
	//this->info="this is a VTable info";
	//instance=this;
	return this;
}