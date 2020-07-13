for f in test/*.in*;
do
  echo "-------------------------------------------------"
  echo $f
  mkfifo temp
  ./interaktivni_server $f flog foutput < temp | ./marin > temp
  cat foutput
  rm temp
done
