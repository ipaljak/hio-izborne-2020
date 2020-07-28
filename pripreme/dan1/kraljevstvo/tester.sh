echo > out
echo > out_brute

while diff -nbqBw out out_brute; do
  ./gen $RANDOM 4 3 50000 100 > in
  ./tonko < in > out 2> /dev/null
  ./paula < in > out_brute 2> /dev/null
  printf '.'
done
