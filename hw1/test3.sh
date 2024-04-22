#!/bin/bash
# input 11111

# create input file and file with correct output
cat > temp-in.txt <<< 11111
cat > gold-out.txt <<< "> 31"

# run test code on input file
rm -f temp-out.txt 
./test-code < temp-in.txt > temp-out.txt 

# compare output to correct output
diff -w temp-out.txt gold-out.txt > diffs.txt
