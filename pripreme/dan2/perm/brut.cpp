#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 1e3 + 10;
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
vector<int> perm[MAXM];

void unesi() {
  scanf("%d %d", &m, &n);
  REP(i, m)
    REP(j, n) {
      int x;
      scanf("%d", &x);
      x--;
      perm[i].push_back(x);
    }
}

vector<int> kompozicija(vector<int> q, vector<int> p) {
  vector<int> ret;
  REP(i, n)
    ret.push_back(q[p[i]]);
  return ret;
}

void ispisi(auto t) {
  for(auto x : t)
    cout << x + 1 << " ";
  cout << endl;
}

void generiraj_grupu() { 
  vector<int> id;
  REP(i, n) id.push_back(i);
  vector<vector<int> > popis;
  map<vector<int>, int> bio;
  queue<vector<int> > q;
  q.push(id);
  bio[id] = 1;
  popis.push_back(id);
  while(!q.empty()) {
    vector<int> t = q.front();
    q.pop();
    REP(i, m) {
      vector<int> p = kompozicija(perm[i], t);
      if(!bio[p]) {
        bio[p] = 1;
        popis.push_back(p);
        q.push(p);
      }
    }
  }
  int ukupan_broj_inverzija = 0;
  for(auto t : popis) {
    REP(i, n)
      FOR(j, i + 1, n)
        if(t[i] > t[j])
          ukupan_broj_inverzija = add(ukupan_broj_inverzija, 1);
  }
  int prosjecan_broj_inverzija = dijeli(ukupan_broj_inverzija, (int) popis.size());
  printf("%d\n", prosjecan_broj_inverzija);
  //for(auto t : popis)
  //  ispisi(t);
  //TRACE(popis.size());
  TRACE(popis.size());
}

int main() {
  unesi();
  generiraj_grupu();  
  return 0;
}

