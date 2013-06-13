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
binding(Bird, void, modemethodA, xxx);
binding(Bird, void, modemethodB, int type);
binding(Bird, void, modemethodC, xxx);
binding(Bird, void, modemethodD, xxx);
}
