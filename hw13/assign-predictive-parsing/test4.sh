#!/bin/bash
# test4.p
./prog < test4.p > temp.out 2>&1
diff -w temp.out test4.txt
