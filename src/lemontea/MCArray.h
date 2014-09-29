#include "MCContext.h"

#ifndef MCARRAY_H_
#define MCARRAY_H_

monkc(MCArray);
	int count;
	int size;
	int indexLast;
	void* (*buff)[];
end(MCArray);

method(MCArray, MCArray*, initWithSize, int size);
method(MCArray, MCArray*, addItem, void* item);
method(MCArray, MCArray*, addItemToIndex, void* item, int index);
method(MCArray, MCArray*, removeLastItem, xxx);
method(MCArray, MCArray*, removeItem, void* item);
method(MCArray, MCArray*, removeItemByIndex, int index);
method(MCArray, MCArray*, clear, xxx);
method(MCArray, void*, getItemByIndex, int index);
method(MCArray, void, visiteEachBy, lamdafunc visitorFunction);
method(MCArray, void, visiteEachWithData, lamdafunc visitorFunction, void* data);
void example_visitor1(_lamda, void* item, int index);
void example_visitor2(_lamda, void* item, int index, void* data);

#endif /* MCARRAY_H_ */
