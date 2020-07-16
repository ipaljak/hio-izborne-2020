#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
import sys

sys.setrecursionlimit(10**6)


def dfs(node, dad, G):
    ret = 1
    for nxt in G[node]:
        if nxt == dad: continue
        ret += dfs(nxt, node, G)
    return ret


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, k = map(int, lines[0].split())
    assert 1 <= n <= 500000, "n kriv"
    assert 1 <= k <= n, "k kriv"
    nl.append("{} {}{}".format(n, k, E))

    v = []
    edges = []
    for i in range(n): v.append([])

    for i in range(n - 1):
        a, b = map(int, lines[i + 1].split())
        assert 1 <= a <= n, "a kriv"
        assert 1 <= b <= n, "b kriv"
        nl.append("{} {}{}".format(a, b, E))
        a -= 1
        b -= 1
        v[a].append(b)
        v[b].append(a)
        edges.append((min(a, b), max(a, b)))

    ovce = list(map(int, lines[n].split()))
    for ovca in ovce:
        assert 1 <= ovca <= n, "ovca izvan stabla"
    assert len(ovce) == len(set(ovce)), "dvije ovce u istom cvoru"
    nl.append("{}{}".format(' '.join(list(map(str, ovce))), E))

    assert dfs(0, -1, v) == n, "nije stablo"

    lanac = True
    edges.sort()
    for i in range(n - 1):
        (a, b) = edges[i]
        if a != i or b != i + 1: lanac = False

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'k': k, 'lanac': lanac}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Subtask 1': 1, 'Subtask 2': 1, 'Subtask 3': 1, 'Subtask 4': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['lanac']: return 'Subtask 1'
    if data['k'] <= 15: return 'Subtask 2'
    if data['n'] <= 2000: return 'Subtask 3'
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
