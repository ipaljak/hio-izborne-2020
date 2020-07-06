PROBLEM=izazovni

rm -f -r test
mkdir test

echo 3 > test/$PROBLEM.dummy.in.1
echo 001 > test/$PROBLEM.dummy.out.1

echo 3 > test/$PROBLEM.dummy.in.2
echo 010 > test/$PROBLEM.dummy.out.2

echo 2 > test/$PROBLEM.in.1
python paula.py < test/$PROBLEM.in.1 > test/$PROBLEM.out.1

echo 4 > test/$PROBLEM.in.2
python paula.py < test/$PROBLEM.in.2 > test/$PROBLEM.out.2

echo 8 > test/$PROBLEM.in.3
python paula.py < test/$PROBLEM.in.3 > test/$PROBLEM.out.3

echo 10 > test/$PROBLEM.in.4
python paula.py < test/$PROBLEM.in.4 > test/$PROBLEM.out.4

echo 100 > test/$PROBLEM.in.5
python paula.py < test/$PROBLEM.in.5 > test/$PROBLEM.out.5

echo 1000 > test/$PROBLEM.in.6
python paula.py < test/$PROBLEM.in.6 > test/$PROBLEM.out.6

echo 10000 > test/$PROBLEM.in.7
python paula.py < test/$PROBLEM.in.7 > test/$PROBLEM.out.7

echo 100000 > test/$PROBLEM.in.8
python paula.py < test/$PROBLEM.in.8 > test/$PROBLEM.out.8

echo 1000000 > test/$PROBLEM.in.9
python paula.py < test/$PROBLEM.in.9 > test/$PROBLEM.out.9
