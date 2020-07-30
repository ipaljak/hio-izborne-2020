#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, k = map(int, lines[0].split())
    assert 1 <= n <= 2 * 10 ** 5, "n kriv"
    assert 1 <= k <= 2 * 10 ** 5, "k kriv"
    nl.append("{} {}{}".format(n, k, E));

    for i in range(n):
        a, b = map(int, lines[i + 1].split())
        assert 1 <= a <= 10 ** 9, "neispravan a"
        assert 1 <= b <= 10 ** 9, "neispravan b"
        nl.append("{} {}{}".format(a, b, E))

    broj_pozivanja_POREDAK = 0
    broj_gostiju = n
    broj_otislih = 0
    #zaboravio sam kak ovo napisat pametnije
    imam = [0 for i in range(n + k + 1)] 
    for i in range(k): 
        l = lines[n + 1 + i].split()
        if l[0] == "POREDAK":
          assert len(l) == 1, "POREDAK mora biti sam"
          broj_pozivanja_POREDAK = broj_pozivanja_POREDAK + 1
          nl.append("{}{}".format("POREDAK", E))
        elif l[0] == "DOLAZI": 
          assert len(l) == 3, "DOLAZI mora imati velicinu 3"
          broj_gostiju = broj_gostiju + 1
          a = int(l[1])
          b = int(l[2])
          assert 1 <= a <= 10 ** 9, "neispravan a"
          assert 1 <= b <= 10 ** 9, "neispravan b"
          nl.append("{} {} {}{}".format("DOLAZI", a, b, E))
        elif l[0] == "ODLAZI": 
          assert len(l) == 2, "ODLAZI mora imati velicinu 2"
          x = int(l[1])
          assert 1 <= x <= broj_gostiju and imam[x] == 0, "problem s odlaskom"
          imam[x] = 1
          broj_otislih = broj_otislih + 1
          nl.append("{} {}{}".format("ODLAZI", x, E))
        assert broj_gostiju - broj_otislih >= 1, "prazan je restac"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'k': k, 'poredak': broj_pozivanja_POREDAK}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'S1': 1, 'S2': 1, 'S3': 1, 'S4': 1, 'S5': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 9 and data['k'] == 1 and data['poredak'] == 1: return 'S1'
    if data['n'] <= 20 and data['k'] == 1 and data['poredak'] == 1: return 'S2'
    if data['n'] <= 200000 and data['k'] == 1 and data['poredak'] == 1: return 'S3'
    if data['n'] <= 200000 and data['poredak'] == 0: return 'S4'
    if data['n'] <= 200000 and data['poredak'] <= 10: return 'S5'


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
