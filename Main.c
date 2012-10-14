#include "DynamicArrayByMacros.c"

Main(
	//old
	// DynamicArray* dold = DynamicArray_new(100);
	// dold->addItem(dold);
	// dold->removeItem(dold,1);
	printf("%d\n",DynamicArray_count);
	DynamicArray_classmethod();
	//new
	DynamicArray* da = New(DynamicArray)
					   Arg() 100 End();
	DynamicArray* db = New(DynamicArray)
					   Arg() 200 End();

	call(da,addItem)end();
	call(da,addItem)end();
	call(db,removeItem)
	arg() 1 end();
	call(db,removeItem)
	arg() 1 end();

	free(da);
	free(db);
)