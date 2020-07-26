#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 1e3 + 10;

int rnd(int a, int b) {
  return rand() % (b - a + 1) + a;
}

int prost[MAXN];
int prebrisan[MAXN];

int m = 10;
int n = 1000;

void eratostenovo_sito() {
  prost[1] = 1;
  for(int i = 2; i < MAXN; i++) {
    if(!prebrisan[i]) {
      prost[i] = 1;
      for(int j = i; j < MAXN; j += i)
        prebrisan[j] = 1;
    }
  }
}

void najgluplji_moguci() {
  printf("%d %d\n", m, n);
  REP(i, m) {
    vector<int> v;
    REP(j, n)
      v.push_back(j + 1);
    random_shuffle(v.begin(), v.end());
    REP(j, n) {
      printf("%d", v[j]);
      if(j < n - 1) printf(" ");
    }
    printf("\n");
  }
}

int prvi_manji_prost(int x) {
  while(!prost[x]) x--;
  return x;
}

void ispisi(auto v) {
  for(auto x : v)
    cerr << x << " ";
  cerr << endl;
}

vector<int> napravi_cikluse(vector<int> velicine) {
  vector<int> ret(n);
  int pocetak = 0;
  REP(i, (int) velicine.size()) {
    vector<int> perm;
    REP(j, velicine[i]) perm.push_back(j);
    random_shuffle(perm.begin(), perm.end());
    REP(j, velicine[i] - 1)
      ret[pocetak + perm[j]] = pocetak + perm[j + 1];
    ret[pocetak + perm[velicine[i] - 1]] = pocetak + perm[0];
    pocetak += velicine[i];
  }
  REP(i, n) ret[i];
  return ret;
}

vector<int> generiraj_velicine() {
  /*return {2, 3, 5, 7, 11};*/
  /*vector<int> niz;
  int sum = 0;
  while(sum < n) {
    niz.push_back(5);
    sum += 5;
  }
  if(n - sum > 0) niz.push_back(n - sum);
  return niz;*/
  int sum = 0;
  vector<int> niz;
  while(sum < n) {
    int gornja = max(1, min(n / m, n - sum));
    int donja = max(1, gornja / 2);
    int x = rnd(donja, gornja);
    niz.push_back(x);
    sum += x;
  }
  return niz;
}

void veliki_ciklusi() {
  printf("%d %d\n", m, n);
  vector<int> velicine = generiraj_velicine();
  vector<vector<int> > v;
  REP(i, m) {
    vector<int> niz = napravi_cikluse(velicine); 
    v.push_back(niz);
  }
  int pocetak = 0;
  REP(i, (int) velicine.size()) {
    int kraj = pocetak + velicine[i];
    if(rnd(1, 2) == 1) {
      FOR(j, 1, m) {
        FOR(k, pocetak, kraj)
          v[j][k] = v[0][k];
      }
    }
    pocetak = kraj;
  }
  REP(i, m) {
    REP(j, n) {
      printf("%d", v[i][j] + 1);
      if(j < n - 1) printf(" ");
    }
    printf("\n");
  }
}

int main() {
  srand(time(0) * getpid());
  eratostenovo_sito();
  veliki_ciklusi();
  return 0;
}

