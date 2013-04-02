LIBOBJS = MCRuntimeAsm.o MCRuntime.o

CC = clang -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

all:$(LIBOBJS)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS)
	tar -czvf monkc.tar.gz ./monkc/*

MCRuntimeAsm.o:MCRuntimeAsm/MCRuntimeAsm_X8664.s MCRuntime.h
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_X8664.s

MCRuntime.o:MCRuntime.c MCRuntime.h
	$(CC) -c MCRuntime.c

install:
	tar -xzvf monkc.tar.gz -C /usr/local/include/
	mv /usr/local/include/monkc/*.a /usr/local/lib/

clean:
	rm -f $(LIBOBJS) monkc.tar.gz
	rm -r monkc

dump:
	ulimit -c unlimited
