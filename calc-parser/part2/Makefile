
# build and print expr objects

SOURCES = expr.c test_main.c

test: test_expr
	./test_expr

test_expr: expr.c expr.h
	gcc -o test_expr test_expr.c expr.c expr.h

clean:
	rm -f test_expr *~ 

