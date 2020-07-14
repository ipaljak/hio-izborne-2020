for f in test/*.in*;
do
  echo "-------------------------------------------------"
  echo $f
  mkfifo temp
  ./zagrade_server $f flog foutput < temp | ./$1 > temp
  cat foutput
  rm temp
done
