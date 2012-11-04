#include "VTable.h"
/* implement */
// method_anchor(VTable, amethod);
// method_anchor(VTable, bmethod);
// method_anchor(VTable, cmethod);
// method_anchor(VTable, dmethod);

id amethod(id para){
	printf("method a\n");
}

id bmethod(id para){
	printf("method b1\n");
	printf("method b2\n");
}

id cmethod(id para){
	printf("method c1\n");
	printf("method c2\n");
	printf("method c3\n");
}

id dmethod(id para){
	printf("method d1\n");
}

/* constructor */
//MCObject instance;
//MCClass classobj;
void Class_initialize(MCClass* self){
	//instance.isa = &classobj;

	alloc(vtsuper, MCClass);
	Super_initialize(vtsuper);
	self->super=vtsuper;

	bind_start(self, amethod, bmethod);
	bind_method(self, cmethod);
	bind_method(self, dmethod);

	
	//MCClass* ret = (MCClass*)malloc(sizeof(classobj));
	//memcpy(ret, &classobj, sizeof(classobj));
	//printf("Class is created\n");
	//printf("%d\n",(int)ret->method_list[2]);

	//return ret;

	
	//classobj->super = Super_initialize();
	// printf("Class is created\n");
	// printf("Class method index is:%d\n",(int)VTable_amethod);
	// printf("Class method index is:%d\n",(int)VTable_bmethod);
	// printf("Class method index is:%d\n",(int)VTable_cmethod);
	// printf("Class method index is:%d\n",(int)VTable_dmethod);

	// response_to_method(ins_ptr->isa, VTable_amethod);
	// ins_ptr->isa->method_list[get_method_index(ins_ptr->isa, VTable_bmethod)](nil);
	// call(ins_ptr->isa, VTable_cmethod, nil);
}
