#include "VTable.h"

/* main */

int main(int argc, char const *argv[])
{

	printf("super method index is:%d\n",(int)super_amethod);
	printf("super method index is:%d\n",(int)super_bmethod);
	printf("super method index is:%d\n",(int)super_cmethod);
	printf("super method index is:%d\n",(int)super_dmethod);
	printf("Class method index is:%d\n",(int)amethod);
	printf("Class method index is:%d\n",(int)bmethod);
	printf("Class method index is:%d\n",(int)cmethod);
	printf("Class method index is:%d\n",(int)dmethod);
	//MCClass* ins_ptr=Class_initialize();

	alloc(ret, MCClass);
	Class_initialize(ret);

	//printf("%d\n",(int)ret->method_list[2]);
	//ret->method_list[2](nil);
	//response_to_method(ret, cmethod);
	call(ret, cmethod, nil);
	call(ret, super_cmethod, nil);
	call(ret, super_amethod, nil);
	call(ret, super_bmethod, nil);
	call(ret, super_dmethod, nil);


	//get_method_index(ins_ptr, VTable_amethod);
	//response_to_method(ins_ptr, VTable_amethod);
	//ins_ptr->isa->method_list[get_method_index(ins_ptr->isa, VTable_bmethod)](nil);
	//call(ins_ptr->isa, VTable_cmethod, nil);
	//response_to_method(objptr->isa, VTable_amethod);
	//objptr->response_to_method(amethod);
	//MC_response_to_method(objptr, (int)Super_amethod);
	//objptr->super->call_method(samethod, nil);
	// MC_call(objptr, (int)Super_amethod, nil);
	// MC_call(objptr, (int)Super_bmethod, nil);
	// MC_call(objptr, (int)Super_cmethod, nil);
	// MC_call(objptr, (int)Super_dmethod, nil);


	// printf("Class method index is:%d\n",(int)Class_amethod);
	// printf("Class method index is:%d\n",(int)Class_bmethod);
	// printf("Class method index is:%d\n",(int)Class_cmethod);
	// printf("Class method index is:%d\n",(int)Class_dmethod);

	// printf("super method index is:%d\n",(int)Super_amethod);
	// printf("super method index is:%d\n",(int)Super_bmethod);
	// printf("super method index is:%d\n",(int)Super_cmethod);
	// printf("super method index is:%d\n",(int)Super_dmethod);

	// printf("method index is:%d\n",(int)amethod);
	// printf("method index is:%d\n",(int)bmethod);
	// printf("method index is:%d\n",(int)cmethod);
	// printf("method index is:%d\n",(int)dmethod);

	// call_method((int)amethod);
	// call_method((int)bmethod);
	// call_method((int)cmethod);
	// call_method((int)dmethod);

	// objptr->method_list[objptr->get_method_index(amethod)];
	// objptr->method_list[objptr->get_method_index(bmethod)];
	// objptr->get_method_index(amethod);
	// objptr->get_method_index(bmethod);
	// objptr->get_method_index(cmethod);
	// objptr->get_method_index(dmethod);

	// objptr->super->call_method((int)samethod);
	// objptr->super->call_method((int)sbmethod);
	// objptr->super->call_method((int)scmethod);
	// objptr->super->call_method((int)sdmethod);
	// if (objptr->super != nil)
	// {
	// 	objptr->super->call_method((int)samethod, nil);
	// 	objptr->super->call_method((int)sbmethod, nil);
	// 	objptr->super->call_method((int)scmethod, nil);
	// 	objptr->super->call_method((int)sdmethod, nil);
	// }

	// (objptr->method_list[0])(nil);
	// (objptr->method_list[1])(nil);
	// (objptr->method_list[2])(nil);
	// (objptr->method_list[3])(nil);

	// objptr->call_method((int)amethod, nil);
	// objptr->call_method((int)bmethod, nil);
	// objptr->call_method((int)cmethod, nil);
	// objptr->call_method((int)dmethod, nil);

	return 0;
}