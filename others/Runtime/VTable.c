#include "VTable.h"

method_imp(VTable, amethod, xxx)
{
	This(VTable);
	// printf("class name is: %s\n", this->isa->name);
	// printf("method id is: %d\n", cmd);
	// printf("parameters: a/b/c is: %d/%s/%1.2f\n", a, b, c);
	return 1;
}

method_imp(VTable, bmethod, int a, double b, char* c)
{
	printf("method b1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	printf("method b2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

method_imp(VTable, cmethod, int a, double b, char* c)
{
	printf("method c1: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	printf("method c2: a/b/c is:%d/%1.2f/%s\n", a, b, c);
	printf("method c3: a/b/c is:%d/%1.2f/%s\n", a, b, c);
}

#define IMPLEMENT
#include "DrawableProtocol.h"
protocol_imp(VTable, draw, xxx){
	This(VTable);
	printf("%s:%s\n", "VTable draw", this->main_color);
}

method_imp(VTable, bye, xxx)
{
	This(VTable);
	//do clean job
	release(this->super_instance);
}

method_imp(VTable, init, xxx)
{
	This(VTable);
	setting_start(this, "VTable");

	this->main_color="sliver";

	New(VTableSuper, vtsuper, nil);
	set_super(this, vtsuper);

	bind(this, MT(amethod), MA(VTable, amethod));
	bind(this, MT(bmethod), MA(VTable, bmethod));
	bind(this, MT(cmethod), MA(VTable, cmethod));
	bind(this, MT(bye), MA(VTable, bye));

	#define BIND
	#include "DrawableProtocol.h"
	bind(this, MT(draw), MA(VTable, draw));
}