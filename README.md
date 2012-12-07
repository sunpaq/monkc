# Mocha-R (Runtime based version)
a set of C macro for OOP programming

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)

## Overview

**Mocha**, is a set of C macros for OOP programming use pure C, the aim of Mocha is to add less syntex to support OOP. The reason to make this is as C is a language so beautiful and so powerful. and the OOP is so handful and nature for a programer. i want to mix them with the less modification

## Syntax
**Mocha** use "MC" as the prefix.
#### declear interface - write in .h file

  	MCInterface	( Classname, Supername );
			int var;
		MCInterfaceEnd( Classname, init, argument-list );
		method(Classname, bye, xxx);
		method(Classname, name1, arg-list);
		method(Classname, name2, arg-list);
	
#### implement methods - write in .c file

		method_imp(Classname, name1, arg-list)
		{
			This(Classname);
			this->var++;
		}
			
		method_imp(Classname, name2, arg-list)
		{
			This(Classname);
			this->var--;
		}
		
		method_imp(Classname, bye, xxx)
		{
			This(Classname);
			//do clean work
		}

		method_imp(Classname, init, argument-list )
		{
			This(Classname);
			setting_start(this, "Classname");
				New(Supername, super, argument-list);
				set_super(this, super);

				bind(this, MT(name1), MA(Classname, name1));
				bind(this, MT(name2), MA(Classname, name2));
				override(this, MT(super_method1), MA(Supername, super_method1));

			setting_end(this, MA(Classname, bye));
		}

####Macros and runtime functions

---
1.MCInterface( )
2.MCInterfaceEnd( )
3.method( )
4.method_imp( )
5.bind( )
6.override( )
7.set_super( )
8.This( )
9.setting_start( )
10.setting_end( )
11.response( )
12.ff( )
13.retain( )
14.release( )
15.id
16.xxx
17.nil
18.BOOL
19.Float
20.MCCast( )
21.MCCastEnd( )
22.protocol( )
23.protocol_imp( )
24.error_log( )
25.debug_log( )
25.runtime_log( )
---

Total **25** words.[^1]

####protocol file
	DrawableProtocol.h

		//please do not include the "MCRuntime.h"
		//in protocol file!!!

		#ifdef VAR
			char* main_color;
		#undef VAR
		#endif
		//----------------------------------------------------------
		#ifdef METHOD 
		protocol(DrawableProtocol, draw, xxx);
		protocol(DrawableProtocol, erase, xxx);
		protocol(DrawableProtocol, redraw, xxx);
		#undef METHOD
		#endif
		//-----------------------------------------------------------
		#ifdef IMPLEMENT
		MCCast(DrawableProtocol);
			char* main_color;
		MCCastEnd(DrawableProtocol);

		protocol_imp(DrawableProtocol, draw, xxx)
		{
			This(DrawableProtocol);
			this->main_color = "default-red";
			debug_log("%s:%s\n", "DrawableProtocol default draw", this->main_color);
		}
		protocol_imp(DrawableProtocol, erase, xxx)
		{
			This(DrawableProtocol);
			this->main_color = "default-yellow";
			debug_log("%s:%s\n", "DrawableProtocol default erase", this->main_color);
		}
		protocol_imp(DrawableProtocol, redraw, xxx)
		{
			This(DrawableProtocol);
			this->main_color = "default-blue";
			debug_log("%s:%s\n", "DrawableProtocol default redraw", this->main_color);
		}
		#undef IMPLEMENT
		#endif
		//----------------------------------------------------------
		#ifdef BIND
		bind(this, MT(draw), MA(DrawableProtocol, draw));
		bind(this, MT(erase), MA(DrawableProtocol, erase));
		bind(this, MT(redraw), MA(DrawableProtocol, redraw));
		#undef BIND
		#endif

######the VAR and METHOD part (include in .h file):

		#ifdef VAR
			char* main_color;
		#undef VAR
		#endif

		#ifdef METHOD 
		protocol(DrawableProtocol, draw, xxx);
		protocol(DrawableProtocol, erase, xxx);
		protocol(DrawableProtocol, redraw, xxx);
		#undef METHOD
		#endif

it just list the vars, which is just as decleard in the interface of a class.

the purpose of doing this is: we can use **#include "xx.h"** to import them direct in our class interface ! just like this:

	MCInterface	( Classname )
		int var;
		#define VAR
		#include "xx.h"
	MCInterfaceEnd( Classname, init, argument-list )
	#define METHOD
	#include "xx.h"
	method( Classname, name1, argument-list )
	
the result of doing this is amazing ! we have already have some feature called: "interface" or "abstract class"
in other OOP language.

######the IMPLEMENT and BIND part (include in .c file):

	
	method_imp(Classname, name1, xxx)
	{
		printf("this is name1\n");
	}
	#define IMPLEMENT
	#include "xx.h"

	method_imp(Classname, init, xxx)
	{
		setting_start();
			bind();
			#define BIND
			#include "xx.h"
		setting_end();
	}

it just give implements of the methods in protocol file. as you can guess it also can be **#include "xx.h"**
to our .c files. we use this to simulate some **inherit** and **Polymorphism** feature.

[^1]: the syntex is improving, maybe more/less keywords in the feature.

