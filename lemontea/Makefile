
OBJS = XCB_example.o

LINK_HEAD = -I/usr/local/include/monkc
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -lxcb

CC = gcc -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

exec:$(OBJS)
	$(CC) -o exec $(OBJS) $(LINK_BIN)

XCB_example.o:XCB_example.c
	$(CC) -c XCB_example.c $(LINK_HEAD)

clean:
	rm exec $(OBJS)

dump:
	ulimit -c unlimited