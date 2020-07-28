#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, k = map(int, lines[0].split())
    assert 3 <= n <= 3000, "n kriv"
    assert 3 <= k <= n, "k kriv"
    nl.append("{} {}{}".format(n, k, E));

    p = []
    for i in range(1, n + 1):
        x, y = map(int, lines[i].split());
        p.append((x, y))
        assert -10 ** 9 <= x <= 10 ** 9, "x koordinata izvan intervala"
        assert -10 ** 9 <= y <= 10 ** 9, "y koordinata izvan intervala"
        nl.append("{} {}{}".format(x, y, E))

    x1, y1 = p[0];
    x2, y2 = p[1];

    assert y1 == 0 and y2 == 0, "kraljevi ne leze na x-osi"
    assert x1 < x2, "Krivi odnos kraljeva"
    for (x, y) in p[2:]:
        assert x1 <= x <= x2, "dvorac nije izmedju kraljeva"

    assert len(p) == len(set(p)), "Ima duplih tocaka"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'S1': 1, 'S2': 1, 'S3': 1, 'S4': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 20: return 'S1'
    if data['n'] <= 100: return 'S2'
    if data['n'] <= 500: return 'S3'
    return 'S4'


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
