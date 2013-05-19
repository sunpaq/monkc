#include "MCMath.h"

loader(MCMath)
{
	binding(MCMath, bye, xxx);
	binding(MCMath, addInteger2, int a, int b) returns(int sum);
}

initer(MCMath)
{
	this->tid = 0;
}

method(MCMath, bye, xxx)
{
	debug_log("%s\n", "MCMath bye bye");
}

method(MCMath, addInteger2, int a, int b) returns(int sum)
{
	return a + b;
}

