#include "MCContext.h"

#ifndef MCARRAY_H_
#define MCARRAY_H_

class(MCArray, MCObject,
	int count;
	int size;
	int indexLast;
	void* (*buff)[];
);

method(MCArray, MCArray*, initWithSize, int size);
method(MCArray, MCArray*, addItem, void* item);
method(MCArray, MCArray*, addItemToIndex, void* item, int index);
method(MCArray, MCArray*, removeLastItem, voida);
method(MCArray, MCArray*, removeItem, void* item);
method(MCArray, MCArray*, removeItemByIndex, int index);
method(MCArray, MCArray*, clear, voida);
method(MCArray, void, bye, voida);
method(MCArray, void*, getItemByIndex, int index);
method(MCArray, void, visiteEachBy, mc_message visitorFunction);
method(MCArray, void, visiteEachWithData, mc_message visitorFunction, void* data);
void example_visitor1(mc_message_arg(MCArray), void* item, int index);
void example_visitor2(mc_message_arg(MCArray), void* item, int index, void* data);

#endif /* MCARRAY_H_ */
