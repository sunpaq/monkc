OBJS = MCRuntime.o MCString.o MCContext.o VTable.o Main.o \
	VTableSuper.o Bird.o MCClock.o MCProcess.o MCException.o \
	MCThread.o MCSocket.o MCIO.o\

CC = gcc -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

exec:$(OBJS)
	$(CC) -o exec $(OBJS) -lpthread

# MCRuntime.o:MCRuntime.s MCRuntime.h
# 	$(AS) -o MCRuntime.o MCRuntime.s

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

VTable.o:VTable.c VTable.h DrawableProtocol.h
	$(CC) -c VTable.c

Main.o:Main.c
	$(CC) -c Main.c

VTableSuper.o:VTableSuper.c VTableSuper.h DrawableProtocol.h
	$(CC) -c VTableSuper.c

Bird.o:Bird.c Bird.h
	$(CC) -c Bird.c

MCClock.o:MCClock.c MCClock.h
	$(CC) -c MCClock.c

MCSocket.o:MCSocket.c MCSocket.h
	$(CC) -c MCSocket.c

MCIO.o:MCIO.c MCIO.h
	$(CC) -c MCIO.c

clean:
	rm core exec $(OBJS)

dump:
	ulimit -c unlimited