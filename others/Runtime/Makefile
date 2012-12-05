OBJS = MCContext.o MCRuntime.o VTable.o Main.o VTableSuper.o

exec:$(OBJS)
	gcc -w -o exec $(OBJS)

MCContext.o:MCContext.c MCRuntime.h
	gcc -w -c MCContext.c

MCRuntime.o:MCRuntime.c MCRuntime.h 
	gcc -w -c MCRuntime.c

VTable.o:VTable.c VTable.h DrawableProtocol.h
	gcc -w -c VTable.c

Main.o:Main.c
	gcc -w -c Main.c

VTableSuper.o:VTableSuper.c VTableSuper.h DrawableProtocol.h
	gcc -w -c VTableSuper.c

clean:
	rm exec $(OBJS)