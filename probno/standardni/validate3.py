
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    a, b, n = map(int, lines[0].split())
    assert 1 <= a and a <= 500000, 'a izvan ogranicenja'
    assert 2 <= b and b <= 500000, 'b izvan ogranicenja'
    assert 1 <= n and n <= a + b - 2, 'n izvan ogranicenja'
    nl.append('{} {} {}{}'.format(a, b, n, E))

    assert len(lines) == n + 1, 'broj rezova nije jednak n'
    set_h, set_v = set(), set()

    for line in lines[1:]:
        d = line[0]
        x = int(line[2:-1])

        if d == 'H':
            assert 1 <= x < b, 'horizontalni rez izvan papira na y={}'.format(x)
            assert x not in set_h, 'dupli horizontalni rez na y={}'.format(x)
            set_h.add(x)
        elif d == 'V':
            assert 1 <= x < a, 'vertikalni rez izvan papira na x={}'.format(x)
            assert x not in set_v, 'dupli vertikalni rez na x={}'.format(x)
            set_v.add(x)
        else:
            assert False, 'prvi znak je razlicit od H i V'

        nl.append('{} {}{}'.format(d, x, E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'a': a, 'b': b, 'n': n}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {"Subtask 1": 1, "Subtask 2": 1, "Subtask 3": 1,
        "Subtask 4": 1, "Subtask 5" : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['a'] == 1: return 'Subtask 3'
    if data['a'] <= 100 and data['b'] <= 100: return 'Subtask 2'
    if data['a'] <= 1000 and data['b'] <= 1000: return 'Subtask 4'
    if data['n'] == 1: return 'Subtask 1'
    return 'Subtask 5'

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
