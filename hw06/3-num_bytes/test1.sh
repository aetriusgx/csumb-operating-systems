#!/bin/bash
# num_bytes

awk --sandbox -f num_bytes.awk malloc-out.txt | head -100 | awk '{sum += $1}END{print sum}' > temp.txt
diff -wB temp.txt test1.txt > diffs.txt

