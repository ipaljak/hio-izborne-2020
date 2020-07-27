#!/bin/bash

ime="perm"

for input in test/perm*.in.*
do
  output=$input
  in="in"
  out="out"
  output="${output/$in/$out}"
  echo $input 
  time ./$ime < $input > out
  if diff -q $output out;
  then
    echo ok!
  else
    echo greska!
    cat out
    cat test/$ime.dummy.out.$i
    break
  fi
  echo -----------------------------------------
done
