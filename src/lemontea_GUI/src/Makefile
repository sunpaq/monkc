
OBJS = MCUIMainLoop.o MCUIBase.o MCNode.o MCXCBContext.o

#for Mac OS install libxcb use macports
LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/opt/local/include/
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -L/opt/local/lib -lxcb

#for UNIX-like OS
#LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/usr/local/include/
#LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -lxcb

CC = clang
FLAGS = -O -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as

exec:$(OBJS)
	$(CC) $(FLAGS) -o exec $(OBJS) $(LINK_BIN)

MCUIBase.o:MCUIBase.c
	$(CC) $(FLAGS) -c MCUIBase.c $(LINK_HEAD)

MCNode.o:MCNode.c
	$(CC) $(FLAGS) -c MCNode.c $(LINK_HEAD)

MCXCBContext.o:MCXCBContext.c
	$(CC) $(FLAGS) -c MCXCBContext.c $(LINK_HEAD)

MCUIMainLoop.o:MCUIMainLoop.c
	$(CC) $(FLAGS) -c MCUIMainLoop.c $(LINK_HEAD)

clean:
	rm -f exec $(OBJS)

dump:
	ulimit -c unlimited
