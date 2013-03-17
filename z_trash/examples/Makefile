
OBJS = Main.o VTable.o VTableSuper.o Bird.o MyTestCase1.o

LINK_HEAD = -I/usr/local/include/mocha
LINK_BIN = -lpthread -L/usr/local/lib -lmocha

CC = gcc -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

exec:$(OBJS)
	$(CC) -o exec $(OBJS) $(LINK_BIN)

Main.o:Main.c
	$(CC) -c Main.c $(LINK_HEAD)

VTable.o:VTable.c VTable.h
	$(CC) -c VTable.c $(LINK_HEAD)

VTableSuper.o:VTableSuper.c VTableSuper.h
	$(CC) -c VTableSuper.c $(LINK_HEAD)

Bird.o:Bird.c Bird.h
	$(CC) -c Bird.c $(LINK_HEAD)

MyTestCase1.o:MyTestCase1.c MyTestCase1.h
	$(CC) -c MyTestCase1.c $(LINK_HEAD)

clean:
	rm exec $(OBJS)

dump:
	ulimit -c unlimited