#include "MCMath.h"

constructor(MCMath, xxx)
{
	link_class(MCMath, MCObject, nil)
	{
		binding(MSNA, MCMath, bye, xxx);
		binding(MS(3,I,I,I), MCMath, addInteger2, int a, int b) returns(int sum);
	}

	return this;
}

method(MCMath, bye, xxx)
{
	printf("%s\n", "MCMath bye bye");
}

method(MCMath, addInteger2, int a, int b) returns(int sum)
{
	return a + b;
}

