#define CLASS DynamicArray
#include "OOP_MACROS.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Interface(DynamicArray)
	void* pointer;
	int currentIndex;
	ssize_t currentSize;
	int dcl( addItem ) end();
	void dcl( removeItem ) 
	arg() int index end();

Implement(DynamicArray)

	Var int DynamicArray_count = 1000;
	Function void DynamicArray_classmethod(void){
		printf("this is a classmethod of DynamicArray\n");
	}

	var int count = 0;
	function void logindex(int index){
		printf("this is the addItem method, currentIndex:%d\n",index);
	}

	method int imp( addItem ) end()
	body(
		this->currentIndex++;
		logindex(this->currentIndex);
		return this->currentIndex;
	)

	method void imp( removeItem )
	arg() int index end()
	body(
		this->currentIndex--;
		logindex(this->currentIndex);
	)

Constructor(DynamicArray)
Arg() size_t init_size End()
Body(
		Set(DynamicArray,currentIndex,10)
		Bind(DynamicArray,addItem)
		Bind(DynamicArray,removeItem)
		ReturnInstance(DynamicArray)
)

/*******************************************************************/
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