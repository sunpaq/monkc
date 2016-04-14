# Monk-C
a toolkit for OOP programming in C language

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)

## Overview

**Monk-C**, is a toolkit for OOP programming use pure C (static library). the aim of Monk-C is to support OOP in pure C with some tiny C macros, functions and even a light preprocessor (optional). Monk-C is inspired by Apple Objective-C and gcc builtin "Constructing Calls". It is tiny and primitive but full of fun. I use it to play with my RaspberryPi and it really vary suitable for the ARM/Linux based embeded systems. It is open source under **BSD** license(3-clause license).

###### Monk-C is based on **C99** standard
###### No stable version released now. but the syntax is nearly ready to be fixed.
###### I am focusing on X86_64 and ARM64 CPUs. (see the list on bottom of this page)

## Please check the latest version here (in MCSource folder)
	
	https://github.com/sunpaq/monkc4iOS

## Documents:

###### 1 [wiki page](https://github.com/sunpaq/monkc/wiki) on github
###### 2 [PDF doc](https://github.com/sunpaq/monkc/tree/master/doc) (on writing)
###### 3 Infos at this page

## Play with Monk-C use IDEs (template project):

the iOS version is latest 2.0:

[1 iOS     - Xcode on MacOS](https://github.com/sunpaq/monkc4iOS)

other version will be ported later:

[2 Android - Eclipse on Linux/Windows](https://github.com/sunpaq/monkc4Android)

[3 Linux   - Eclipse on Linux](https://github.com/sunpaq/monkc4Linux)

[4 Mac     - Xcode on MacOS](https://github.com/sunpaq/monkc4Mac)

[5 Win32   - Eclipse on Windows](https://github.com/sunpaq/monkc4Win32)

## Syntax

**Monk-C** use "MC" as the prefix.

#### Header file

	#ifndef _MCCamera
	#define _MCCamera

	#include "monkc.h"
	#include "MC3DBase.h"
	#include "MC3DNode.h"

	class(MCCamera, MC3DNode,
	    double ratio;
	    double focal_length;
	    double view_angle;
	    double max_distance;
	    MCVector3 lookat;
	    MCMatrix4 projectionMatrix;
	    MCMatrix4 modelViewMatrix;
	    //world coordinate
	    MCVector3 currentPosition;
	    //local spherical coordinate
	    //R[0,unlimited) tht[0, 180.0), fai[0, 360.0)
	    double R;
	    double tht;
	    double fai;
	    
	    computing(MCMatrix4, mvproj);
	    computing(MCMatrix3, normal);
	);

	method(MCCamera, MCCamera*, initWithWidthHeight, unsigned width, unsigned height);
	method(MCCamera, void, move, double deltaFai, double deltaTht);
	method(MCCamera, void, reset, voida);
	method(MCCamera, void, update, MCGLContext* ctx);//override

	#define MCLensStandard50mm (0.050)
	#define MCLensWide24mm     (0.024)
	#define MCLensLong100mm    (0.100)
	#define MCLensLong200mm    (0.200)

	#define MCRatioCameraFilm3x2    (3.0/2.0)
	#define MCRatioOldTV4x3         (4.0/3.0)
	#define MCRatioHDTV16x9         (16.0/9.0)
	#define MCRatioCinema239x100    (2.39/1.0)
	#define MCRatioMake(w, h)       ((double)w / (double)h)

	#define MCLensStandard50mmViewAngle (45.0)
	#endif

#### C file

	#include "MCCamera.h"

	compute(MCMatrix4, mvproj);
	compute(MCMatrix3, normal);

	oninit(MCCamera)
	{
	    if (init(MCObject)) {
	        var(ratio) = MCRatioHDTV16x9;//MCRatioCameraFilm3x2;
	        var(focal_length) = MCLensWide24mm;//MCLensStandard50mm;
	        var(view_angle) = MCLensStandard50mmViewAngle;
	        var(max_distance) = 100;//100 metres
	        var(lookat) = MCVector3Make(0,0,0);
	        var(projectionMatrix) = MCMatrix4Identity();
	        var(modelViewMatrix) = MCMatrix4Identity();
	        //world coordinate
	        var(currentPosition) = MCVector3Make(0, 0, 0);
	        //local spherical coordinate
	        var(R) = 100;
	        var(tht) = 60;
	        var(fai) = 45;
	        
	        var(mvproj) = mvproj;
	        var(normal) = normal;
	        return obj;
	    }else{
	        return mull;
	    }
	}

	compute(MCMatrix4, mvproj)
	{
	    varscope(MCCamera);
	    MCMatrix4 mvp = MCMatrix4Multiply(var(projectionMatrix), var(modelViewMatrix));
	    return mvp;
	}

	compute(MCMatrix3, normal)
	{
	    varscope(MCCamera);
	    MCMatrix3 nor = MCMatrix3InvertAndTranspose((MCMatrix3)MCMatrix4GetMatrix3(obj->modelViewMatrix), NULL);
	    return nor;
	}

	method(MCCamera, MCCamera*, initWithWidthHeight, unsigned width, unsigned height)
	{
	    //setting camera
	    obj->ratio = MCRatioMake(width, height);
	    obj->R = 5;
	    return obj;
	}

	method(MCCamera, void, reset, voida)
	{
	    init(MCCamera);
	}

	function(void, updatePosition, MCVector3* result)
	{
	    varscope(MCCamera);
	    var(currentPosition) = MCWorldCoorFromLocal(MCVertexFromSpherical(var(R), var(tht), var(fai)), var(lookat));
	    if (result != mull) {
	        result->x = var(currentPosition).x;
	        result->y = var(currentPosition).x;
	        result->z = var(currentPosition).x;
	    }
	}

	function(void, updateRatioFocalDistance, voida)
	{
	    varscope(MCCamera);
	    var(projectionMatrix) = MCMatrix4MakePerspective(MCDegreesToRadians(obj->view_angle),
	                                                     var(ratio),
	                                                     var(focal_length),
	                                                     var(max_distance));
	}

	function(void, updateLookat, voida)
	{
	    varscope(MCCamera);
	    MCVector3 modelpos = var(lookat);
	    MCVector3 eyelocal = MCVertexFromSpherical(var(R), var(tht), var(fai));
	    MCVector3 eye = MCWorldCoorFromLocal(eyelocal, modelpos);
	    
	    if (var(tht) < 90.0) {
	        MCVector3 Npole = MCVector3Make(0, var(R)/MCCosDegrees(var(tht)), 0);
	        var(modelViewMatrix) = MCMatrix4MakeLookAt(eye.x, eye.y, eye.z,
	                                                   modelpos.x, modelpos.y, modelpos.z,
	                                                   Npole.x-eye.x, Npole.y-eye.y, Npole.z-eye.z);
	    }
	    if (var(tht) > 90.0) {
	        MCVector3 Spole = MCVector3Make(0, -var(R)/MCCosDegrees(180.0-var(tht)), 0);
	        var(modelViewMatrix) = MCMatrix4MakeLookAt(eye.x, eye.y, eye.z,
	                                                   modelpos.x, modelpos.y, modelpos.z,
	                                                   eye.x-Spole.x, eye.y-Spole.y, eye.z-Spole.z);
	    }
	    if (var(tht) == 90.0) {
	        var(modelViewMatrix) = MCMatrix4MakeLookAt(eye.x, eye.y, eye.z,
	                                                   modelpos.x, modelpos.y, modelpos.z, 0, 1, 0);
	    }
	}

	//override
	method(MCCamera, void, update, MCGLContext* ctx)
	{
	    updateRatioFocalDistance(0, obj, 0);
	    updatePosition(0, obj, mull);
	    updateLookat(0, obj, 0);
	    
	    MCGLContext_setUniformMatrix4(0, ctx, "modelViewProjectionMatrix", cvar(mvproj).m);
	    MCGLContext_setUniformMatrix3(0, ctx, "normalMatrix", cvar(normal).m);
	}

	method(MCCamera, void, move, double deltaFai, double deltaTht)
	{
	    obj->fai = obj->fai + deltaFai;   //Left
	    obj->tht = obj->tht + deltaTht;   //Up
	    //camera->fai = camera->fai - 0.1; //Right
	    //camera->tht = camera->tht - 0.1; //Down
	    
	    updateLookat(0, obj, 0);
	}

	onload(MCCamera)
	{
	    if (load(MCObject)) {
	        mixing(void, updatePosition, MCVertex* result);
	        mixing(void, updateRatioFocalDistance);
	        mixing(void, updateLookat);
	        
	        binding(MCCamera, void, reset, MCBool updateOrNot);
	        binding(MCCamera, void, update);
	        return cla;
	    }else{
	        return mull;
	    }
	}

#### Dynamically calling method

	it just like the Objective-C. sending message instead of function call.

	Bird* bird = new(Bird);
	ff(bird, fly, 0);

#### Statically calling method
	
	C style: 	Bird_fly(0, bird, 0);

#### Builtin Log

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
16. voida & mull

---

Total only **16** words.[^1]

## Hack the MonkC runtime on UNIX-like system use command line tools

#### recomand code editor:
	Sublime Text
	Atom
	Vim/Emacs (with plugins)
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

##TODO list:

	1. add type check/convert to preprocessor mcpp

	2. add auto binding to preprocessor mcpp

	3. add memory leak detector to preprocessor mcpp

	4. lemontea_WEB

	5. lemontea_GUI

	6. lemontea_3D

[^1]: the syntex is improving, maybe more/less keywords in the future.
