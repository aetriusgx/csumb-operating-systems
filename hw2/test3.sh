#!/bin/bash
# today command works

# input
cat > temp-in.txt <<zzz
today
zzz

# correct output
date +%m/%d/%Y > gold-out.txt

# actual output
rm -f temp-out.txt
./msh1 < temp-in.txt > temp-out.txt

diff -wB temp-out.txt gold-out.txt > diffs.txt

