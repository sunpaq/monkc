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
	hinding(Bird, void, modemethodA, 1891533949, xxx);
	hinding(Bird, void, modemethodB, 1891533950, int type);
	hinding(Bird, void, modemethodC, 1891533951, xxx);
	hinding(Bird, void, modemethodD, 1891533952, xxx);
	return claz;
}
