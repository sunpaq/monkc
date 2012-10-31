#ifndef __DynamicArray__
#define __DynamicArray__

#define CLASS DynamicArray
#include "OOP_MACROS.h"

Interface(DynamicArray)
	id pointer;
	int currentIndex;
	ssize_t currentSize;
	int dcl( addItem )arg(tail);
	void dcl( removeItem )arg(int index);
	void dcl( onnew )arg(tail);
	void dcl( onbye )arg(tail);
IEnd(DynamicArray,size_t init_size)

#endif