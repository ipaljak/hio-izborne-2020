python gen.py

for f in test/*.in.*
do
  ./standardni_paljak < $f > ${f/in/out}
done
