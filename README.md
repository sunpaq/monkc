author: sunpaq
email:  sunpaq@gmail.com

OOP Macros for C:

syntex:
	
	#define CLASS MyClass
	#include "OOP_MACROS.h"

	Class(MyClass)
		int var;
		void dcl( method )
		arg() int arg1, float arg2 end();

	Implement(MyClass)
		static void imp( method )
		arg() int arg1, float arg2 end()
		body(
			this->var = 0;
		)

	Constructor(MyClass)
	Arg() int arg1, float arg2 End()
	Body(
		Var(MyClass,var) = 100;
		Bind(MyClass,method);
		ReturnInstance(MyClass);
	)	


useage:

	MyClass* instance = New(MyClass)Arg() 10, 10.5 End();
	call(instance,method)arg() 1, 1.5 end();
	free(instance)
