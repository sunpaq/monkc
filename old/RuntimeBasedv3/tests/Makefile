
OBJS = Main.o TestMCRuntime.o TestMCClock.o

LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea

CC = clang -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

exec:$(OBJS)
	$(CC) -o exec $(OBJS) $(LINK_BIN)

Main.o:Main.c
	$(CC) -c Main.c $(LINK_HEAD)

TestMCRuntime.o:TestMCRuntime.c TestMCRuntime.h
	$(CC) -c TestMCRuntime.c $(LINK_HEAD)

TestMCClock.o:TestMCClock.c TestMCClock.h
	$(CC) -c TestMCClock.c $(LINK_HEAD)

clean:
	rm -f exec $(OBJS) core

dump:
	ulimit -c unlimited