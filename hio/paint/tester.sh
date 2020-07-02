echo > out
echo > out_brute

while diff -nbqBw out out_brute; do
  ./gen $RANDOM 20 20 20 6 > in
  ./marin < in > out 2> /dev/null
  ./paint_brute < in > out_brute 2> /dev/null
  printf '.'
done
