#include "MCMath.h"

method(MCMath, new, xxx)
{
	//
}

constructor(MCMath, xxx)
{
	link_class(MCMath, MCObject, nil)
	{
		have_method(MCMath, new);
	}

	return this;
}