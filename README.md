# Monk-C (Runtime based version)
a toolkit for OOP programming in C language

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

	#include "MCRuntime.h"
	#include "BirdFather.h"

	#ifndef Bird_
	#define Bird_

	implements(Flyable);
	extends(BirdFather);

	class(Bird);
		char* name;
		int type;
	end(Bird);

	method(Bird, bye, xxx);
	method(Bird, initWithType, int type);
	method(Bird, fly, xxx);
	method(Bird, fatherAge, xxx);

	#endif
	
#### implement methods - write in .c file
		
	#include "Bird.h"

	initer(Bird)
	{
		this->super = new(BirdFather);
		this->type = 3;
		debug_logt("Bird", "[%p] init called\n", this);
	}

	method(Bird, bye, xxx)
	{
		debug_logt(this->isa->name, "[%p] bye called\n", this);

		release(this->super);
	}

	void funcA(Bird* this, int arg1)
	{
		debug_log("i am local function A\n");
	}

	protocol(Flyable, duckFly, xxx)
	{
		debug_log("%s\n", "Bird:Duck GuaGuaGua fly");
	}

	protocol(Flyable, chickenFly, xxx)
	{
		debug_log("%s\n", "Bird:Chicken JiJiJi fly");
	}

	method(Bird, initWithType, int type)
	{
		this->type = type;
		return this;
	}

	method(Bird, fatherAge, xxx)
	{
		debug_logt(this->isa->name, "my father age is: %d\n", Cast(BirdFather, this->super)->age);
	}

	method(Bird, fly, xxx)
	{
		debug_log("Bird[%p->%p]: default fly type %d\n", this, this->super, this->type);
		funcA(this, 100);
	}

	loader(Bird)
	{
		debug_logt(class->name, "load called\n");
		#include "Flyable.p"

		binding(Bird, initWithType, int type);
		binding(Bird, bye, xxx);
		binding(Bird, fly, xxx);
		binding(Bird, fatherAge, xxx);
	}

####method calling

	it just like the Objective-C. sending message instead of function call.

	Bird* bird = new(Bird);
	ff(bird, fly, nil);

####Macros and runtime functions

---

1. class
2. end
3. initer
4. loader
5. method
6. protocol

7. binding
8. override

9. new
10.call
11.ff

12.retain
13.release
14.relnil

15.shift
16.shift_back

17. This
18. Cast

---

Total **33** words.[^1]

####protocol file

	<Flyable.p>

	binding(Flyable, duckFly, xxx);
	binding(Flyable, chickenFly, xxx);


######the BIND part (include in .c file):

	loader(Bird)
	{
		debug_logt(class->name, "load called\n");
		#include "Flyable.p"

		binding(Bird, initWithType, int type);
		binding(Bird, bye, xxx);
		binding(Bird, fly, xxx);
		binding(Bird, fatherAge, xxx);
	}


####TODO list:

	1. more test use MCUnitTest framework.

	2. test runtime on arm/linux platform.

	3. a parser and some lightly added syntex to make the class define macros looks better

	4. method list in classobj should be read-only for instance
	(allow add method only)

	5. more detailed document.

	6. move more logic to MCObject

[^1]: the syntex is improving, maybe more/less keywords in the feature.

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)
