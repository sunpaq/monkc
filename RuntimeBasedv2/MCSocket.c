#include "MCSocket.h"

<<<<<<< HEAD
method(MCSocket, new, xxx)
=======
method(MCSocket, bye, xxx)
>>>>>>> version 0108
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