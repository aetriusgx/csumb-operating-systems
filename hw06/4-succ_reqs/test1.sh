#!/bin/bash
# succ_reqs

awk --sandbox -f succ_reqs.awk malloc-out.txt | head -10 | tail -1 > temp.txt
diff -wB temp.txt test1.txt > diffs.txt
