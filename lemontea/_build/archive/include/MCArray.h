#include "MCContext.h"

#ifndef MCARRAY_H_
#define MCARRAY_H_

class(MCArray, MCObject,
	size_t count;
	size_t maxcount;
	size_t indexLast;
    MCGeneric* buff);

method(MCArray, void, bye, voida);
method(MCArray, MCArray*, initWithMaxCount, size_t max);
method(MCArray, MCArray*, addItem, MCGeneric item);
method(MCArray, MCArray*, addItemToIndex, MCGeneric item, size_t index);
method(MCArray, MCArray*, removeLastItem, voida);
method(MCArray, MCArray*, removeItem, MCGeneric* item);
method(MCArray, MCArray*, removeItemByIndex, size_t index);
method(MCArray, MCArray*, clear, voida);
method(MCArray, MCGeneric*, getItemByIndex, size_t index);
method(MCArray, void, printAll, const char* delimiter);

#endif /* MCARRAY_H_ */
