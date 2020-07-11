#!/usr/bin/python2

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "standardni"
sys.setrecursionlimit(1000010)

MAXN = 500000

class Test(object):
    def __init__(self, a, b, n, cuts):
        self.a = a       # horizontal dimension
        self.b = b       # vertical dimension
        self.n = n       # number of cuts
        self.cuts = cuts # cuts, i.e. [('V', 5), ('H', 3), ...]


    def validate(self):
        assert(1 <= self.a <= MAXN)
        assert(1 <= self.b <= MAXN)
        assert(1 <= self.n <= MAXN)
        assert(self.n <= self.a + self.b - 2)
        assert(len(self.cuts) == self.n)
        for (x, y) in self.cuts:
            assert(x == 'H' or x == 'V')
            if x == 'H':
                assert(1 <= y < self.b)
            else:
                assert(1 <= y < self.a)
        assert(len(set(self.cuts)) == self.n)


    def write(self, fd=sys.stdout):
        print>>fd, self.a, self.b, self.n
        for (x, y) in self.cuts:
            print>>fd, x, y


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_random(a, b, n):
    cuts = set()
    while len(cuts) < n:
        x = ['H', 'V'][random.randint(0, 1)]
        if x == 'H':
            y = random.randint(1, b - 1)
        else:
            y = random.randint(1, a - 1)
        cuts.add((x, y))
    return Test(a, b, n, list(cuts))


def gen_random_all(a, b):
    cuts = []
    for i in range(1, a): cuts.append(('V', i))
    for i in range(1, b): cuts.append(('H', i))
    random.shuffle(cuts)
    return Test(a, b, a + b - 2, cuts)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        1000,
        1000,
        1,
        [('V', 200)]
    ))

    dummy.append(Test(
        6,
        4,
        3,
        [('H', 3),
         ('H', 1),
         ('V', 4)]
    ))

    dummy.append(Test(
        10,
        20,
        6,
        [('H', 17),
         ('V', 3),
         ('V', 2),
         ('H', 19),
         ('H', 13),
         ('V', 7)]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subask -- 2 <= A, B <= 500000, N = 1
    subtask1 = []
    for i in range(1, 5):
        subtask1.append(gen_random(random.randint(2, MAXN),
                                    random.randint(2, MAXN), 1))
    subtask1.append(gen_random(500000, 500000, 1))
    real.append(subtask1)

    # 2. subask -- 2 <= A, B <= 100
    subtask2 = []
    for i in range(1, 5):
        subtask2.append(gen_random_all(random.randint(2, 100),
                                        random.randint(2, 100)))
    subtask2.append(gen_random_all(100, 100))
    real.append(subtask2)

    # 3. subask -- A = 1, 2 <= B <= 500000
    subtask3 = []
    for i in range(1, 5):
        subtask3.append(gen_random_all(1,
                                        random.randint(2, 500000)))
    subtask3.append(gen_random_all(1, 500000))
    real.append(subtask3)

    # 4. subask -- 2 <= A, B <= 1000
    subtask4 = []
    for i in range(1, 5):
        subtask4.append(gen_random_all(random.randint(500, 1000),
                                        random.randint(500, 1000)))
    subtask4.append(gen_random_all(1000, 1000))
    real.append(subtask4)

    # 5. subask -- 2 <= A, B <= 500000
    subtask5 = []
    for i in range(1, 5):
        subtask5.append(gen_random(random.randint(400000, 500000),
                                    random.randint(400000, 500000),
                                    500000))
    subtask5.append(gen_random(500000, 500000, 500000))
    real.append(subtask5)

    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d%c' \
                    % (PROBLEM, i+1, chr(ord('a')+j))
            input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
            test.write(file(input, 'wt'))

def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()

