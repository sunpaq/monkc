BINPATH = /usr/local/bin/

all:
	flex -o mcpp_lex.c mcpp.l
	bison -o mcpp_parser.c -d mcpp.y
	clang mcpp_lex.c mcpp_parser.c -o mcpp

clean:
	rm mcpp_lex.c mcpp_parser.c mcpp core

install:
	cp mcpp $(BINPATH)