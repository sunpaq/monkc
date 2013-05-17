ASM_IA32 = MCRuntimeAsm_IA32.o
ASM_X8664 = MCRuntimeAsm_X8664.o
ASM_ARM32 = MCRuntimeAsm_ARM32.o
ASM_ARM64 = MCRuntimeAsm_ARM64.o

LIBOBJS = MCRuntime.o Hash.o Vectors.o Allocators.o Log.o Classpool.o

CC = clang -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

#default is IA-32 cpus
all:$(LIBOBJS) $(ASM_IA32)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) $(ASM_IA32)
	tar -czvf monkc.tar.gz ./monkc/*

#cpu targets
ia32:$(LIBOBJS) $(ASM_IA32)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) $(ASM_IA32)
	tar -czvf monkc.tar.gz ./monkc/*

x8664:$(LIBOBJS) $(ASM_X8664)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) $(ASM_X8664)
	tar -czvf monkc.tar.gz ./monkc/*

arm32:$(LIBOBJS) $(ASM_ARM32)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) $(ASM_ARM32)
	tar -czvf monkc.tar.gz ./monkc/*

arm64:$(LIBOBJS) $(ASM_ARM64)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) $(ASM_ARM64)
	tar -czvf monkc.tar.gz ./monkc/*

#asm objects
MCRuntimeAsm_IA32.o:MCRuntimeAsm/MCRuntimeAsm_IA32.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_IA32.o MCRuntimeAsm/MCRuntimeAsm_IA32.s

MCRuntimeAsm_X8664.o:MCRuntimeAsm/MCRuntimeAsm_X8664.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_X8664.o MCRuntimeAsm/MCRuntimeAsm_X8664.s

MCRuntimeAsm_ARM32.o:MCRuntimeAsm/MCRuntimeAsm_ARM32.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_ARM32.o MCRuntimeAsm/MCRuntimeAsm_ARM32.s

MCRuntimeAsm_ARM64.o:MCRuntimeAsm/MCRuntimeAsm_ARM64.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_ARM64.o MCRuntimeAsm/MCRuntimeAsm_ARM64.s

#c objects
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

Classpool.o:Classpool.c MCRuntime.h
	$(CC) -c Classpool.c

install:
	rm -f -r /usr/local/include/monkc
	rm -f /usr/local/lib/libmonkc.a
	tar -xzvf monkc.tar.gz -C /usr/local/include/
	mv /usr/local/include/monkc/*.a /usr/local/lib/

clean:
	rm -f $(LIBOBJS) MCRuntimeAsm*.o monkc.tar.gz 
	rm -f -r monkc

dump:
	ulimit -c unlimited
