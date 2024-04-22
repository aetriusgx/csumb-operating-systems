#!/bin/bash
# multiple commands

# input
cat > temp-in.txt <<zzz
help
today
ls -t
exit
zzz

# correct output
cat > gold-out.txt <<zzz
enter 'help', 'today', or 'exit' to quit
zzz
date +%m/%d/%Y >> gold-out.txt
cat >> gold-out.txt <<zzz
token: 'ls'
token: '-t'
zzz

# actual output
rm -f temp-out.txt
./msh1 < temp-in.txt > temp-out.txt

diff -wB temp-out.txt gold-out.txt > diffs.txt
