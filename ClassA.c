#include "Menifest.h"

Interface
	virtual(void,amethod,xxx);
	virtual(void,bmethod,xxx);
	virtual(void,cmethod,xxx);
	Base* base_handler;
	int ref_count;
	friend(void,retain,xxx);
	friend(void,release,xxx);
InterfaceEnd(ClassA,xxx)

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
		call(this->base_handler,release,xxx);
		free();
	}

ImplementEnd(ClassA,xxx){
	new(h,Base,nil);
	Set(base_handler,h);
	Bind(amethod);
	Bind(bmethod);
	Bind(cmethod);
	Return(ClassA);
}


