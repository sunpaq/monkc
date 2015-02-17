BINPATH = /usr/local/bin/
LEX=flex
all:
	$(LEX) mcpp.l
	$(CC) lex.yy.c -o mcpp

clean:
	rm -f lex.yy.c mcpp core

install:
	mkdir -p $(BINPATH)
	cp mcpp $(BINPATH)
