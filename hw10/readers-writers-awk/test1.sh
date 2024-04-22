#!/bin/bash
# readers and writers okay

# input
cat > temp-in.txt <<zzz
sr
sr
dr
dr
sw
dw
zzz

# correct output
cat > gold-out.txt << zzz
maxr = 2, maxw = 1
reader/writer test: PASS
writer/writer test: PASS
zzz

# actual output
cp test-code.awk check-rwlock.awk
awk -f check-rwlock.awk temp-in.txt > temp-out.txt

diff -w temp-out.txt gold-out.txt > diffs.txt
