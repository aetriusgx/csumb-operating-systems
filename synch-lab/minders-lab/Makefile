
test: minder
	./minder > temp.txt

minder: minder.c
	gcc -o minder minder.c -pthread

clean:
	rm -f minder temp*
