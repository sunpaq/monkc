#define CLASS DynamicArray
#include "OOP_MACROS.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Class(DynamicArray)
	void* pointer;
	int currentIndex;
	ssize_t currentSize;
	int dcl( addItem ) end();
	void dcl( removeItem ) 
	arg() int index end();

Implement(DynamicArray)
	static int imp( addItem ) end()
	body(
		this->currentIndex++;
		printf("this is the addItem method, currentIndex:%d\n",this->currentIndex);
		return this->currentIndex;
	)
	static void imp( removeItem )
	arg() int index end()
	body(
		this->currentIndex--;
		printf("this is the removeItem method, currentIndex:%d\n",this->currentIndex);
	)

Constructor(DynamicArray)
Arg() size_t init_size End()
Body(
		Var(DynamicArray,currentIndex) = 10;
		Bind(DynamicArray,addItem)
		Bind(DynamicArray,removeItem)
		ReturnInstance(DynamicArray)
)

/*******************************************************************/
Main(
	//old
	DynamicArray* dold = DynamicArray_new(100);
	dold->addItem(dold);
	dold->removeItem(dold,1);

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