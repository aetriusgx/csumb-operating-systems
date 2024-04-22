#!/bin/bash
# bad input

# create input file and file with correct output
cat > temp-in.txt <<< "1230"
cat > gold-out.txt <<< "> input must contain only zeros and ones"

# run test code on input file
rm -f temp-out.txt 
./test-code < temp-in.txt > temp-out.txt 

# compare output to correct output
diff -w temp-out.txt gold-out.txt > diffs.txt

