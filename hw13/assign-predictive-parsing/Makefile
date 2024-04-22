
# simplistic program parser

SOURCES = error.c expr.c lexer.c main.c parser.c prog.c stmt.c string_util.c symbol.c

tests: prog
	./run-tests.sh
	
prog: $(SOURCES)
	gcc -o prog $(SOURCES)

prog.tar: $(SOURCES)
	tar cf prog.tar *.c *.h Makefile

clean:
	rm -f prog *~ temp* *.o

