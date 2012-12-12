#include "MCSocket.h"

method_imp(MCSocket, new, xxx)
{
	This(MCSocket);
}

constructor_imp(MCSocket, xxx)
{
	Chis(MCSocket, MCObject, nil);

	if (set_class(this, MK(MCSocket), MK(MCObject)))
	{
		bind(this, MK(new), MV(MCSocket, new));
	}
}