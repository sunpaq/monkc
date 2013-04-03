LIBOBJS = MCRuntimeAsm.o MCRuntime.o \
	Hash.o Vectors.o Allocators.o Log.o Classpool.o

CC = clang -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

all:$(LIBOBJS)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS)
	tar -czvf monkc.tar.gz ./monkc/*

MCRuntimeAsm.o:MCRuntimeAsm/MCRuntimeAsm_IA32.s MCRuntime.h
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32.s

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
	tar -xzvf monkc.tar.gz -C /usr/local/include/
	mv /usr/local/include/monkc/*.a /usr/local/lib/

clean:
	rm -f $(LIBOBJS) monkc.tar.gz -r monkc

dump:
	ulimit -c unlimited