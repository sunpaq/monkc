#include "MCMath.h"

method(MCMath, new, xxx)
{
	//
}

constructor(MCMath, xxx)
{
	super_init(this, MCObject, nil);

	if (set_class(this, MK(MCMath), MK(MCObject)))
	{
		bind(this, MK(new), MV(MCMath, new));
	}

	return this;
}