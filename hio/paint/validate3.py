#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    r, s = map(int, lines[0].split())
    assert 1 <= r <= 200000, "r kriv"
    assert 1 <= s <= 200000, "s kriv"
    assert 1 <= r * s <= 200000, "r * s kriv"
    nl.append("{} {}{}".format(r, s, E));

    grid = []
    for i in range(r):
        row = list(map(int, lines[i + 1].split()))
        for x in row:
            assert 0 <= x < 100000, "kriva boja"
        grid.append(row)
        nl.append("{}{}".format(' '.join(list(map(str, row))), E))

    q = int(lines[r + 1].strip())
    assert 1 <= q <= 100000, "q kriv"
    nl.append("{}{}".format(q, E))

    binary = True
    for i in range(q):
        rr, ss, c = map(int, lines[r + i + 2].split())
        assert 1 <= rr <= r, "rr kriv"
        assert 1 <= ss <= s, "ss kriv"
        assert 0 <= c < 100000, "c kriv"
        if c > 1: binary = False
        nl.append("{} {} {}{}".format(rr, ss, c, E))

    for row in grid:
        for c in row:
            if c > 1: binary = False

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'r': r, 's': s, 'q': q, 'binary': binary}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Subtask 1': 1, 'Subtask 2': 1, 'Subtask 3': 1, 'Subtask 4': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['r'] * data['s'] <= 10000 and data['q'] <= 10000: return 'Subtask 1'
    if data['r'] == 1: return 'Subtask 2'
    if data['binary']: return 'Subtask 3'
    return 'Subtask 4'


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
