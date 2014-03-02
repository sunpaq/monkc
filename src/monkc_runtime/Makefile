INCPATH = /usr/local/include/
LIBPATH = /usr/local/lib/

SRCS = $(wildcard *.c)
LIBOBJS = $(patsubst %.c, %.o, $(SRCS))
ARCH = $(strip $(shell uname -m))
OS = $(strip $(shell uname -s))

CC = clang -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

#default is IA-32 cpus
all:$(LIBOBJS) MCRuntimeAsm.o
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) MCRuntimeAsm.o
	tar -czvf monkc.tar.gz ./monkc/*

MCRuntimeAsm.o:
ifeq ($(ARCH),x86_64)
ifeq ($(OS),Darwin)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_X8664_darwin.asm
endif
endif
ifeq ($(ARCH),i386)
ifeq ($(OS),Darwin)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32_darwin.asm
endif
endif
ifeq ($(ARCH),i686)
ifeq ($(OS),Darwin)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32_darwin.asm
endif
endif
ifeq ($(ARCH),x86_64)
ifeq ($(OS),Linux)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_X8664.asm
endif
endif
ifeq ($(ARCH),amd64)
ifeq ($(OS),FreeBSD)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_X8664.asm
endif
endif
ifeq ($(ARCH),i386)
ifeq ($(OS),Linux)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32.asm
endif
endif
ifeq ($(ARCH),i686)
ifeq ($(OS),Linux)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32.asm
endif
endif
ifeq ($(ARCH),armv6l)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_ARM32.asm
endif
#TODO
ifeq ($(ARCH),armv9)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_ARM64.asm
endif

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
