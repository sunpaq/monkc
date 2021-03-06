#include "MonkeyExt.h"

method(Monkey, void, extensionMethod, voida)
{
	printf("%s extensionMethod\n", svar(name));
}

function(void, extensionFunction, voida)
{
	as(Monkey);
	printf("%s extensionFunction\n", svar(name));
}

onextend(Monkey, Ext)
{
	binding(Monkey, void, extensionMethod, voida);
	mixing(void, extensionFunction, voida);
}
