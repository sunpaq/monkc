#include "BirdModeA.h"

initer(BirdModeA)
{
	//
}

method(Bird, void, modemethodA, xxx)
{

}

method(Bird, void, modemethodB, int type)
{

}

method(Bird, void, modemethodC, xxx)
{
	debug_log("Bird ModeA modemethodC\n");
}

method(Bird, void, modemethodD, xxx)
{

}

loader(BirdModeA)
{
hinding(Bird, void, modemethodA, 1891533949, xxx);
hinding(Bird, void, modemethodB, 1891533950, int type);
hinding(Bird, void, modemethodC, 1891533951, xxx);
hinding(Bird, void, modemethodD, 1891533952, xxx);
}
