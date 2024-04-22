#!/bin/bash
# count-allocs

awk --sandbox -f count_allocs.awk malloc-out.txt > count.txt
diff -wB count.txt test1.txt > diffs.txt

