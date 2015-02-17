SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea

FLAGS = -O -g -w -Wall -Wno-unused-variable -Wno-return-type

exec:$(OBJS)
	$(CC) $(FLAGS) -o exec $(OBJS) $(LINK_BIN)

#general target
%.o:%.c
	$(CC) $(FLAGS) -c $< $(LINK_HEAD)

clean:
	rm -f exec $(OBJS) core

dump:
	ulimit -c unlimited
