#ifndef Cell_
#define Cell_

#include "monkc.h"

class(Cell, MCObject,
    unsigned age;
)

method(Cell, void, breath, voida);
method(Cell, void, breed, voida);

#endif