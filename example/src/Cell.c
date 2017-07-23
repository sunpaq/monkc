#include "Cell.h"

oninit(Cell) {
    if(init(MCObject)) {
        var(age) = 100;
        return obj;
    }
    return null;
}

method(Cell, void, breath, voida)
{
    printf("~~~~\n");
}

method(Cell, void, breed, voida)
{
    printf(">>>>\n");
}

onload(Cell) {
    if(load(MCObject)) {
        binding(Cell, void, breath, voida);
        binding(Cell, void, breed, voida);
        return cla;
    }
    return null;
}
