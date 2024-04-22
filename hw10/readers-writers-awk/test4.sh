#!/bin/bash
# read and write while writing

# input
cat > temp-in.txt <<zzz
sr
dr
sw
sw
sr
dr
dw
dw
zzz

# correct output
cat > gold-out.txt << zzz
maxr = 1, maxw = 2
reader/writer test: FAIL
writer/writer test: FAIL
zzz

# actual output
awk -f check-rwlock.awk temp-in.txt > temp-out.txt

diff -w temp-out.txt gold-out.txt > diffs.txt
