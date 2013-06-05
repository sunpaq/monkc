LIBOBJS = MCString.o MCContext.o \
	MCClock.o MCProcess.o MCException.o \
	MCThread.o MCSocket.o MCIO.o MCMath.o \
	MCBuffer.o MCUnitTest.o 

LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea
#LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea

CC = clang -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

all:$(LIBOBJS)
	mkdir -p lemontea
	cp *.h ./lemontea
	ar -r ./lemontea/liblemontea.a $(LIBOBJS)
	tar -czvf lemontea.tar.gz ./lemontea/*

MCMath.o:MCMath.c MCMath.h
	$(CC) -c MCMath.c $(LINK_HEAD)

MCThread.o:MCThread.c MCThread.h
	$(CC) -c MCThread.c $(LINK_HEAD)

MCException.o:MCException.c MCException.h
	$(CC) -c MCException.c $(LINK_HEAD)

MCProcess.o:MCProcess.c MCProcess.h
	$(CC) -c MCProcess.c $(LINK_HEAD)

MCString.o:MCString.c MCString.h
	$(CC) -c MCString.c $(LINK_HEAD)

MCContext.o:MCContext.c MCContext.h
	$(CC) -c MCContext.c $(LINK_HEAD)

MCClock.o:MCClock.c MCClock.h
	$(CC) -c MCClock.c $(LINK_HEAD)

MCSocket.o:MCSocket.c MCSocket.h
	$(CC) -c MCSocket.c $(LINK_HEAD)

MCIO.o:MCIO.c MCIO.h
	$(CC) -c MCIO.c $(LINK_HEAD)

MCBuffer.o:MCBuffer.c MCBuffer.h
	$(CC) -c MCBuffer.c $(LINK_HEAD)

MCUnitTest.o:MCUnitTest.c MCUnitTest.h
	$(CC) -c MCUnitTest.c $(LINK_HEAD)

install:
	rm -f -r /usr/local/include/lemontea
	rm -f /usr/local/lib/liblemontea.a
	tar -xzvf lemontea.tar.gz -C /usr/local/include/
	mv /usr/local/include/lemontea/*.a /usr/local/lib/

clean:
	rm -f $(LIBOBJS) lemontea.tar.gz 
	rm -f -r lemontea

dump:
	ulimit -c unlimited