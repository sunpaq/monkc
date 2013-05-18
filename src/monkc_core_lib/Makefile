INCPATH = /usr/local/include/
LIBPATH = /usr/local/lib/
BINPATH = /usr/local/bin/

SRCS = $(wildcard *.c)
LIBOBJS = $(patsubst %.c, %.o, $(SRCS))
ARCH = $(strip $(shell uname -m))
OS = $(strip $(shell uname -s))

CC = clang -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

#default is IA-32 cpus
all:$(LIBOBJS) MCRuntimeAsm.o mcbuild
	mkdir -p monkc
	cp *.h ./monkc
	cp mcbuild ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) MCRuntimeAsm.o
	tar -czvf monkc.tar.gz ./monkc/*

MCRuntimeAsm.o:
ifeq ($(ARCH),x86_64)
ifeq ($(OS),Darwin)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_X8664_darwin.s
endif
endif
ifeq ($(ARCH),i386)
ifeq ($(OS),Darwin)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32_darwin.s
endif
endif
ifeq ($(ARCH),i686)
ifeq ($(OS),Darwin)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32_darwin.s
endif
endif
ifeq ($(ARCH),x86_64)
ifeq ($(OS),Linux)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_X8664.s
endif
endif
ifeq ($(ARCH),i386)
ifeq ($(OS),Linux)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32.s
endif
endif
ifeq ($(ARCH),i686)
ifeq ($(OS),Linux)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_IA32.s
endif
endif
ifeq ($(ARCH),armv6l)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_ARM32.s
endif
#TODO
ifeq ($(ARCH),armv9)
	$(AS) -o MCRuntimeAsm.o MCRuntimeAsm/MCRuntimeAsm_ARM64.s
endif

#general target
%.o:%.c
	$(CC) -c $<

install:
	rm -f -r $(INCPATH)monkc
	rm -f $(LIBPATH)libmonkc.a
	rm -f $(BINPATH)mcbuild
	tar -xzvf monkc.tar.gz -C $(INCPATH)
	mv $(INCPATH)monkc/*.a $(LIBPATH)
	mv $(INCPATH)monkc/mcbuild $(BINPATH)
	chmod +x $(BINPATH)mcbuild

clean:
	rm -f $(LIBOBJS) MCRuntimeAsm.o monkc.tar.gz 
	rm -f -r monkc

dump:
	ulimit -c unlimited
