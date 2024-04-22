#!/bin/bash
# number of readers
set -e
awk -f check-rwlock.awk rwlock-out.txt | grep 'maxr = [23]' > /dev/null
