
test: msh4
	for i in 1 2 3; do echo -n test $$i ": "; ./test$$i.sh; echo $$?; done

msh4: msh4.c
	gcc -o msh4 msh4.c

clean:
	rm -f temp* msh4 diffs.txt gold-out*
