#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
from queue import Queue


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    r, s = map(int, lines[0].split())
    assert 1 <= r, "r kriv"
    assert 1 <= s, "s kriv"
    nl.append("{} {}{}".format(r, s, E));

    sr, ss = map(int, lines[1].split())
    assert 0 <= sr < r, "sr kriv"
    assert 0 <= ss < s, "ss kriv"
    nl.append("{} {}{}".format(sr, ss, E));

    assert len(lines) == r + 2, "broj redaka nije r"
    grid = []
    b_cnt = 0
    for i in range(r):
        row = lines[i + 2].strip()
        assert len(row) == s, "krivi broj znakova u retku"
        for c in row:
            assert c in "#.B", "nedopusten znak u gridu"
            if c == 'B': b_cnt += 1
        grid.append(row)
        nl.append("{}{}".format(row, E))
    assert b_cnt == 1, "krivi broj znakova B u gridu"

    n = 0
    gold = False
    Q = Queue()
    bio = set()
    dr = [0, 1, 0, -1]
    ds = [1, 0, -1, 0]
    Q.put((sr, ss))
    bio.add((sr, ss))
    while not Q.empty():
        (rr, ss) = Q.get()
        n += 1
        if grid[rr][ss] == 'B': gold = True
        for (ddr, dds) in zip(dr, ds):
            rrr = rr + ddr
            sss = ss + dds
            if grid[rrr][sss] == '#' or (rrr, sss) in bio: continue
            bio.add((rrr, sss))
            Q.put((rrr, sss))

    assert gold, "blago nije dohvatljivo"
    assert 1 <= n <= 100000, "krivi broj dohvatljivih polja"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'r': r, 's': s, 'n': n}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Subtask 1': 1, "Subtask 2": 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 15: return "Subtask 1"
    return "Subtask 2"


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
