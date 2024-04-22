#!/bin/bash
# writer/writer
set -e
awk -f check-rwlock.awk rwlock-out.txt | grep 'writer.*writer.*PASS' > /dev/null
