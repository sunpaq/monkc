# Mocha

a set of C macro for OOP programming (Runtime based version)

[download source code from github](https://github.com/sunpaq/OOP_MACROS)


### Overview

**Mocha**, is a set of C macros for OOP programming use pure C, the aim of Mocha is to add less syntex to support OOP. The reason to make this is as C is a language so beautiful and so powerful. and the OOP is so handful and nature for a programer. i want to mix them with the less modification

### Install
1. download the source tarball and extract it.
2. open a terminal and "cd" to the source folder.
3. "cd" to the "mocha_core_lib" folder and "make"
4. "sudo make install" this will install the libmocha.a static library on your system /usr/local/bin/ and /usr/local/include/

### Run some example
1. in the source root folder "make" this will build a executable called "exec"
2. "./exec" will run it

### Syntax
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
		
		constructor( Classname, argument-list )
		{
			link_class(Classname, Supername, super-argument-list)
			{
				have_method(Classname, bye, xxx);
				have_method(Classname, name1, arg-list);
				have_method(Classname, name2, arg-list);
			}
			
			return this;
		}
		
		method(Classname, name1, arg-list) retuens(BOOL)
		{
			this->var++;
			return YES;
		}
			
		method(Classname, name2, arg-list)
		{
			this->var--;
		}
		
		method(Classname, bye, xxx)
		{
			//do clean work
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
10. call
11. response
12. ff
13. fr
16. set_class
17. retain
18. release
19. id
20. xxx
21. nil
22. BOOL
23. String
24. Float
25. MV
26. MK
27. Handle
28. protocol
29. This
30. Cast

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
		have_method(DrawableProtocol, draw, xxx);
		have_method(DrawableProtocol, erase, xxx);
		have_method(DrawableProtocol, redraw, xxx);
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

	constructor( Classname, argument-list )
	{
		link_class(Classname, Supername, super-argument-list)
		{
			have_method(Classname, bye, xxx);
			have_method(Classname, name1, arg-list);
			have_method(Classname, name2, arg-list);
		}
	}
	
	method(Classname, name1, xxx)
	{
		printf("this is name1\n");
	}

it just give implements of the methods in protocol file. as you can guess it also can be **#include "xx.h"**
to our .c files. we use this to simulate some **inherit** and **Polymorphism** feature.

####method calling

it just like the Objective-C. sending message instead of function call.

	mc_init();
	
	VTable* ret = new(VTable, nil);
	ff(ret, MK(show), YES, "this is a super method called by child:VTable");
	
	mc_end();

###TODO list:

	1. implement the "__builtin_apply" extension on non-gcc platform
	   make the Mocha portable.

	2. wrap many popular C/UNIX libs:
	   time.h       ->  MCClock.h
	   pthread.h    ->  MCThread.h
	   string.h     ->  MCString.h
	   sys/socket.h ->  MCSocket.h
	   math.h       ->  MCMath.h

	3. a parser and some lightly added syntex to make the class define macros looks better

	4. test on clang-LLVM. make sure it can works on the newst technology

	5. method list in classobj should be read-only for instance

	6. more detailed "evolution" document.

	7. move more logic to MCObject
	
	
![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=140&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)

[^1]: the syntex is improving, maybe more/less keywords in the future.


