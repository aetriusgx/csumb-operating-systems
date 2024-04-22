#!/bin/bash
# test3.p
./prog < test3.p > temp.out 2>&1
diff -w temp.out test3.txt
