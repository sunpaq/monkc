MODULES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(MODULES))
LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea
FLAGS = -g -w -Wall -Wno-unused-variable -Wno-return-type
AS = as
PP = mcpp
exec:$(OBJS)
	$(CC) $(FLAGS) -o exec $(OBJS) $(LINK_BIN)
%.o:%.c
	$(PP) $< .hash
	mv -f .hash $<
	$(CC) -c $< $(LINK_HEAD)
clean:
	rm -f exec $(OBJS) temp.* stream.txt core
dump:
	ulimit -c unlimited
