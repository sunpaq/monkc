#include "MCMath.h"

method_imp(MCMath, new, xxx)
{
	This(MCMath);
}

constructor_imp(MCMath, xxx)
{
	Chis(MCMath, MCObject, nil);
	if (set_class(this, MK(MCMath), MK(MCObject)))
	{
		bind(this, MK(new), MV(MCMath, new));
	}


}