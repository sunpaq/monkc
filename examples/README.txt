HOW TO BUILD MONKC PROJECT IN COMMAND LINE

1."mcbuild" command line tool need be installed

2."mcbuild -c(--create)"
  will create an /build and an /src folder
  place an Makefile into /build folder

3.copy all the code in /source_code into /src
  you can orgnized them in any folder structure you want

4."mcbuild -s(--sync)" 
  will copy all the source files in /src 
  into /build folder. prehash all the method name
  into numbers. prepare the "automatic build Makefile"

5."make -C build" (gmake on FreeBSD)
  the make tool will make the code under /build folder

6."./build/exec"
  run your binary