#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    k, n = map(int, lines[0].split())
    assert 1 <= k <= 10, "k kriv"
    assert 1 <= n <= 2500, "n kriv"
    nl.append("{} {}{}".format(k, n, E));

    s = set()
    for i in range(n): s.add(i + 1)

    ciklus = True

    for i in range(k):
        pi = list(map(int, lines[1 + i].split()))
        assert len(pi) == n, "kriva duljina permutacije"
        assert set(pi) == s, "niz nije permutacija"
        nl.append("{}{}".format(' '.join(list(map(str, pi))), E))

        visited = set()
        node = 1
        while (node - 1) not in visited:
            visited.add(node - 1)
            node = pi[node - 1]
        ciklus &= len(visited) == n

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'k': k, 'n': n, 'ciklus': ciklus}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'S1': 1, 'S2': 1, 'S3': 1, 'S4': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['k'] <= 10 and data['n'] <= 9: return 'S1'
    if data['k'] == 1 and data['n'] <= 2500 and data['ciklus']: return 'S2'
    if data['k'] == 1 and data['n'] <= 2500: return 'S3'
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
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1


    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
