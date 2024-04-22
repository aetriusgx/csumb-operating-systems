#!/bin/bash
# tokens are printed

# input
cat > temp-in.txt <<zzz
wc -c   -w
exit
zzz

# correct output
cat > gold-out.txt <<zzz
token: 'wc'
token: '-c'
token: '-w'
zzz

# actual output
rm -f temp-out.txt
./msh1 < temp-in.txt > temp-out.txt

diff -w temp-out.txt gold-out.txt > diffs.txt

