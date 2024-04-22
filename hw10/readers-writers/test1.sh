#!/bin/bash
# code compiles and terminates
set -e		# exit at any error
rm -f rwlock-out.txt rwlock temp.txt
sed 's/NUMOPS .*/NUMOPS 100000/' rwlock.c > rwlock-big.c
gcc -o rwlock rwlock-big.c -pthread
./rwlock > temp.txt

# this is done so no output if code times out
mv temp.txt rwlock-out.txt
