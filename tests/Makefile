
OBJS = Main.o MyTestCase1.o

LINK_HEAD = -I/usr/local/include/monkc
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -lffi

CC = clang -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

exec:$(OBJS)
	$(CC) -o exec $(OBJS) $(LINK_BIN)

Main.o:Main.c
	$(CC) -c Main.c $(LINK_HEAD)

MyTestCase1.o:MyTestCase1.c MyTestCase1.h
	$(CC) -c MyTestCase1.c $(LINK_HEAD)

clean:
	rm exec $(OBJS)

dump:
	ulimit -c unlimited