LIBOBJS = MCRuntime.o MCString.o MCContext.o \
	MCClock.o MCProcess.o MCException.o \
	MCThread.o MCSocket.o MCIO.o MCMath.o \
	MCBuffer.o

CC = gcc -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

all:$(LIBOBJS)
	mkdir -p mocha
	cp *.h ./mocha
	ar -r ./mocha/libmocha.a $(LIBOBJS)
	tar -czvf mocha.tar.gz ./mocha/*

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

install:
	tar -xzvf mocha.tar.gz -C /usr/local/include/
	mv /usr/local/include/mocha/*.a /usr/local/lib/

clean:
	rm $(LIBOBJS) mocha.tar.gz -r mocha

dump:
	ulimit -c unlimited