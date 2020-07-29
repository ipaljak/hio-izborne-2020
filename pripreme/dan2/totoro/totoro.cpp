#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 2510;
const int MAXM = 20;
const int MOD = 1e9 + 7;

int add(int a, int b) {
  int ret = a + b;
  if(ret >= MOD) ret -= MOD;
  return ret;
}

int mul(int a, int b) {
  llint ret = (llint) a * b;
  if(ret >= MOD) ret %= MOD;
  return ret;
}

int pot(int a, int x) {
  int ret = 1;
  while(x) {
    if(x % 2 == 1)
      ret = mul(ret, a);
    a = mul(a, a);
    x /= 2;
  }
  return ret;
}

int inverz(int a) {
  return pot(a, MOD - 2);
}

int dijeli(int a, int b) {
  assert(b != 0);
  return mul(a, inverz(b));
}

int m, n, rj;
int perm[MAXM][MAXN];

int bio[MAXN][MAXN];

void unesi() {
  scanf("%d %d", &m, &n);
  REP(i, m)
    REP(j, n) {
      scanf("%d", &perm[i][j]);
      perm[i][j]--;
    }
}

int brojac;
int ukupan_broj_cvorova_u_komponenti;
int broj_inverznih_cvorova;

vector<int> velicine_komponenti;

void dfs(int x, int y) {
  //ovaj assert provjerava ima li graf doista to svojstvo da je svaka
  //connected komponenta doista i scc komponenta, zato i korisitm brojac
  assert(bio[x][y] == 0 || bio[x][y] == brojac);
  if(bio[x][y]) return;
  ukupan_broj_cvorova_u_komponenti++;
  if(x > y)
    broj_inverznih_cvorova++;
  bio[x][y] = brojac;
  for(int i = 0; i < m; i++)
    dfs(perm[i][x], perm[i][y]);
}

void obradi_komponentu(int x, int y) {
  brojac++;
  ukupan_broj_cvorova_u_komponenti = 0;
  broj_inverznih_cvorova = 0;
  dfs(x, y);
  int num = ukupan_broj_cvorova_u_komponenti - broj_inverznih_cvorova;
  int udio_inverznih = dijeli(broj_inverznih_cvorova, ukupan_broj_cvorova_u_komponenti);
  rj = add(rj, mul(num, udio_inverznih));
  velicine_komponenti.push_back(ukupan_broj_cvorova_u_komponenti);
}

void rijesi() {
  REP(i, n)
    REP(j, n)
      if(!bio[i][j])
        obradi_komponentu(i, j);
}

void ispisi_podatke_o_komponentama() {
  cerr << m << " " << n << endl;
  TRACE(velicine_komponenti.size());
}

int main() {
  unesi();
  rijesi();
  printf("%d\n", rj);
  //ispisi_podatke_o_komponentama();
  return 0;
}

