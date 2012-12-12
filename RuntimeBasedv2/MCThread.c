#include "MCThread.h"


method_imp(MCThread, new, xxx)
{
	This(MCThread);
}

constructor_imp(MCThread, xxx)
{
	Chis(MCThread, MCObject, nil);

	if (set_class(this, "MCThread", "MCObject"))
	{
		bind(this, MK(new), MV(MCThread, new));
	}
}

