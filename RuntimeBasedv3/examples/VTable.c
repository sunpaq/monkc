#include "VTable.h"

constructor(VTable, xxx) returns(VTable*)
{
	link_class(VTable, VTableSuper, nil)
	{
		binding(VTable, bye, xxx);
		binding(VTable, amethod, xxx) 							returns(int);
		binding(VTable, amethod2, char* srt, int index);
		binding(VTable, bmethod, int a, vector b, char* c);
		binding(VTable, cmethod, int a, vector b, char* c);

		#define BIND
		#include "DrawableProtocol.h"

	}
		
	this->main_color="sliver";
	//this->info="this is a VTable info";
	//instance=this;

	this->private.a = 4;
	this->private.b = 5;
	this->private.c = 6;
	return this;
}

static VTable* instance=nil;

VTable* VTable_getInstance()
{
	if(instance==nil){
		instance = new(VTable, nil);
		instance->ref_count = -1;
		return instance;
		debug_log("return new instance: %d\n", instance);
	}else{
		debug_log("return old instance: %d\n", instance);
		return instance;
	}
}

void VTable_releaseInstance()
{
	debug_log("release old instance: %d\n", instance);
	mc_free(instance);
	instance=nil;
}

static void function(){
	//private function
	printf("%s\n", "this is a private function");
}

method(VTable, amethod, xxx) returns(int)
{
	debug_log("VTable amethod\n");
	return 1;
}

method(VTable, amethod2, char* srt, int index)
{
	debug_log("VTable amethod2: %s\n", srt);
}

method(VTable, bmethod, int a, vector b, char* c)
{
	debug_log("method argument: a/b/c is:%d/%1.2f/%s\n", a, popvx(b), c);
	debug_log("method super-public: a/b/c is:%d/%d/%d\n", this->a, this->b, this->c);
	debug_log("method private: a/b/c is:%d/%d/%d\n", this->private.a, this->private.b, this->private.c);
}

method(VTable, cmethod, int a, vector b, char* c)
{
	debug_log("method c1: a/b/c is:%d/%1.2f/%s\n", a, popvx(b), c);
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
	//every release have no effect
}


