
# build expr objects

SOURCES = expr.c test_expr.c

test: test_expr
	./test_expr

test_expr: $(SOURCES)
	gcc -o test_expr test_expr.c expr.c expr.h

clean:
	rm -f test_expr *~ 

