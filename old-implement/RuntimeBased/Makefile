OBJS = MCString.o MCContext.o MCRuntime.o MCRuntimeMessaging.o VTable.o Main.o VTableSuper.o Bird.o

exec:$(OBJS)
	gcc -w -o exec $(OBJS)

MCString.o:MCString.c MCString.h
	gcc -w -c MCString.c

MCContext.o:MCContext.c MCContext.h
	gcc -w -c MCContext.c

MCRuntime.o:MCRuntime.c MCRuntime.h 
	gcc -w -c MCRuntime.c

MCRuntimeMessaging.o:MCRuntimeMessaging.s MCRuntime.h
	as -o MCRuntimeMessaging.o -c MCRuntimeMessaging.s

VTable.o:VTable.c VTable.h DrawableProtocol.h
	gcc -w -c VTable.c

Main.o:Main.c
	gcc -w -c Main.c

VTableSuper.o:VTableSuper.c VTableSuper.h DrawableProtocol.h
	gcc -w -c VTableSuper.c

Bird.o:Bird.c Bird.h
	gcc -w -c Bird.c

clean:
	rm exec $(OBJS)