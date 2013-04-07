
OBJS = Main.o VTable.o VTableSuper.o Bird.o

LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea

CC = clang -g -w -Wall -Wno-unused-variable -Wno-return-type
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

clean:
	rm -f exec $(OBJS) temp.* stream.txt core 

dump:
	ulimit -c unlimited