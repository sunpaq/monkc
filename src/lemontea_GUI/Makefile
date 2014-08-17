
OBJS = MCUIMainLoop.o MCUIBase.o

#LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/opt/local/include/
#LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -L/opt/local/lib -lxcb

LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/usr/local/include/
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -lxcb

CC = gcc -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

exec:$(OBJS)
	$(CC) -o exec $(OBJS) $(LINK_BIN)

MCUIBase.o:MCUIBase.c
	$(CC) -c MCUIBase.c $(LINK_HEAD)

MCUIMainLoop.o:MCUIMainLoop.c
	$(CC) -c MCUIMainLoop.c $(LINK_HEAD)

clean:
	rm -f exec $(OBJS)

dump:
	ulimit -c unlimited
