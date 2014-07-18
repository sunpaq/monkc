# Monk-C
a toolkit for OOP programming in C language

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)

## Overview

**Monk-C**, is a toolkit for OOP programming use pure C (static library). the aim of Monk-C is to support OOP in pure C with some tiny C macros, functions and even a light preprocessor (optional). Monk-C is inspired by Apple Objective-C and gcc builtin "Constructing Calls". It is tiny and primitive but full of fun. I use it to play with my RaspberryPi and it really vary suitable for the ARM/Linux based embeded systems. It is open source under **BSD** license(3-clause license). I written it under the X86/Linux platform and X86/MacOS ARM/Linux is also fully tested and supportted both 32bit and 64bit.

###### Monk-C is based on **C99** standard
###### No stable version released now, developing commit: 0.1.140223

## Supported platforms:

	[CPUArch/OS/Compiler]

	IA-32/FreeBSD/clang                         On Working
	IA-32/Linux/gcc&clang    					OK
	IA-32/MacOS/gcc&clang 	 					No Test
	IA-32/Windows7(MinGW-32bit)/mingw-gcc		OK

	X86-64/FreeBSD/clang                        OK
	X86-64/Linux/gcc&clang 	 					OK
	X86-64/MacOS/gcc&clang   					OK
	X86-64/Windows7(MinGW-32bit)/mingw-gcc		OK

	ARM32/FreeBSD/clang                         On Working (RaspberryPi)
	ARM32/Linux/gcc&clang    					OK (RaspberryPi/Debian)
	ARM32/iOS/clang								OK
	ARM32/Android/clang							OK (NDK build)

	ARM64/Linux/gcc&clang    					On Working
	ARM64/iOS/clang								On Working

	PowerPC64/FreeBSD/clang                     On Working (iMac G5)

## Documents:

###### 1 [wiki page](https://github.com/sunpaq/monkc/wiki) on github
###### 2 [PDF doc](https://github.com/sunpaq/monkc/tree/master/doc) (on writing)
###### 3 Infos at this page

## Play with MonkC use IDEs (template project):

	1. Xcode   			(MacOS)
	2. Eclipse 			(Linux/Windows)
	3. VisualStudio12 	(Windows)

[Android](https://github.com/sunpaq/monkc4Android)
[iOS](https://github.com/sunpaq/monkc4iOS)
[Linux](https://github.com/sunpaq/monkc4Linux)
[Mac](https://github.com/sunpaq/monkc4Mac)
[Win32](https://github.com/sunpaq/monkc4Win32)

	i usurally develop MonkC on Mac OS use Xcode
	so the Mac version will be the latest one.

## Syntax

**Monk-C** use "MC" as the prefix.


#### declear interface - write in .h file

	#include "monkc.h"
	#include "BirdFather.h"

	//avoid multi-defines
	#ifndef Bird_
	#define Bird_

	//class define
	monkc(Bird);
		char* name;
		int type;
	end(Bird);

	//methods define
	method(Bird, void, bye, xxx);
	method(Bird, Bird*, initWithType, int type);
	method(Bird, void, fly, xxx);
	method(Bird, int, fatherAge, xxx);

	#endif
	
####protocol file (Flyable.p)

	binding(Flyable, void, duckFly, xxx);
	binding(Flyable, void, chickenFly, xxx);

#### implement methods - write in .c file
		
	#include "Bird.h"

	//called by runtime, initialize the class data
	initer(Bird)
	{
		//new your super by hand!
		obj->super = new(BirdFather);
		obj->type = 3;
		debug_logt("Bird", "[%p] init called\n", obj);
		return obj;
	}

	//public method implements
	method(Bird, void, bye, xxx)
	{
		debug_logt(nameof(obj), "[%p] bye called\n", obj);
		recycle(obj->super);
	}

	//private C function
	static void funcA(Bird* obj, int arg1)
	{
		debug_log("i am local function A\n");
	}

	//protocol you comply with
	protocol(Flyable, void, duckFly, xxx)
	{
		debug_log("%s\n", "Bird:Duck GuaGuaGua fly");
	}

	protocol(Flyable, void, chickenFly, xxx)		
	{
		debug_log("%s\n", "Bird:Chicken JiJiJi fly");
	}

	method(Bird, Bird*, initWithType, int type)
	{
		obj->type = type;
		return obj;
	}

	method(Bird, int, fatherAge, xxx)
	{
		int fage = cast(BirdFather, obj->super)->age;
		debug_logt(nameof(obj), "my father age is: %d\n", fage);
		return fage;
	}

	method(Bird, void, fly, xxx)
	{
		debug_log("Bird[%p->%p]: default fly type %d\n", obj, obj->super, obj->type);
		funcA(obj, 100);
	}

	//must have. binding methods at runtime.
	loader(Bird)
	{
		debug_logt(nameofc(class), "load called\n");

		//protocol itself is just a header file
		#include "Flyable.p"

		//DO NOT WRITE THEM BY HAND!
		//YOU CAN COPY ALL THE METHODS DECLEARED IN HEADER FILE
		//AND CHANGE "method->binding"

		binding(Bird, Bird*, initWithType, int type);
		binding(Bird, void, bye, xxx);
		binding(Bird, void, fly, xxx);
		binding(Bird, int, fatherAge, xxx);
		return claz;
	}

####Dynamically calling method

	it just like the Objective-C. sending message instead of function call.

	Bird* bird = new(Bird);
	ff(bird, fly, nil);

####Statically calling method
	
	C style: 	Bird_fly(bird, 0, fly, nil);
	Macro:		call(bird, Bird, fly, nil);

#### main entry

	int main(int argc, char const *argv[])
	{
		LOG_LEVEL = MC_VERBOSE;
		//your code here
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

####Macros and runtime functions often used

---

1. monkc
2. end
3. initer
4. loader
5. method
6. protocol
7. binding
8. new
9. call
10. ff
11. retain
12. release
13. recycle
14. obj
15. claz
16. xxx

---

Total only **16** words.[^1]

## Hack the MonkC runtime on UNIX-like system use command line tools

#### recomand code editor:
	Sublime Text 
	(you can use any editor. but some one have auto-complete function will help a lot)

#### need these tools:
    gmake - this is needed on FreeBSD
            i am trying to write a generic makefile for both
            make and GNU make. but for now. please alias your
            make to gmake.
	clang - I strongly recommand use this C compiler. 
	        because i found it can report more detailed error infomations
	flex - this is needed to build the 'mcpp' preprocessor for monkc

#### how to compile and install (command line):

	0. default is compile by 'clang'. make sure you have one installed. 
	   it also need 'flex'. you can install flex by 'sudo apt-get install flex' on Ubuntu
	   or install flex use macport on Mac OS X
	1. cd ./src
	2. sudo make install

	clang is recommand. cause it can output better error infomations
	if you want change it to gcc
	change [ CC = clang -> CC = gcc ] in:
	1. /src/monkc_runtime/Makefile 	    -> line10 
	2. /src/monkc_buildtool/mcbuild     -> line12
	3. /src/lemontea/Makefile			-> line9
	4. /src/tests/Makefile				-> line7
	to use gcc as the compiler

	the command above will build the <libmonkc.a> <liblemontea.a>
	and automatically copy them to 				/usr/local/lib/
	and copy the <.h> header files to 			/usr/local/include/
	and copy the <mcpp> <mcbuild> tool to 		/usr/local/bin/

#### how to create and build a monkc project:

	1. mkdir <your project dir>
	2. cd <your project dir> && mcbuild -create
	3. write code in the <your project dir/src> folder
	  (you can use any folder structure to organize your code)
	4. cd <your project dir> && mcbuild -sync
	5. cd <your project dir>/build && make
	   the output binary will be 'exec' in the build folder
	  (see the examples folder for more details)

##For more infomation please goto [wiki page](https://github.com/sunpaq/monkc/wiki) on github

##TODO list:

	1. add type convert to preprocessor mcpp

	2. add auto binding to preprocessor mcpp

	3. add arg type check to preprocessor mcpp

	4. lemontea_WEB

	5. lemontea_GUI

	6. lemontea_3D

[^1]: the syntex is improving, maybe more/less keywords in the future.
