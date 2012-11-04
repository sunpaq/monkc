#include "MCRuntime.h"

void bind_start(MCClass* const self, funcptr(mptr1), funcptr(mptr2)){
	self->method_index = 0;
	self->method_offset = (int)mptr2 - (int)mptr1;
	self->method_first = mptr1;
	//clear to 0
	memset(self->method_list, 0, MAX_METHOD_NUM);
	memset(self->method_boolean, 0, MAX_METHOD_NUM);
	//bind the first and second
	self->method_list[self->method_index] = mptr1;
	self->method_boolean[self->method_index] = 1;
	self->method_index++;
	self->method_list[self->method_index] = mptr2;
	self->method_boolean[self->method_index] = 1;
	self->method_index++;
}

int bind_method(MCClass* const self, funcptr(mptr)){
	if(self->method_index > MAX_METHOD_NUM-1){
		printf("method index out of bound\n");
		return -1;
	}
	self->method_list[self->method_index] = mptr;
	self->method_boolean[self->method_index] = 1;
	self->method_index++;
	printf("add a method, index:%d\n",self->method_index-1);
	return self->method_index-1;
}

int get_method_index(MCClass* const self, funcptr(name)){

	// int i;
	// for (i = 0; i < MAX_METHOD_NUM-1; ++i)
	// {
	// 	if(self->method_list[i]==name)return i;
	// }
	// return -1;

	printf("in get_method_index\n");
	int step = self->method_offset;
	int offset = (int)name - (int)self->method_first;
	int index = (int)offset / step;
	printf("step is: %d offset is: %d index is: %d\n", step, offset, index);
	return index;
}

bool response_to_method(MCClass* const self, funcptr(name)){

	// int i;
	// for (i = 0; i < (MAX_METHOD_NUM-1); ++i)
	// {
	// 	if(self->method_list[i]==name)return true;
	// }
	// return false;

	int index = get_method_index(self, name);
	if (self->method_boolean[index]==1)
	{
		printf("%s\n", "in class can response_to_method");
		return true;
	}else{
		printf("%s\n", "in class can not response_to_method");
		return false;
	}
}

void call(MCClass* const self, funcptr(name), id para){
	MCClass* obj = self;
	while(response_to_method(obj, name)==false){
		if(obj->super != nil){
			obj = obj->super;
			printf("%s\n", "continue to my super");
		}else{
			printf("%s\n", "MC_call return");
			return;
		}
	}

	obj->method_list[get_method_index(obj, name)](nil);
	printf("%s\n", "MC_call finish");
}
