#!/bin/bash
# help command works

# input
cat > temp-in.txt <<zzz
help
zzz

# correct output
cat > gold-out.txt <<zzz
enter 'help', 'today', or 'exit' to quit
zzz

# actual output
rm -f temp-out.txt
./msh1 < temp-in.txt > temp-out.txt

diff -wB temp-out.txt gold-out.txt > diffs.txt

