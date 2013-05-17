MODULES = $(wildcard *.c) 
OBJS = $(patsubst %.c, %.o, $(MODULES)) 
LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea 
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea 
CC = clang -g -w -Wall -Wno-unused-variable -Wno-return-type 
AS = as 
exec:$(OBJS)
	$(CC) -o exec $(OBJS) $(LINK_BIN) 
%.o:%.c
	$(CC) -c $< $(LINK_HEAD) 
clean:
	rm -f exec $(OBJS) temp.* stream.txt core 
dump:
	ulimit -c unlimited
