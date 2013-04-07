# Monk-C (Runtime based version)
a toolkit for OOP programming in C language

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)

## Overview

**Monk-C**, is a toolkit for OOP programming use pure C. the aim of Monk-C is to support OOP in pure C with some tiny C macros, functions and even a light preprocessor. Monk-C is inspired by Apple Objective-C and gcc builtin "Constructing Calls". It is tiny and primitive but full of fun. I use it to play with my RaspberryPi and it really vary suitable for the ARM/Linux based embeded systems. It is open source under BSD license(3-clause license). I written it under the X86/Linux platform and X86/MacOS ARM/Linux is also fully tested and supportted both 32bit and 64bit.

#### supported platforms:

	[CPUArch/OS/Compiler]

	IA-32/Linux/gcc&clang    OK
	X86-64/Linux/gcc&clang
	IA-32/MacOS/gcc&clang
	X86-64/MacOS/gcc&clang
	ARM32/Linux/gcc&clang
	ARM64/Linux/gcc&clang

## Syntax
**Monk-C** use "MC" as the prefix.
#### declear interface - write in .h file

		#ifndef _Classname
		#define _Classname _Supername;\
			type var1;\
			type var2;\
			type var3;\

		class(Classname);

		constructor( Classname, argument-list );

		method(Classname, bye, xxx);
		method(Classname, name1, arg-list);
		method(Classname, name2, arg-list);

		#endif
	
#### implement methods - write in .c file
		
		constructor(Classname, argument-list )
		{
			link_class(Classname, Supername, super-init-args)
			{
				binding(Classname, bye, xxx);
				binding(Classname, name1, arg-list);
				binding(Classname, name2, arg-list);
				override(Classname, supermethod, arg-list);
			}

			this->var1 = 0;
			return this;
		}

		method(Classname, name1, arg-list)
		{
			this->var++;
		}
			
		method(Classname, name2, arg-list)
		{
			this->var--;
		}
		
		method(Classname, bye, xxx)
		{
			//do clean work
		}

####method calling

	it just like the Objective-C. sending message instead of function call.

	VTable ret = new(VTable, nil);
	ff(ret, show, YES, "this is a super method called by child:VTable");

####Macros and runtime functions

---

1. _Classname
2. class
3. method
4. constructor

5. link_class
6. binding
7. override

9. new
10.call
11.response
12.ff

17.retain
18.release
19.relnil

19.id
20.xxx
21.nil
22.BOOL
23.String
24.Float
25.MV
26.MK
27.Handle

28.protocol
29. This
30. Cast

31.error_log
32.debug_log
33.runtime_log

---

Total **33** words.[^1]

####protocol file

	DrawableProtocol.h

		#ifdef METHOD 
		protocol(DrawableProtocol, draw, xxx);
		protocol(DrawableProtocol, erase, xxx);
		protocol(DrawableProtocol, redraw, xxx);
		#undef METHOD
		#endif

		#ifdef BIND
		binding(DrawableProtocol, draw, xxx);
		binding(DrawableProtocol, erase, xxx);
		binding(DrawableProtocol, redraw, xxx);
		#undef BIND
		#endif

######the METHOD part (include in .h file):

		#ifdef METHOD 
		protocol(DrawableProtocol, draw, xxx);
		protocol(DrawableProtocol, erase, xxx);
		protocol(DrawableProtocol, redraw, xxx);
		#undef METHOD
		#endif

it just list the vars, which is just as decleard in the interface of a class.

the purpose of doing this is: we can use **#include "xx.h"** to import them direct in our class interface ! just like this:

	#define METHOD
	#include "xx.h"
	method( Classname, name1, argument-list )
	
the result of doing this is amazing ! we have already have some feature called: "interface" or "abstract class"
in other OOP language.

######the BIND part (include in .c file):

	constructor(Classname, xxx)
	{
		link_class()
		{
			binding(Classname, method1, xxx);
			#define BIND
			#include "xx.h"
		}
	}

it just give implements of the methods in protocol file. as you can guess it also can be **#include "xx.h"**
to our .c files. we use this to simulate some **inherit** and **Polymorphism** feature.

####TODO list:

	1. more test use MCUnitTest framework.

	2. test runtime on arm/linux platform.

	3. a parser and some lightly added syntex to make the class define macros looks better

	4. method list in classobj should be read-only for instance
	(allow add method only)

	5. more detailed document.

	6. move more logic to MCObject

[^1]: the syntex is improving, maybe more/less keywords in the feature.

