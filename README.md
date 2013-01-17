# Mocha-R (Runtime based version)
a set of C macro for OOP programming

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)

## Overview

**Mocha**, is a set of C macros for OOP programming use pure C, the aim of Mocha is to add less syntex to support OOP. The reason to make this is as C is a language so beautiful and so powerful. and the OOP is so handful and nature for a programer. i want to mix them with the less modification

## Syntax
**Mocha** use "MC" as the prefix.
#### declear interface - write in .h file

		#ifndef _Classname
		#define _Classname _Supername;\
			type var1;\
			type var2;\
			type var3;\

		class(Classname);
		method(Classname, bye, xxx);
		method(Classname, name1, arg-list);
		method(Classname, name2, arg-list);
		constructor( Classname, argument-list );

		#endif
	
#### implement methods - write in .c file
		
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

		constructor(Classname, argument-list )
		{
			super_init(this, Supername, argument-list);

			if(set_class(this, "Classname", "Supername")){
				bind(this, MK(name1), MV(Classname, name1));
				bind(this, MK(name2), MV(Classname, name2));
				bind(this, MK(bye), MV(Classname, bye));
				override(this, MK(super_method1), MV(Supername, super_method1));
			}
		}

####Macros and runtime functions

---

1. _Classname
2. class
3. method
4. constructor

5. super_init
6. set_class
7. bind
8. override

9. new
10.call
11.response
12.ff
13.fr

16.set_class

17.retain
18.release

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

		//please do not include the "MCRuntime.h"
		//in protocol file!!!

		#ifdef METHOD 
		protocol(DrawableProtocol, draw, xxx);
		protocol(DrawableProtocol, erase, xxx);
		protocol(DrawableProtocol, redraw, xxx);
		#undef METHOD
		#endif

		#ifdef BIND
		bind(this, MT(draw), MA(DrawableProtocol, draw));
		bind(this, MT(erase), MA(DrawableProtocol, erase));
		bind(this, MT(redraw), MA(DrawableProtocol, redraw));
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

	
	method(Classname, name1, xxx)
	{
		printf("this is name1\n");
	}

	method(Classname, init, xxx)
	{
		if(set_class()){
			bind();
			#define BIND
			#include "xx.h"
		}
	}

it just give implements of the methods in protocol file. as you can guess it also can be **#include "xx.h"**
to our .c files. we use this to simulate some **inherit** and **Polymorphism** feature.

####method calling

it just like the Objective-C. sending message instead of function call.

	New(VTable, ret, nil);
	ff(ret, MT(show), YES, "this is a super method called by child:VTable");

####TODO list:

	1. implement the "__builtin_apply" extension on non-gcc platform
	   make the Mocha portable.

	2. wrap many popular C/UNIX libs:
	   time.h       ->  MCClock.h
	   pthread.h    ->  MCThread.h
	   string.h     ->  MCString.h
	   sys/socket.h ->  MCSocket.h
	   math.h       ->  MCMath.h

	3. a parse and some lightly added syntex to make the class define macros looks better

	4. test on clang-LLVM. make sure it can works on the newst technology

	5. method list in classobj should be read-only for instance

	6. more detailed "evolution" document.

	7. move more logic to MCObject

[^1]: the syntex is improving, maybe more/less keywords in the feature.

