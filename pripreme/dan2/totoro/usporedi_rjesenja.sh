#!/bin/bash

ime="totoro"
ime_koda="totoro"

for input in test/$ime*.in.*
do
  output=$input
  in="in"
  out="out"
  output="${output/$in/$out}"
  echo $input 
  echo $output
  echo "hmmmm"
  time ./$ime_koda < $input > out_file
  if diff -q $output out_file;
  then
    echo ok!
  else
    echo greska!
    cat out_file
    break
  fi
  echo -----------------------------------------
done
