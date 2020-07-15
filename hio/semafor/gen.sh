for f in test/*.in.*
do
  echo $f
  ./daniel_fast < $f > ${f/in/out}
done
