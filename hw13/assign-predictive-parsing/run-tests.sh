#!/bin/bash
# test the parser by running all files with names of the form test*p

for f in test*p; do
  echo ------ $f ------
  cat $f
  echo ------ output: ------
  ./prog < $f
  echo ""
done
