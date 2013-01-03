OBJS = MCRuntime.o MCString.o MCContext.o VTable.o Main.o \
	VTableSuper.o Bird.o MCClock.o MCProcess.o MCException.o \
	MCThread.o \

CC = gcc -g
AS = as

exec:$(OBJS)
	$(CC) -w -o exec $(OBJS) -lpthread

# MCRuntime.o:MCRuntime.s MCRuntime.h
# 	$(AS) -o MCRuntime.o MCRuntime.s

MCThread.o:MCThread.c MCThread.h
	$(CC) -w -c MCThread.c -lpthread

MCException.o:MCException.c MCException.h
	$(CC) -w -c MCException.c

MCProcess.o:MCProcess.c MCProcess.h
	$(CC) -w -c MCProcess.c

MCString.o:MCString.c MCString.h
	$(CC) -w -c MCString.c

MCContext.o:MCContext.c MCContext.h
	$(CC) -w -c MCContext.c

MCRuntime.o:MCRuntime.c MCRuntime.h
	$(CC) -w -c MCRuntime.c

VTable.o:VTable.c VTable.h DrawableProtocol.h
	$(CC) -w -c VTable.c

Main.o:Main.c
	$(CC) -w -c Main.c

VTableSuper.o:VTableSuper.c VTableSuper.h DrawableProtocol.h
	$(CC) -w -c VTableSuper.c

Bird.o:Bird.c Bird.h
	$(CC) -w -c Bird.c

MCClock.o:MCClock.c MCClock.h
	$(CC) -w -c MCClock.c

clean:
	rm core exec $(OBJS)

dump:
	ulimit -c unlimited