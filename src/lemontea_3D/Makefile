OBJS = MC3DMainLoop.o MCCamera.o

<<<<<<< HEAD
#for Mac OS install libgl use macports
=======
#for Mac OS install libxcb use macports
>>>>>>> d497317155bc4d2e6e922ce59e0d7f7ca0a0eade
#LINK_HEAD = -I/usr/local/include/monkc \
            -I/usr/local/include/lemontea \
            -I/opt/local/include \
            -I/opt/X11/include
#LINK_BIN = -lpthread \
           -L/usr/local/lib -lmonkc -llemontea \
<<<<<<< HEAD
           -L/opt/X11/lib -lX11 -lGL -lGLU 

#for UNIX-like OS
LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/usr/local/include/
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -lX11 -lGL -lGLU -lm

=======
           -L/opt/X11/lib -lm -lX11 -lGL -lGLU

#for UNIX-like OS
LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/usr/local/include/
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -lm -lX11 -lGL -lGLU

CC = gcc
>>>>>>> d497317155bc4d2e6e922ce59e0d7f7ca0a0eade
FLAGS = -O -g -w -Wall -Wno-unused-variable -Wno-return-type

exec:$(OBJS)
	$(CC) $(FLAGS) -o exec $(OBJS) $(LINK_BIN)

MC3DMainLoop.o:MC3DMainLoop.c
	$(CC) $(FLAGS) -c MC3DMainLoop.c $(LINK_HEAD)

MCCamera.o:MCCamera.c
	$(CC) $(FLAGS) -c MCCamera.c $(LINK_HEAD)

clean:
	rm -f exec $(OBJS)

dump:
	ulimit -c unlimited
