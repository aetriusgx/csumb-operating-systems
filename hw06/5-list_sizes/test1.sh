#!/bin/bash
# list-sizes

awk --sandbox -f list_sizes.awk malloc-out.txt | head -20 | tail -1 > temp.txt
diff -wB temp.txt test1.txt > diffs.txt
