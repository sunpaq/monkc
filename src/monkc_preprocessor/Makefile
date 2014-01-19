BINPATH = /usr/local/bin/
CC = clang

all:
	flex mcpp.l
	$(CC) lex.yy.c -o mcpp

clean:
	rm lex.yy.c mcpp core

install:
	cp mcpp $(BINPATH)