#include "Monkey.h"

oninit(Monkey)
{
	if (init(MCObject)) {
		var(name) = "little monkey";
		var(age) = 30;
		return obj;
	} else {
		return mull;
	}
}

method(Monkey, void, info, voida)
{
	printf("%s\n", "show info");
}

method(Monkey, void, showname, voida)
{
	printf("Monkey name: %s\n", obj->name);
}

method(Monkey, void, showage, voida)
{
	printf("Monkey age: %d\n", obj->age);
}

onload(Monkey)
{
	if (load(MCObject)) {
		binding(Monkey, void, info, voida);
		binding(Monkey, void, showname, voida);
		binding(Monkey, void, showage, voida);
		return cla;
	} else {
		return mull;
	}
}