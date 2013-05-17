#include "BirdModeA.h"

modiniter(Bird, ModeA)
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

modloader(Bird, ModeA)
{
	binding(Bird, modemethodA, xxx);
	binding(Bird, modemethodB, int type);
	binding(Bird, modemethodC, xxx);
	binding(Bird, modemethodD, xxx);
}
