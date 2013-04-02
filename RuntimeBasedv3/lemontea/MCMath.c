#include "MCMath.h"

constructor(MCMath, xxx)
{
	link_class(MCMath, MCObject, nil)
	{
		binding(MCMath, bye, xxx);
		binding(MCMath, addInteger2, int a, int b) returns(int sum);
	}

	return this;
}

method(MCMath, bye, xxx)
{
	debug_log("%s\n", "MCMath bye bye");
}

method(MCMath, addInteger2, int a, int b) returns(int sum)
{
	return a + b;
}

