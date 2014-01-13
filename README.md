# Monk-C
a toolkit for OOP programming in C language
[download source at github](https://github.com/sunpaq/OOP_MACROS/)

## Overview

**Monk-C**, is a toolkit for OOP programming use pure C. the aim of Monk-C is to support OOP in pure C with some tiny C macros, functions and even a light preprocessor. Monk-C is inspired by Apple Objective-C and gcc builtin "Constructing Calls". It is tiny and primitive but full of fun. I use it to play with my RaspberryPi and it really vary suitable for the ARM/Linux based embeded systems. It is open source under BSD license(3-clause license). I written it under the X86/Linux platform and X86/MacOS ARM/Linux is also fully tested and supportted both 32bit and 64bit.

#### supported platforms:

	[CPUArch/OS/Compiler]

	IA-32/Linux/gcc&clang    OK
	X86-64/Linux/gcc&clang 	 No Test
	IA-32/MacOS/gcc&clang 	 No Test
	X86-64/MacOS/gcc&clang   OK
	ARM32/Linux/gcc&clang    OK (RaspberryPi/Linux)
	ARM64/Linux/gcc&clang    No Test

#### easy way for Mac users (Xcode/intel x86_64):
###### Build a simple command line tool use MonkC:
	just use the Xcode project templete in /XcodeMonkC/MonkCAppXcodeTemplete/

###### Hack the monkc runtime system for your unique requirement:
	just check the Xcode project templete in /XcodeMonkC/MonkCStatic/

#### how to compile and install (command line):

	0. default is compile by gcc. make sure you have one installed. it also need flex
	   you can install flex by sudo apt-get install flex on Ubuntu
	   or install flex use macport on Mac OS X
	1. cd ./src
	2. sudo make install

	clang is recommand. cause it can output better error infomations
	change [ CC = gcc -> CC = clang ] in:
	1. /src/monkc_core_lib/Makefile 	-> line10 
	2. /src/monkc_core_lib/mcbuild 		-> line12
	3. /src/lemontea/Makefile			-> line9
	4. /src/tests/Makefile				-> line7
	to use clang as the compiler

	the command above will build the <libmonkc.a> <liblemontea.a>
	and copy them to 					/usr/local/lib/
	and copy the <.h> header files to 	/usr/local/include/
	and copy the <mcbuild> tool to 		/usr/local/bin/

#### how to create and build a monkc project:

	1. mkdir <your project dir>
	2. cd <your project dir> && mcbuild -create
	3. write code in the <your project dir/src> folder
	  (you can use any folder structure to organize your code)
	4. cd <your project dir> && mcbuild -build
	5. the output binary will be 'exec' in the project root dir
	  (see the examples folder for more details)

## Syntax
**Monk-C** use "MC" as the prefix.
#### main entry

	make sure you called all the code written by monkc
	between mc_init() and mc_end()
	it is better to put the mc_init() at the very beginning of main()
	and to put the mc_end() at the end of main()

	int main(int argc, char const *argv[])
	{
		mc_init();
			LOG_LEVEL = MC_VERBOSE;
			test_object_life_cycle();
		mc_end();
		return 0;
	}

	global log level:
	you can set the global variable LOG_LEVEL to:
	MC_SILENT		//no log outputed
	MC_ERROR_ONLY  //error log only
	MC_DEBUG 		//error log and debug log
	MC_VERBOSE     //error log and debug log and runtime log

	you can use:
	error_log()
	debug_log()
	runtime_log()
	to output logs. parameter is same as printf(char* fmt, ...)

#### declear interface - write in .h file

	#include "monkc.h" ---> must include
	#include "BirdFather.h"	 ---> super class

	#ifndef Bird_ ---> avoid multi-defines
	#define Bird_

	implements(Flyable); ---> protocol mark
	extends(BirdFather); ---> super class mark

	monkc(Bird); ---> class data begin
		char* name;
		int type;
	end(Bird); ---> class data end

	method(Bird, void, bye, xxx); ---> class public method list begin
	method(Bird, Bird*, initWithType, int type);
	method(Bird, void, fly, xxx);
	method(Bird, int, fatherAge, xxx); ---> class public method list end

	#endif ---> avoid multi-defines
	
#### implement methods - write in .c file
		
	#include "Bird.h"

	initer(Bird) ---> must have. initialize the class data
	{
		this->super = new(BirdFather); ---> new your super by hand!
		this->type = 3;
		debug_logt("Bird", "[%p] init called\n", this);
	}

	method(Bird, void, bye, xxx) ---> 1.public method implements
	{
		debug_logt(nameof(this), "[%p] bye called\n", this);
		recycle(this->super);
	}

	static void funcA(Bird* this, int arg1) ---> 2.private C function
	{
		debug_log("i am local function A\n");
	}

	protocol(Flyable, void, duckFly, xxx) ---> 3.protocol method you comply with
	{
		debug_log("%s\n", "Bird:Duck GuaGuaGua fly");
	}

	protocol(Flyable, void, chickenFly, xxx)		
	{
		debug_log("%s\n", "Bird:Chicken JiJiJi fly");
	}

	method(Bird, Bird*, initWithType, int type)
	{
		this->type = type;
		return this;
	}

	method(Bird, int, fatherAge, xxx)
	{
		int fage = cast(BirdFather, this->super)->age;
		debug_logt(nameof(this), "my father age is: %d\n", fage);
		return fage;
	}

	method(Bird, void, fly, xxx)
	{
		debug_log("Bird[%p->%p]: default fly type %d\n", this, this->super, this->type);
		funcA(this, 100);
	}

	loader(Bird) ---> must have. binding methods at runtime.
	{
		debug_logt(nameofc(class), "load called\n");
		#include "Flyable.p"

		binding(Bird, Bird*, initWithType, int type);
		binding(Bird, void, bye, xxx);
		binding(Bird, void, fly, xxx);
		binding(Bird, int, fatherAge, xxx);
	}

####method calling

	it just like the Objective-C. sending message instead of function call.

	Bird* bird = new(Bird);
	ff(bird, fly, nil);

####Macros and runtime functions

---

1. monkc
2. end
3. initer
4. loader
5. method
6. protocol
7. binding
8. override
9. new
10. call
11. ff
12. retain
13. release
14. recycle
15. shift
16. shift_back
17. this
18. cast
19. nameof
20. nameofc

---

Total **20** words.[^1]

####protocol file

	<Flyable.p>

	binding(Flyable, void, duckFly, xxx);
	binding(Flyable, void, chickenFly, xxx);


######the BIND part (include in .c file):

	loader(Bird)
	{
		debug_logt(class->name, "load called\n");
		#include "Flyable.p"

		binding(Bird, Bird*, initWithType, int type);
		binding(Bird, void, bye, xxx);
		binding(Bird, void, fly, xxx);
		binding(Bird, int, fatherAge, xxx);
	}


####TODO list:

	1. add type convert to preprocessor mcpp

	2. add auto binding to preprocessor mcpp

	3. add arg type check to preprocessor mcpp

	4. lemontea_WEB

	5. lemontea_GUI

	6. lemontea_3D

[^1]: the syntex is improving, maybe more/less keywords in the feature.

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)
