#!/bin/bash
# test7.p
./prog < test7.p > temp.out 2>&1
diff -w temp.out test7.txt
