#!/bin/bash
# test1.p
./prog < test1.p > temp.out 2>&1
diff -w temp.out test1.txt
