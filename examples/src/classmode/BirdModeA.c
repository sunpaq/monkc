#include "BirdModeA.h"

initer(BirdModeA)
{
	return obj;
}

method(Bird, void, modemethodA, xxx)
{
	debug_log("Bird ModeA modemethodA\n");
}

method(Bird, void, modemethodB, int type)
{
	debug_log("Bird ModeA modemethodB\n");
}

method(Bird, void, modemethodC, xxx)
{
	debug_log("Bird ModeA modemethodC\n");
}

method(Bird, void, modemethodD, xxx)
{
	debug_log("Bird ModeA modemethodD\n");
}

loader(BirdModeA)
{
	binding(Bird, void, modemethodA, xxx);
	binding(Bird, void, modemethodB, int type);
	binding(Bird, void, modemethodC, xxx);
	binding(Bird, void, modemethodD, xxx);
	return claz;
}
