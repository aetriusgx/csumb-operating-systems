#!/bin/bash
# multi-threaded 
gcc -o test6 test6.c dict.c -pthread
./test6
