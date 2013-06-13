#include "MCMath.h"

loader(MCMath)
{
	binding(MCMath, void, bye, xxx);
	binding(MCMath, int, addInteger2, int a, int b);
}

initer(MCMath)
{
	this->tid = 0;
}

method(MCMath, void, bye, xxx)
{
	debug_log("%s\n", "MCMath bye bye");
}

method(MCMath, int, addInteger2, int a, int b)
{
	return a + b;
}

