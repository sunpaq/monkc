OBJS = MC3DMainLoop.o

#for Mac OS install libxcb use macports
LINK_HEAD = -I/usr/local/include/monkc \
            -I/usr/local/include/lemontea \
            -I/opt/local/include \
            -I/opt/X11/include
LINK_BIN = -lpthread \
           -L/usr/local/lib -lmonkc -llemontea \
           -L/opt/X11/lib -lX11 -lGL -lGLU

#for UNIX-like OS
#LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/usr/local/include/
#LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -lxcb

CC = clang
FLAGS = -O -g -w -Wall -Wno-unused-variable -Wno-return-type

exec:$(OBJS)
	$(CC) $(FLAGS) -o exec $(OBJS) $(LINK_BIN)

MC3DMainLoop.o:MC3DMainLoop.c
	$(CC) $(FLAGS) -c MC3DMainLoop.c $(LINK_HEAD)

clean:
	rm -f exec $(OBJS)

dump:
	ulimit -c unlimited