# Monk-C
a toolkit for OOP programming in C language

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)

## Overview

**Monk-C**, is a toolkit for OOP programming use pure C (static library). the aim of Monk-C is to support OOP in pure C with some tiny C macros, functions and even a light preprocessor (optional). Monk-C is inspired by Apple Objective-C and gcc builtin "Constructing Calls". It is tiny and primitive but full of fun. I use it to play with my RaspberryPi and it really vary suitable for the ARM/Linux based embeded systems. It is open source under **BSD** license(3-clause license).

###### Monk-C is based on **C99** standard
###### No stable version released now. but the syntax is nearly ready to be fixed.
###### I am focusing on X86_64 and ARM64 CPUs.

## Documents:

###### 1 [wiki page](https://github.com/sunpaq/monkc/wiki) on github
###### 2 Infos at this page

## Use Monk-C on iOS

[Library via Cocoapods](https://github.com/sunpaq/monkc-pod)

[Demo App](https://github.com/sunpaq/monkc4iOS)

## The BohdiEngine (3D) written use Monk-C:

[iOS version via Cocoapods](https://github.com/sunpaq/BohdiEngine-pod)

[Android version](https://github.com/sunpaq/monkc4Android)

## The BohdiAR written use Monk-C:

[https://github.com/sunpaq/BohdiAR-pod](https://github.com/sunpaq/BohdiAR-pod)

## The Demo Google Cardboard VR App using BohdiEngine:

[https://github.com/sunpaq/BohdiEngineDemoSwift](https://github.com/sunpaq/BohdiEngineDemoSwift)

## Monk-C on Windows (64bit):

in 'platforms/windows' folder of this repo, there have a Visual Studio Solution 'monkc.sln'
you can build 'monkc.lib' using it. the binary and header will copy into 'output' folder

here is a demo using the 'monkc.lib' in other Visual Studio Solution
the binary and header placed into its 'libs' folder
[https://github.com/sunpaq/monkc4win64](https://github.com/sunpaq/monkc4win64)

## Monk-C on UNIX(Mac & Linux) via command line tools (this repo):

#### requires

	clang/gcc
	git
	ruby
	
#### install build tool

	sudo gem install mcbuild
	
#### build & run

	./build.rb all
	./build.rb run 

#### install snippets for sublime text

	1.[SublimeText Menu -> Preferences -> Browse Packages...] open the plugin folder
	2.copy the 'mcsublime-snippets' folder into 'User' 

## The MCBuild tool:

MCBuild is a script library written use Ruby. Helping C/Monk-C developr generate Makefile.
[https://github.com/sunpaq/mcbuild](https://github.com/sunpaq/mcbuild)

## Syntax

**Monk-C** use "MC" as the prefix.

#### Header file

    #include "monkc.h"

	class(MCSort, MCObject,
	      MCGeneric* array;
	      size_t length);

	method(MCSort, void, bye, voida);
	method(MCSort, MCSort*, initWithArray, MCGeneric* array, size_t length);
	method(MCSort, void, insertionSort, voida);
	method(MCSort, void, quickSort, voida);
	method(MCSort, void, printArray, voida);

#### C file

    #include "MCSort.h"

	oninit(MCSort)
	{
	    if (init(MCObject)) {
	        var(array) = null;
	        var(length) = 0;
	        return obj;
	    }else{
	        return null;
	    }
	}

	method(MCSort, void, bye, voida)
	{
	    if (obj->array && obj->length > 0) {
	        free(obj->array);
	    }
	}

	method(MCSort, MCSort*, initWithArray, MCGeneric* array, size_t length)
	{
	    var(array) = (MCGeneric*)malloc(sizeof(MCGeneric) * length);
	    for (size_t i=0; i<length; i++) {
	        obj->array[i] = array[i];
	    }
	    var(length) = length;
	    //debug
	    //ff(obj, printArray, 0);
	    return obj;
	}

	function(void, swap, size_t a, size_t b)
	{
	    as(MCSort);
	    if (a < b) {
	        MCGeneric t = obj->array[a];
	        obj->array[a] = obj->array[b];
	        obj->array[b] = t;
	    }
	}

	method(MCSort, void, insertionSort, voida)
	{
	    
	}

	function(void, quicksort, const size_t l, const size_t r)
	{
	    as(MCSort);
	    if (l >= r || l > obj->length || r > obj->length) {
	        //debug_log("quicksort exit l=%ld r=%ld\n", l, r);
	        return;
	    }
	    MCGeneric pivot = obj->array[l];
	    size_t cur=l;
	    for (size_t idx=l+1; idx<=r; idx++) {
	        if (MCGenericCompare(obj->array[idx], pivot) < 0)
	            swap(obj, ++cur, idx);
	    }
	    
	    swap(obj, l, cur);
	    quicksort(obj, l, cur-1);
	    quicksort(obj, cur+1, r);
	}

	method(MCSort, void, quickSort, voida)
	{
	    quicksort(obj, 0, var(length)-1);
	}

	method(MCSort, void, printArray, voida)
	{
	    for (size_t i=0; i<obj->length; i++) {
	        printf("element of array[%ld]=%.2f\n", i, obj->array[i].mcfloat);
	    }
	}

	onload(MCSort)
	{
	    if (load(MCObject)) {
	        binding(MCSort, void, bye, voida);
	        binding(MCSort, MCSort*, initWithArray, MCGeneric* array, size_t length);
	        binding(MCSort, void, insertionSort, voida);
	        binding(MCSort, void, quickSort, voida);
	        binding(MCSort, void, printArray, voida);
	        return cla;
	    }else{
	        return null;
	    }
	}

#### Dynamically calling method

	it just like the Objective-C. sending message instead of function call.

	Bird* bird = new(Bird);
	ff(bird, fly, 0);

#### Statically calling method
	
	C style: 	Bird_fly(bird, 0);

#### Macros and runtime functions often used

---

1. class
2. method   (binding)
3. function (mixing)
4. compute  (computing)
5. utility
6. var
7. new
8. ff
9. oninit (init)
10. onload (load)
11. retain
12. release
13. recycle
14. obj
15. cla
16. voida & null

---

Total only **16** words.[^1]

[^1]: the syntex is improving, maybe more/less keywords in the future.
