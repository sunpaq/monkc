INCPATH=/usr/local/include/
LIBPATH=/usr/local/lib/

SRCS=$(wildcard *.c)
LIBOBJS=$(patsubst %.c, %.o, $(SRCS))
ARCH=$(strip $(shell uname -m))
OS=$(strip $(shell uname -s))

#-w -Wno-unused-variable -Wno-return-type
CC=clang -g -Wall
AS=as

ASMFILE=MCRuntimeAsm_IA32.asm
ifeq ($(ARCH),x86_64)
ifeq ($(OS),Darwin)
	ASMFILE=MCRuntimeAsm_X8664_darwin.asm
endif
endif
ifeq ($(ARCH),i386)
ifeq ($(OS),Darwin)
	ASMFILE=MCRuntimeAsm_IA32_darwin.asm
endif
endif
ifeq ($(ARCH),i686)
ifeq ($(OS),Darwin)
	ASMFILE=MCRuntimeAsm_IA32_darwin.asm
endif
endif
ifeq ($(ARCH),x86_64)
ifeq ($(OS),Linux)
	ASMFILE=MCRuntimeAsm_X8664.asm
endif
endif
ifeq ($(ARCH),amd64)
ifeq ($(OS),FreeBSD)
	ASMFILE=MCRuntimeAsm_X8664.asm
endif
endif
ifeq ($(ARCH),i386)
ifeq ($(OS),Linux)
	ASMFILE=MCRuntimeAsm_IA32.asm
endif
endif
ifeq ($(ARCH),i686)
ifeq ($(OS),Linux)
	ASMFILE=MCRuntimeAsm_IA32.asm
endif
endif
ifeq ($(ARCH),armv6l)
	ASMFILE=MCRuntimeAsm_ARM32.asm
endif
#TODO
ifeq ($(ARCH),armv9)
	ASMFILE=MCRuntimeAsm_ARM64.asm
endif

#default is IA-32 cpus
all:$(LIBOBJS) MCRuntimeAsm.o
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) MCRuntimeAsm.o
	tar -czvf monkc.tar.gz ./monkc/*

MCRuntimeAsm.o:
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/$(ASMFILE)

#general target
%.o:%.c
	$(CC) -c $<

install:
	mkdir -p $(INCPATH)
	mkdir -p $(LIBPATH)
	rm -f -r $(INCPATH)monkc
	rm -f $(LIBPATH)libmonkc.a
	tar -xzvf monkc.tar.gz -C $(INCPATH)
	mv $(INCPATH)monkc/*.a $(LIBPATH)

clean:
	rm -f $(LIBOBJS) MCRuntimeAsm.o monkc.tar.gz 
	rm -f -r monkc
	rm -f *.o

dump:
	ulimit -c unlimited
