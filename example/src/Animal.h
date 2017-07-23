#ifndef Animal_
#define Animal_

#include "Cell.h"

class(Animal, Cell,
    char* name;
)

method(Animal, void, eat, voida);
method(Animal, void, walk, voida);
method(Animal, void, sleep, voida);

#endif