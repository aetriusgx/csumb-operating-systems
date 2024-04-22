#!/bin/bash
# test6.p
./prog < test6.p > temp.out 2>&1
diff -w temp.out test6.txt
