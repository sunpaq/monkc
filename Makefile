exec:Main.o LinkList.o Node.o String.o
	gcc -o exec Main.o LinkList.o Node.o String.o
Main.o:Main.c
	gcc -c Main.c
LinkList.o:LinkList.c
	gcc -c LinkList.c
Node.o:Node.c
	gcc -c Node.c
String.o:String.c
	gcc -c String.c
clean:
	rm exec Main.o LinkList.o Node.o String.o