#include "VTableSuper.h"

id super_amethod(id para){
	printf("method a\n");
}

id super_bmethod(id para){
	printf("method b1\n");
	printf("method b2\n");
}

id super_cmethod(id para){
	printf("method c1\n");
	printf("method c2\n");
	printf("method c3\n");
}

id super_dmethod(id para){
	printf("method d1\n");
}

/* constructor */
//MCObject instance;
//MCClass classobj;
void Super_initialize(MCClass* self){
	//instance.isa = &classobj;
	self->super=nil;

	bind_start(self, super_amethod, super_bmethod);
	bind_method(self, super_cmethod);
	bind_method(self, super_dmethod);
}
