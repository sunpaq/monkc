BINPATH = /usr/local/bin/

all:
	flex mcpp.l
	clang lex.yy.c -o mcpp

clean:
	rm lex.yy.c mcpp core

install:
	cp mcpp $(BINPATH)