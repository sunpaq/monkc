#include "Menifest.h"

Implement

	virtual_imp(void,amethod,xxx){
		printf("%s\n", "this is ClassA-amethod");
	}

	virtual_imp(void,bmethod,xxx){
		printf("%s\n", "this is ClassA-bmethod");
	}

	virtual_imp(void,cmethod,xxx){
		printf("%s\n", "this is ClassA-cmethod");
	}

	friend_borrow(ClassA,base_handler,void,retain,xxx)

	friend_imp(void,release,xxx){
		
	}

ImplementEnd(ClassA,xxx){
	new(h,Base,nil);
	Set(base_handler,h);
	Bind(amethod);
	Bind(bmethod);
	Bind(cmethod);
	Return(ClassA);
}


