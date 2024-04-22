
test: msh1
	for i in 1 2 3 4 5 6; do echo -n test $$i ": "; ./test$$i.sh; echo $$?; done

msh1: msh1.c
	gcc -o msh1 msh1.c

clean:
	rm -f temp* msh1 diffs.txt gold-out*
