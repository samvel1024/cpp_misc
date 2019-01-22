#!/usr/bin/env bash
set -e

cd cmake-build-debug; make -j8; cd ..;

if test -z "$1"
then
      echo "Test dir not specified"
      exit 1
fi

if test -z "$2"
then
      echo "Input for generator not specified"
      exit 1
fi

mkdir -p $1
for i in $(seq 1 20); do
    echo "generating $i"
   file="./$1/t$i.in"
   echo "$2" | ./cmake-build-debug/testgen > ${file}
   cat "$file" | ./cmake-build-debug/naive > "./$1/t$i.out"
done;


