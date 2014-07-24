SRCS=$(wildcard *.c)
LIBOBJS=$(patsubst %.c, %.o, $(SRCS))

LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea
#LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea

CC = gcc -g -w -Wall -Wno-unused-variable -Wno-return-type

all:$(LIBOBJS)
	mkdir -p lemontea
	cp -f *.h ./lemontea
	ar -r ./lemontea/liblemontea.a $(LIBOBJS)
	tar -czvf lemontea.tar.gz ./lemontea/*

#general target
%.o:%.c
	$(CC) -c $< $(LINK_HEAD)

install:
	rm -f -r /usr/local/include/lemontea
	rm -f /usr/local/lib/liblemontea.a
	tar -xzvf lemontea.tar.gz -C /usr/local/include/
	mv /usr/local/include/lemontea/*.a /usr/local/lib/

clean:
	rm -f $(LIBOBJS) lemontea.tar.gz
	rm -f -r lemontea
	rm -f *.o

dump:
	ulimit -c unlimited
