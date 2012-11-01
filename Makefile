exec:Main.o Class.o LinkList.o MemAllocator.o ObjectsPool.o
	gcc -o exec Main.o Class.o LinkList.o MemAllocator.o ObjectsPool.o
Main.o:Main.c
	gcc -c Main.c
Class.o:Class.c
	gcc -c Class.c
LinkList.o:LinkList.c
	gcc -c LinkList.c
MemAllocator.o:MemAllocator.c
	gcc -c MemAllocator.c
ObjectsPool.o:ObjectsPool.c
	gcc -c ObjectsPool.c
clean:
	rm exec Main.o Class.o LinkList.o MemAllocator.o ObjectsPool.o