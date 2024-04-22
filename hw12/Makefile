
test: parens
	for t in test*.sh; do ./$$t; echo $$?; done

parens: parens.c
	gcc -o parens parens.c

clean:
	rm -f parens *~
