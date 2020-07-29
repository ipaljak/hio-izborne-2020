echo > out
echo > out_brute

while diff -nbqBw out out_brute; do
  ./gen $RANDOM 1000 300 > in
  ./tonko < in > out 2> /dev/null
  ./paljak_nk < in > out_brute 2> /dev/null
  printf '.'
done
