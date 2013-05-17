ASM_ARM32 = MCRuntimeAsm_ARM32.o
ASM_ARM64 = MCRuntimeAsm_ARM64.o
ASM_IA32 = MCRuntimeAsm_IA32.o
ASM_X8664 = MCRuntimeAsm_X8664.o
ASM_IA32_darwin = MCRuntimeAsm_IA32_darwin.o
ASM_X8664_darwin = MCRuntimeAsm_X8664_darwin.o

SRCS = $(wildcard *.c)
LIBOBJS = $(patsubst %.c, %.o, $(SRCS))

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

ia32_darwin:$(LIBOBJS) $(ASM_IA32_darwin)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) $(ASM_IA32_darwin)
	tar -czvf monkc.tar.gz ./monkc/*

x8664_darwin:$(LIBOBJS) $(ASM_X8664_darwin)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS) $(ASM_X8664_darwin)
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

MCRuntimeAsm_IA32_darwin.o:MCRuntimeAsm/MCRuntimeAsm_IA32_darwin.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_IA32_darwin.o MCRuntimeAsm/MCRuntimeAsm_IA32_darwin.s

MCRuntimeAsm_X8664_darwin.o:MCRuntimeAsm/MCRuntimeAsm_X8664_darwin.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_X8664_darwin.o MCRuntimeAsm/MCRuntimeAsm_X8664_darwin.s

MCRuntimeAsm_ARM32.o:MCRuntimeAsm/MCRuntimeAsm_ARM32.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_ARM32.o MCRuntimeAsm/MCRuntimeAsm_ARM32.s

MCRuntimeAsm_ARM64.o:MCRuntimeAsm/MCRuntimeAsm_ARM64.s MCRuntime.h
	$(AS) -o MCRuntimeAsm_ARM64.o MCRuntimeAsm/MCRuntimeAsm_ARM64.s

#general target
%.o:%.c
	$(CC) -c $<

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
