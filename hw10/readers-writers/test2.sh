#!/bin/bash
# reader/writer
set -e
awk -f check-rwlock.awk rwlock-out.txt | grep 'reader.*writer.*PASS' > /dev/null
