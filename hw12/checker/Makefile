
test: check
	for t in test*.sh; do ./$$t; echo $$?; done

check: check.c
	gcc -o check check.c

clean:
	rm -f check
