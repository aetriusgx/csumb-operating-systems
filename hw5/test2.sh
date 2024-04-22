#!/bin/bash
# in and out redirection

set -e

# input
cat > temp-in.txt <<zzz
wc -c < test1.sh > temp.txt
exit
zzz

# correct output
cat > gold-out.txt << zzz
58
zzz

# actual output
# this is strange; we're using bash redirection to have msh read
# commands from temp-in.txt, and msh uses its own redirection on the
# commands in temp-in.txt!
./msh4 < temp-in.txt > temp2.txt
mv temp.txt temp-out.txt

diff -wB temp-out.txt gold-out.txt > diffs.txt
