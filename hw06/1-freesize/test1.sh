#!/bin/bash
# freesize

awk --sandbox -f freesize.awk malloc-out.txt | head -100 | awk '{sum += $1}END{print sum}' > temp.txt
awk --sandbox -f freesize.awk malloc-out.txt | wc -l >> temp.txt
diff -wB temp.txt test1.txt > diffs.txt

