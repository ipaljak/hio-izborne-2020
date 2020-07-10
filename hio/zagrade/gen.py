"""Generator primjera za Zagrade."""

import os
import random
import shutil
import sys

sys.setrecursionlimit(1000010)

PROBLEM = 'zagrade'
N1 = 10**3
N2 = 10**5

def validate(s):
    assert s.count('(') == s.count(')')
    assert all(c in '()' for c in s)

def write_test(s, num, is_linear=False, is_dummy=False):
    validate(s)

    if is_dummy:
        name = 'test/' + PROBLEM + '.dummy.in.' + num
    else:
        name = 'test/' + PROBLEM + '.in.' + num

    n = len(s)
    q = n - 1 if is_linear else n * n // 4

    with open(name, 'w') as f:
        print(n, q, file=f)
        print(s, file=f)

def coin_flip(p):
    return random.random() < p

def gen_valid_interval(s, l, r, p):
    if l == r: return

    if coin_flip(p):
        s[l] = '('
        s[r - 1] = ')'
        gen_valid_interval(s, l + 1, r - 1, p)
    else:
        m = random.randrange(l + 1, r, 2)
        s[l] = '('
        s[m] = ')'
        gen_valid_interval(s, l + 1, m, p)
        gen_valid_interval(s, m + 1, r, p)

def gen(n, p, k=0):
    assert n % 2 == 0

    if p == 1:
        s = ['('] * (n // 2) + [')'] * (n // 2)
    else:
        s = ['?'] * n
        gen_valid_interval(s, 0, n, p)

    while k > 0:
        i = random.randrange(0, n)
        j = random.randrange(0, n)
        if i > j:
            i, j = j, i

        if s[i] == '(' and s[j] == ')':
            s[i] = ')'
            s[j] = '('
            k -= 1

    return ''.join(s)

def main():
    random.seed(28071997)

    shutil.rmtree('test', ignore_errors=True)
    os.mkdir('test')

    write_test('((()))', '1', is_dummy=True)

    write_test('()', '1a')
    write_test('()' * (N1 // 2), '1b')
    write_test(gen(N1, 0.00), '1c')
    write_test(gen(N1, 0.25), '1d')
    write_test(gen(N1, 0.50), '1e')
    write_test(gen(N1, 0.75), '1f')
    write_test(gen(N1, 1.00), '1g')
    write_test(gen(N1 - 100, 0.50), '1h')

    write_test(')(', '2a')
    write_test(')' * (N1 // 2) + '(' * (N1 // 2), '2b')
    write_test(gen(N1, 0.00, int(N1 * 0.1)), '2c')
    write_test(gen(N1, 0.25, int(N1 * 0.3)), '2d')
    write_test(gen(N1, 0.50, int(N1 * 0.1)), '2e')
    write_test(gen(N1, 0.75, int(N1 * 0.3)), '2f')
    write_test(gen(N1, 1.00, int(N1 * 0.1)), '2g')
    write_test(gen(N1 - 100, 0.50, int(N1 * 0.01)), '2h')

    write_test('(())', '3a', is_linear=True)
    write_test('()' * (N2 // 2), '3b', is_linear=True)
    write_test(gen(N2, 0.00), '3c', is_linear=True)
    write_test(gen(N2, 0.25), '3d', is_linear=True)
    write_test(gen(N2, 0.50), '3e', is_linear=True)
    write_test(gen(N2, 0.75), '3f', is_linear=True)
    write_test(gen(N2, 1.00), '3g', is_linear=True)
    write_test(gen(N2 - 100, 0.50), '3h', is_linear=True)

    write_test('))((', '4a', is_linear=True)
    write_test(')' * (N2 // 2) + '(' * (N2 // 2), '4b', is_linear=True)
    write_test(gen(N2, 0.00, int(N2 * 0.1)), '4c', is_linear=True)
    write_test(gen(N2, 0.25, int(N2 * 0.3)), '4d', is_linear=True)
    write_test(gen(N2, 0.50, int(N2 * 0.1)), '4e', is_linear=True)
    write_test(gen(N2, 0.75, int(N2 * 0.3)), '4f', is_linear=True)
    write_test(gen(N2, 1.00, int(N2 * 0.1)), '4g', is_linear=True)
    write_test(gen(N2 - 100, 0.50, int(N2 * 0.001)), '4h', is_linear=True)

if __name__ == '__main__':
    main()
