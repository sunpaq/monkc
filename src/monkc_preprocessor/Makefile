BINPATH = /usr/local/bin/
CC = clang

all:
	flex mcpp.l
	$(CC) lex.yy.c -o mcpp

clean:
	rm -f lex.yy.c mcpp core

install:
	mkdir -p $(BINPATH)
	cp mcpp $(BINPATH)
