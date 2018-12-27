#!/usr/bin/env bash
set -e

if test -z "$1"
then
      echo "Test dir not specified"
      exit 1
fi

for i in $(seq 1 20); do
   in="./$1/t$i.in"
   out="./$1/t$i.out"
   cp $in std.in
   cp $out temp.expected
   cat "$in" | ./cmake-build-debug/solution > "temp.out"
   diff "temp.out" "temp.expected"
   rm -f temp.out
   rm temp.expected
   echo "Passed $i"
done;





