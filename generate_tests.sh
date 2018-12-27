#!/usr/bin/env bash
set -e

mkdir -p tests
for i in $(seq 1 20); do
   file="./tests/t$i.in"
   echo "$1 $2" | ./cmake-build-debug/testgen > ${file}
   cat "$file" | ./cmake-build-debug/naive > "./tests/t$i.out"
done;


