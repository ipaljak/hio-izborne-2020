#!/bin/bash

for i in {1..3}
do
  echo dummy $i
  python3 skandal.py < test/skandal.dummy.in.$i > out
  if diff -q test/skandal.dummy.out.$i out;
  then
    echo ok!
  else
    echo greska!
    cat out
    cat test/skandal.dummy.out.$i
    break
  fi
  echo -----------------------------------------
done

for i in {1..4}
do
  for j in a b c d e
  do
    echo primjer $i$j
    python3 skandal.py < test/skandal.in.$i$j > out
    if diff -q test/skandal.out.$i$j out;
    then
      echo ok!
    else
      echo greska!
      cat out
      cat test/skandal.out.$i$j
      break
    fi
    echo -----------------------------------------
  done
done
