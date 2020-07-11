for f in test/*.in*;
do
  echo "-------------------------------------------------"
  echo $f
  ./interaktivni_server $f flog foutput < temp | ./marin > temp
  cat foutput
done
