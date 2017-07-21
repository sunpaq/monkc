#include "Monkey.h"

oninit(Monkey)
{
	if (init(Animal)) {
		{
			scope(Cell);
			scope->age = 31;
		}

		{
			scope(Animal);
			scope->name = "little monkey";
		}

		var(level) = 10;
		return obj;
	} else {
		return null;
	}
}

method(Monkey, void, info, voida)
{
	printf("%s\n", "show info");
}

method(Monkey, void, showname, voida)
{
	printf("Monkey name: %s\n", sobj->name);
}

method(Monkey, void, showage, voida)
{
	scope(Cell);
	printf("Monkey age: %d\n", scope->age);
}

function(void, fly, voida)
{
	printf("Monkey fly fly fly\n");
}

function(void, takeoff, const char* info)
{
	printf("Monkey takeoff %s\n", info);
}

function(void, landing, const char* info)
{
	printf("Monkey landing %s\n", info);
}

onload(Monkey)
{
	if (load(Animal)) {
		binding(Monkey, void, info, voida);
		binding(Monkey, void, showname, voida);
		binding(Monkey, void, showage, voida);
		#include "Flyable.h"
		return cla;
	} else {
		return null;
	}
}