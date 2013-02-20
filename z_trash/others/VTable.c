#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_METHOD_NUM 100

#define id void*
#define nil ((void*)0)
#define funcptr(name) id (*name)(id)
#define funcarray(name) id (*name[MAX_METHOD_NUM])(id)
#define dcl(name) id _##name(id para);\
				  id name(id para){return _##name(para);}

typedef struct _class
{
	struct _class* super;
	funcarray(method_list);
}
Class;
Class classobj;

dcl(amethod)
dcl(bmethod)
dcl(cmethod)
dcl(dmethod)

id _amethod(id para){
	printf("method a\n");
}

id _bmethod(id para){
	printf("method b1\n");
	printf("method b2\n");
}

id _cmethod(id para){
	printf("method c1\n");
	printf("method c2\n");
	printf("method c3\n");
}

id _dmethod(id para){
	printf("method d1\n");
}

static funcarray(method_array);

int bind_method(funcptr(mptr)){
	static int index = 0;
	if(index > MAX_METHOD_NUM-1){
		//print out error
		printf("method index out of bound\n");
		return -1;
	}
	method_array[index++] = mptr;
	printf("add a method, index:%d\n",index-1);
	return index-1;
}

void call_method(int name){
	//int index = name-(int)amethod;
	int index = ((name % (int)amethod)/20);
	(method_array[index])(nil);
}

// id first_method(id para){
// 	printf("do nothing but mark the first address\n");
// }

Class classobj;
Class* Class_initialize(){

	//bind_method(first_method);
	bind_method(amethod);
	bind_method(bmethod);
	bind_method(cmethod);
	bind_method(dmethod);


	printf("Class is created\n");
	return &classobj;
}

int main(int argc, char const *argv[])
{

	Class* objptr = Class_initialize();
	//printf("method index is:%d\n",(int)first_mehtod);
	printf("method index is:%d\n",(int)amethod);
	printf("method index is:%d\n",(int)bmethod);
	printf("method index is:%d\n",(int)cmethod);
	printf("method index is:%d\n",(int)dmethod);

	call_method((int)amethod);
	call_method((int)bmethod);
	call_method((int)cmethod);
	call_method((int)dmethod);

	return 0;
}