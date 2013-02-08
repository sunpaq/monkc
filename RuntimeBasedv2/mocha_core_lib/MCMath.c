#include "MCMath.h"

constructor(MCMath, xxx)
{
	link_class(MCMath, MCObject, nil)
	{
		have_method(MCMath, new, xxx);
	}

	return this;
}

method(MCMath, new, xxx)
{
	//
}
