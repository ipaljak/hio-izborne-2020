echo > out
echo > out_brute

while diff -nbqBw out out_brute; do
  ./gen $RANDOM 15 9 20 > in
  ./tonko < in > out 2> /dev/null
  ./paula_brut < in > out_brute 2> /dev/null
  printf '.'
done
