#include "MCSocket.h"

method(MCSocket, bye, xxx)
{
	//
}

constructor(MCSocket, xxx)
{
	super_init(this, MCObject, nil);

	if (set_class(this, MK(MCSocket), MK(MCObject)))
	{
		bind(this, MK(bye), MV(MCSocket, bye));
	}

	return this;
}