
# simplistic expression parser

SOURCES = error.c expr.c expr.h lexer.c main.c parser.c symbol.c

calc: $(SOURCES)
	gcc -o calc $(SOURCES)

tests: calc
	./run-tests.sh
	
clean:
	rm -f calc *~ temp* *.o

