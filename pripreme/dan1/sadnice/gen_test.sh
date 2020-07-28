PREFIX="test/sadnice.in"

echo 1 1       > $PREFIX.1a
echo 2 2       > $PREFIX.1b
echo 9 9       > $PREFIX.1c
echo 999 999   > $PREFIX.1d
echo 1000 1000 > $PREFIX.1e

echo 1 2      > $PREFIX.2a
echo 2 4      > $PREFIX.2b
echo 3 6      > $PREFIX.2c
echo 498 996  > $PREFIX.2d
echo 499 998  > $PREFIX.2e
echo 500 1000 > $PREFIX.2f

echo 1 1 > $PREFIX.3a
echo 1 2 > $PREFIX.3b
echo 1 3 > $PREFIX.3c
echo 2 2 > $PREFIX.3d
echo 2 3 > $PREFIX.3e
echo 3 3 > $PREFIX.3f

echo 10 10 > $PREFIX.4a
echo 9 10  > $PREFIX.4b
echo 6 10  > $PREFIX.4c
echo 5 10  > $PREFIX.4d
echo 1 10  > $PREFIX.4e
echo 7 9   > $PREFIX.4f
echo 5 7   > $PREFIX.4g
echo 4 5   > $PREFIX.4h
echo 2 3   > $PREFIX.4i

echo 100 100 > $PREFIX.5a
echo 97 100  > $PREFIX.5b
echo 77 92   > $PREFIX.5c
echo 43 78   > $PREFIX.5d
echo 33 87   > $PREFIX.5e
echo 32 96   > $PREFIX.5f
echo 16 65   > $PREFIX.5g
echo 9 100   > $PREFIX.5h
echo 5 99    > $PREFIX.5i
echo 1 100   > $PREFIX.5j

echo 1000 1000 > $PREFIX.6a
echo 930 992   > $PREFIX.6b
echo 929 993   > $PREFIX.6c
echo 667 999   > $PREFIX.6d
echo 503 1000  > $PREFIX.6e
echo 491 999   > $PREFIX.6f
echo 330 998   > $PREFIX.6g
echo 238 962   > $PREFIX.6h
echo 202 997   > $PREFIX.6i
echo 84 924    > $PREFIX.6j
echo 32 999    > $PREFIX.6k
echo 9 997     > $PREFIX.6l
echo 1 1000    > $PREFIX.6m

rm test/sadnice.out.*
for f in test/sadnice.in.*; do
    ./paula < $f > ${f/.in/.out}
done
