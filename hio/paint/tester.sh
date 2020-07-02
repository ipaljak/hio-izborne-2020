echo > out
echo > out_brute

while diff -nbqBw out out_brute; do
  ./gen $RANDOM 200 200 50000 4 > in
  ./paint < in > out 2> /dev/null
  ./marin < in > out_brute 2> /dev/null
  printf '.'
done
