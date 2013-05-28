#include "BirdModeA.h"

initer(BirdModeA)
{
	//
}

method(Bird, modemethodA, xxx)
{

}

method(Bird, modemethodB, int type)
{

}

method(Bird, modemethodC, xxx)
{
	debug_log("Bird ModeA modemethodC\n");
}

method(Bird, modemethodD, xxx)
{

}

loader(BirdModeA)
{
	binding(Bird, modemethodA, xxx);
	binding(Bird, modemethodB, int type);
	binding(Bird, modemethodC, xxx);
	binding(Bird, modemethodD, xxx);
}
