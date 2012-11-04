OBJS = MCRuntime.o VTable.o VTableMain.o VTableSuper.o

exec:$(OBJS)
	gcc -o exec $(OBJS)

MCRuntime.o:MCRuntime.c MCRuntime.h
	gcc -c MCRuntime.c

VTable.o:VTable.c VTable.h
	gcc -c VTable.c

VTableMain.o:VTableMain.c
	gcc -c VTableMain.c

VTableSuper.o:VTableSuper.c VTableSuper.h
	gcc -c VTableSuper.c

clean:
	rm exec $(OBJS)