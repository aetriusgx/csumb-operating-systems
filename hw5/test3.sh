#!/bin/bash
# output redirection

set -e

rm -f temp.txt temp-out.txt -- -c

# input
cat > temp-in.txt <<zzz
wc -c test1.sh > temp.txt
exit
zzz

# correct output
cat > gold-out.txt << zzz
58 test1.sh
zzz

# actual output
./msh4 < temp-in.txt > temp2.txt
mv temp.txt temp-out.txt

diff -w temp-out.txt gold-out.txt > diffs.txt
