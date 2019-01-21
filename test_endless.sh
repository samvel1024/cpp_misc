#!/usr/bin/env bash
set -e


if test -z "$1"
then
      echo "Temporary test file not specified"
      exit 1
fi
ctr=0

if test -z "$2"
then
      echo "Testgen input not specified"
      exit 1
fi
ctr=0


while true; do
   ctr=$((ctr + 1))
   echo "********TEST $ctr ******";

   echo $2 | ./cmake-build-debug/testgen > "$1.in"
   cat "$1.in" | ./cmake-build-debug/naive > "$1.expected"
   cat "$1.in" | ./cmake-build-debug/solution > "$1.out"
   diff "$1.out" "$1.expected"
   rm -f "$1.out"
   rm "$1.expected"
   echo "Passed"
done;


