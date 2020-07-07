PROBLEM=izazovni

rm -f -r test
mkdir test

echo 3 > test/$PROBLEM.dummy.in.1
echo 001 > test/$PROBLEM.dummy.out.1

echo 3 > test/$PROBLEM.dummy.in.2
echo 010 > test/$PROBLEM.dummy.out.2

echo 2 > test/$PROBLEM.in.1a
echo 4 > test/$PROBLEM.in.1b
echo 8 > test/$PROBLEM.in.1c
echo 16 > test/$PROBLEM.in.1d
echo 20 > test/$PROBLEM.in.1e

echo 21 > test/$PROBLEM.in.2a
echo 50 > test/$PROBLEM.in.2b
echo 100 > test/$PROBLEM.in.2c

echo 101 > test/$PROBLEM.in.3a
echo 1000 > test/$PROBLEM.in.3b
echo 10000 > test/$PROBLEM.in.3c

echo 10001 > test/$PROBLEM.in.4a
echo 100000 > test/$PROBLEM.in.4b
echo 1000000 > test/$PROBLEM.in.4c

for fin in test/$PROBLEM.in.*; do
    fout=${fin/.in./.out.}
    python paula.py < $fin > $fout
done
