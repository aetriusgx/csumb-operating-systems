#!/bin/bash
# test5.p
./prog < test5.p > temp.out 2>&1
diff -w temp.out test5.txt
