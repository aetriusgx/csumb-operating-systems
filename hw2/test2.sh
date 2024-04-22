#!/bin/bash
# exit command works

# input
cat > temp-in.txt <<zzz
exit
zzz

# correct output
cat > gold-out.txt <<zzz
zzz

# actual output
rm -f temp-out.txt
./msh1 < temp-in.txt > temp-out.txt

diff -w temp-out.txt gold-out.txt > diffs.txt

