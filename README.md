author: sunpaq
email:  sunpaq@gmail.com

OOP Macros for C:

syntex:

[start of a file:]
	
	#define CLASS MyClass
	#include "OOP_MACROS.h"
	//you must use them at first of a class file

[write a class:]

	Class(C)
	   //vars
	   //methods
	Implement(C)
           //implement of the methods
	Constructor(C)
	   //the constructor of this class

       	//you must write them in order as above


[declare the method:]
		dcl(method_name)

[argumets:]
		arg() <arg_list> end()
		//even there is no argument at all, you still need the end()

[implement the method:]
		imp(method_name)

[method body:]
		body(your_method_body)

[class constructor:]
		//the constructor name always be: Constructor
		//the argument list mark must be uppercase: Arg() <argi_list> End()
		//the body mark must be uppercase: Body()
		//you can set the var by Var(MyClass,var) = xxx
		//you must bind the methods you implemented to your class 
		//you must return a instance at last of constructor
		//
		//keep in mind: the right constructor must be: Var()->Bind()->ReturnInstance()

example:
	
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
