#!/usr/bin/env bash
set -e


for i in $(seq 1 20); do
   in="./tests/t$i.in"
   out="./tests/t$i.out"
   cp $in std.in
   cp $out temp.expected
   cat "$in" | ./cmake-build-debug/solution > "temp.out"
   diff "temp.out" "temp.expected"
   rm -f temp.out
   rm temp.expected
   echo "Passed $i"
done;





