#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 1e6 + 10;

int main() {
  for(int i = 1; i <= 10; i++) {
    printf("\n%d:\n", i);
    system("./generator > in");
    system("python3 analizator.py < in > out_analizator");
    system("./perm < in > out_pravo");
    //system("./brut < in > out_brut");
    if(system("diff -b out_analizator out_pravo")) break;
    system("cat out_pravo");
  }
  printf("\n----------------------------\n");
  return 0;
}

