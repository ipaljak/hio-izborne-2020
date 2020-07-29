#!/bin/bash

ime="perm"

#abcdefghijklmnopqrstuvwxyz
rm test/ -r
mkdir test

f() {
  echo $1 $2 $3
  ./generator $3 > test/$ime.in.$1$2
  ./$ime < test/perm.in.$1$2 > test/perm.out.$1$2
  #python3 analizator.py < test/perm.in.$1$2
  echo
}

for i in {a..j} #10 komada
do
  f 1 $i prvi
done

for i in {a..j} #10 komada
do
  f 2 $i drugi
done

for i in {a..j} #10 komada
do
  f 3 $i treci
done

for i in {a..t} #20 komada
do
  f 4 $i cetvrti
done
