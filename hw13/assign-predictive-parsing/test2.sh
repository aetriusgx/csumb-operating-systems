#!/bin/bash
# test2.p
./prog < test2.p > temp.out 2>&1
diff -w temp.out test2.txt
