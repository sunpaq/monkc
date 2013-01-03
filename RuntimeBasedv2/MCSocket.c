#include "MCSocket.h"

method(MCSocket, new, xxx)
{
	//
}

constructor(MCSocket, xxx)
{
	super_init(this, MCObject, nil);

	if (set_class(this, MK(MCSocket), MK(MCObject)))
	{
		bind(this, MK(new), MV(MCSocket, new));
	}

	return this;
}