#!/bin/bash
# write while reading

# input
cat > temp-in.txt <<zzz
sr
sw
dw
dr
zzz

# correct output
cat > gold-out.txt << zzz
maxr = 1, maxw = 1
reader/writer test: FAIL
writer/writer test: PASS
zzz

# actual output
awk -f check-rwlock.awk temp-in.txt > temp-out.txt

diff -w temp-out.txt gold-out.txt > diffs.txt
