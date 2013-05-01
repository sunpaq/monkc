
#compiler settings
CC86 = clang -O3 -fno-omit-frame-pointer -g -w -Wall -Wno-unused-variable -Wno-return-type
CCARM = clang -O3 -mapcs-frame -g -w -Wall -Wno-unused-variable -Wno-return-type

CC = $(CCARM)
AS = as

#asm object settings
ASM_IA32 = MCRuntimeAsm_IA32.o
ASM_IA32_darwin = MCRuntimeAsm_X8664_darwin.o
ASM_X8664 = MCRuntimeAsm_X8664.o
ASM_X8664_darwin = MCRuntimeAsm_X8664_darwin.o
ASM_ARM32 = MCRuntimeAsm_ARM32.o
ASM_ARM64 = MCRuntimeAsm_ARM64.o

ASM = $(ASM_ARM32)

#c object settings
LIBOBJS = Main.o Bird.o Bird_Engle.o BirdFather.o MCRuntime.o Hash.o Vectors.o Allocators.o Log.o Classpool.o

#default is IA-32 cpus
exec:$(LIBOBJS) $(ASM)
	$(CC) -o exec $(LIBOBJS) $(ASM)

#asm objects
MCRuntimeAsm_IA32.o:MCRuntimeAsm/MCRuntimeAsm_IA32.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_IA32.o MCRuntimeAsm/MCRuntimeAsm_IA32.s

MCRuntimeAsm_IA32_darwin.o:MCRuntimeAsm/MCRuntimeAsm_IA32_darwin.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_IA32_darwin.o MCRuntimeAsm/MCRuntimeAsm_IA32_darwin.s

MCRuntimeAsm_X8664.o:MCRuntimeAsm/MCRuntimeAsm_X8664.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_X8664.o MCRuntimeAsm/MCRuntimeAsm_X8664.s

MCRuntimeAsm_X8664_darwin.o:MCRuntimeAsm/MCRuntimeAsm_X8664_darwin.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_X8664_darwin.o MCRuntimeAsm/MCRuntimeAsm_X8664_darwin.s

MCRuntimeAsm_ARM32.o:MCRuntimeAsm/MCRuntimeAsm_ARM32.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_ARM32.o MCRuntimeAsm/MCRuntimeAsm_ARM32.s

MCRuntimeAsm_ARM64.o:MCRuntimeAsm/MCRuntimeAsm_ARM64.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_ARM64.o MCRuntimeAsm/MCRuntimeAsm_ARM64.s

#c objects
Main.o:Main.c
	$(CC) -c Main.c 

Bird.o:Bird.c Bird.h
	$(CC) -c Bird.c

Bird_Engle.o:Bird_Engle.c Bird_Engle.h
	$(CC) -c Bird_Engle.c

BirdFather.o:BirdFather.c BirdFather.h
	$(CC) -c BirdFather.c

MCRuntime.o:MCRuntime.c MCRuntime.h
	$(CC) -c MCRuntime.c

Hash.o:Hash.c MCRuntime.h
	$(CC) -c Hash.c

Vectors.o:Vectors.c Vectors.h
	$(CC) -c Vectors.c

Allocators.o:Allocators.c MCRuntime.h
	$(CC) -c Allocators.c

Log.o:Log.c Log.h
	$(CC) -c Log.c

#Classpool.o:Classpool.c MCRuntime.h
#	$(CC) -c Classpool.c

install:
	rm -f -r /usr/local/include/monkc
	rm -f /usr/local/lib/libmonkc.a
	tar -xzvf monkc.tar.gz -C /usr/local/include/
	mv /usr/local/include/monkc/*.a /usr/local/lib/

clean:
	rm -f $(LIBOBJS) MCRuntimeAsm*.o monkc.tar.gz core exec
	rm -f -r monkc

dump:
	ulimit -c unlimited
