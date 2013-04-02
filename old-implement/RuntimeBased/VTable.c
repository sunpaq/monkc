#include "VTable.h"

method_imp(VTable, amethod, xxx)
{
	This(VTable);
	debug_log("VTable amethod\n");
	return 1;
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

#define IMPLEMENT
#include "DrawableProtocol.h"
protocol_imp(VTable, draw, xxx){
	This(VTable);
	//printf("%s:%s\n", "VTable draw", this->main_color);
	puts("VTable draw");
}

method_imp(VTable, bye, xxx)
{
	This(VTable);
	//do clean job
	//release(this->super_instance);
}

method_imp(VTable, init, xxx)
{
	This(VTable);
	SuperInit(VTableSuper, this, nil);

	if(set_class(this, "VTable", "VTableSuper")){
		bind(this, MT(amethod), MA(VTable, amethod));
		bind(this, MT(bmethod), MA(VTable, bmethod));
		bind(this, MT(cmethod), MA(VTable, cmethod));
		bind(this, MT(bye), MA(VTable, bye));
		#define BIND
		#include "DrawableProtocol.h"
	}

	override(this, MT(draw), MA(VTable, draw));

	this->main_color="sliver";
	//this->info="this is a VTable info";
}