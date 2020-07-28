#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, m = map(int, lines[0].split())
    assert 1 <= n <= 5 * 10 ** 5, "n kriv"
    assert 1 <= m <= 5 * 10 ** 5, "m kriv"
    nl.append("{} {}{}".format(n, m, E));

    hi_col = 0
    col_set = set()

    for i in range(m):
        a, b, c = map(int, lines[i + 1].split())
        assert 1 <= a <= b <= n, "neispravan interval"
        assert 1 <= c <= 5 * 10 ** 5, "neispravna boja"
        hi_col = max(hi_col, c)
        col_set.add(c)
        nl.append("{} {} {}{}".format(a, b, c, E))

    l = list(map(int, lines[m + 1].split()))
    assert len(l) == n, "kriva duljina niza"
    for c in l:
        hi_col = max(hi_col, c)
        assert 0 <= c <= 5 * 10 ** 5, "kriva boja na dasci"
    nl.append("{}{}".format(' '.join(list(map(str, l))), E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'm': m, 'hi_col': hi_col, 'diff_col': len(col_set) == m}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'S1': 1, 'S2': 1, 'S3': 1, 'S4': 1, 'S5': 1, 'S6': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['m'] <= 9 and data['n'] <= 9: return 'S1'
    if data['m'] <= 5000 and data['n'] <= 5000 and data['diff_col']: return 'S2'
    if data['m'] <= 5 * 10 ** 5 and data['n'] <= 5 * 10 ** 5 and data['diff_col']: return 'S3'
    if data['m'] <= 5000 and data['n'] <= 5000: return 'S4'
    if data['m'] <= 5 * 10 ** 5 and data['n'] <= 5 * 10 ** 5 and data['hi_col'] <= 5: return 'S5'
    return 'S6'


################### Zadatak-specifican kod iznad ove linije #########################

import sys
import glob
import hashlib


def group_in_batches(files):
    # mnozenje.in.1a, mnozenje.in.1b sprema u isti batch

    files.sort()
    B = []
    for f in files:
        if f[-1].islower() and len(B) > 0 and f[:-1] == B[-1][-1][:-1]:
            B[-1].append(f)
        else:
            B.append([f])
    return B


if __name__ == "__main__":
    f = []
    for pattern in sys.argv[1:]:
        for filename in glob.glob(pattern):
            f.append(filename)

    bc = []
    for batch in group_in_batches(f):
        if 'dummy' not in batch[0]:
            bc.append([])
        for filename in batch:
            print("{}: ".format(filename), end="")
            try:
                lines = open(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska!", e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))

    clusters = {}
    for b in bc:
        for c in b:
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
