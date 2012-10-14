#ifndef __DynamicArray__
#define __DynamicArray__

#include "OOP_MACROS.h"
#define CLASS DynamicArray

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

#endif