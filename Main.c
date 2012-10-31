#include "DynamicArrayByMacros.h"
#include "ClassA.h"

Main(
	new(aaa,ClassA,nil);
	call(aaa,open,nil);
	//printf("%d\n",DynamicArray_count);
	//DynamicArray_classmethod();
	//new
	new(da,DynamicArray,100);
	new(db,DynamicArray,200);

	call(da,addItem,nil);
	call(da,addItem,nil);
	call(db,removeItem,1);
	call(db,removeItem,1);

	//delete
	bye(da);
	bye(db);
)