LIBOBJS = MCRuntime.o MCString.o MCContext.o \
	MCClock.o MCProcess.o MCException.o \
	MCThread.o MCSocket.o MCIO.o MCMath.o \
	MCBuffer.o MCUnitTest.o

CC = clang -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

all:$(LIBOBJS)
	mkdir -p monkc
	cp *.h ./monkc
	ar -r ./monkc/libmonkc.a $(LIBOBJS)
	tar -czvf monkc.tar.gz ./monkc/*

MCMath.o:MCMath.c MCMath.h
	$(CC) -c MCMath.c

MCThread.o:MCThread.c MCThread.h
	$(CC) -c MCThread.c -lpthread

MCException.o:MCException.c MCException.h
	$(CC) -c MCException.c

MCProcess.o:MCProcess.c MCProcess.h
	$(CC) -c MCProcess.c

MCString.o:MCString.c MCString.h
	$(CC) -c MCString.c

MCContext.o:MCContext.c MCContext.h
	$(CC) -c MCContext.c

MCRuntime.o:MCRuntime.c MCRuntime.h
	$(CC) -c MCRuntime.c

MCClock.o:MCClock.c MCClock.h
	$(CC) -c MCClock.c

MCSocket.o:MCSocket.c MCSocket.h
	$(CC) -c MCSocket.c

MCIO.o:MCIO.c MCIO.h
	$(CC) -c MCIO.c

MCBuffer.o:MCBuffer.c MCBuffer.h
	$(CC) -c MCBuffer.c

MCUnitTest.o:MCUnitTest.c MCUnitTest.h
	$(CC) -c MCUnitTest.c

install:
	tar -xzvf monkc.tar.gz -C /usr/local/include/
	mv /usr/local/include/monkc/*.a /usr/local/lib/

clean:
	rm $(LIBOBJS) monkc.tar.gz -r monkc

dump:
	ulimit -c unlimited