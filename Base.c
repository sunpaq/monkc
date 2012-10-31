#include "Menifest.h"

Implement

	virtual_imp(void,retain,xxx){
		this(Base);
		this->ref_count++;
	}

	virtual_imp(void,release,xxx){
		this(Base);
		if ((this->ref_count--)==0)
		{
			free(this);
		}
	}

ImplementEnd(Base,xxx){
	Bind(retain);
	Bind(release);
	Return(Base);
}