#include "Animal.h"

oninit(Animal) {
    if(init(Cell)) {
        var(name) = "animal";
        return obj;
    }
    return null;
}

method(Animal, void, eat, voida)
{
    printf("%s eating...\n", var(name));
}

method(Animal, void, walk, voida)
{
    printf("%s walking...\n", var(name));
}

method(Animal, void, sleep, voida)
{
    printf("%s Zzz...\n", var(name));
}

onload(Animal) {
    if(load(Cell)) {
        binding(Animal, void, eat, voida);
        binding(Animal, void, walk, voida);
        binding(Animal, void, sleep, voida);
        return cla;
    }
    return null;
}