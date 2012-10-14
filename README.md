author: sunpaq
email:  sunpaq@gmail.com

OOP Macros for C:

syntex:

[marks:]

		Var      //this is a C-style global variable
		Function //this is a C-style global function
		var      //this is a C-style local variable
		function //this is a C-style local function
		method   //this is a OOP-style method of this class

[declare the method:]

		dcl(method_name)

[argumets:]

		arg(...)
		//at least one arg, fill it with tail: 
		arg(tail) 
		//if you want a dummy

[implement the method:]

		imp(method_name)arg(...)

[method body:]

		body(your_method_body)

[class constructor:]

		Constructor(class)Arg(...)Body(
			Bind(class,method1)
		)


-------------------------------------------------

[header file:]
	
	#ifndef __ClassA__
	#define __ClassA__
	#define CLASS ClassA
	#include "OOP_MACROS.h"
	Interface(ClassA)
		int i;
		int dcl(open)arg(tail);
		void dcl(onnew)arg(tail);
		void dcl(onbye)arg(tail);
	IEnd(ClassA,tail)
	#endif

[implement file:]

	#include "ClassA.h"
	// Interface(ClassA)
	// 	int i;
	// 	int dcl(open)arg(tail);
	// 	void dcl(onnew)arg(tail);
	// 	void dcl(onbye)arg(tail);
	// Interface(ClassA,tail)
	Implement(ClassA)
		method int imp(open)arg(tail)
		body(
			printf("ClassA open\n");
		)

		method void imp(onnew)arg(tail)
		body(
			printf("ClassA hello\n");
		)

		method void imp(onbye)arg(tail)
		body(
			printf("ClassA byebye!\n");
		)
	MEnd(ClassA)
	Constructor(ClassA)Arg(tail)
	Body(
		Bind(ClassA,onnew);
		Bind(ClassA,onbye);
		Bind(ClassA,open);
	)CEnd(ClassA)


[how to use objects:]


#include "DynamicArrayByMacros.h"
#include "ClassA.h"
Main(
	new(ClassA,aaa,nil);
	call(aaa,open,nil);
	//printf("%d\n",DynamicArray_count);
	//DynamicArray_classmethod();
	//new
	new(DynamicArray,da,100);
	new(DynamicArray,db,200);

	call(da,addItem,nil);
	call(da,addItem,nil);
	call(db,removeItem,1);
	call(db,removeItem,1);

	//delete
	bye(da);
	bye(db);
)
