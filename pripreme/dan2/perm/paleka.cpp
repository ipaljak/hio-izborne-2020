#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<
#define debug(...) fprintf(stderr, __VA_ARGS__)
typedef long long ll;
using namespace std;

const int MaxN = 1010; 
const int MaxK = 12;
const int Mod = 1e9 + 7;

int N, K;
int p[MaxK][MaxN];
bool visited[MaxN][MaxN];
ll res[MaxN*MaxN];
ll sz[MaxN*MaxN];

inline ll mod_mul(ll a, ll b) {
  return a * b % Mod; 
}

inline ll mod_pot(ll a, int exp) {
  ll ret = 1;
  for (; exp > 0; exp >>= 1) {
    if (exp & 1) ret = mod_mul(ret, a);  
    a = mod_mul(a, a);
  }
  return ret;
}

inline ll mod_inv(ll a) {
  return mod_pot(a, Mod - 2);
}

void dfs(int i, int j, int comp) {
  visited[i][j] = true;
  res[comp] += (i > j);
  sz[comp]++;
  REP(k, K) {
    if (!visited[p[k][i]][p[k][j]]) {
      dfs(p[k][i], p[k][j], comp);
    }
  }
}

void solve() {
  int comp = 0;
  REP(i, N) REP(j, N) {
    if (!visited[i][j]) {
      dfs(i, j, comp++);
    } 
  }
  ll sol = 0;
  REP(c, comp) {
    sol += mod_mul(sz[c] - res[c], mod_mul(res[c], mod_inv(sz[c])));
    sol %= Mod;
  }
  cout << sol << endl;
}

void load() {
  cin >> K >> N;
  REP(k, K) REP(i, N) {cin >> p[k][i]; p[k][i]--;}
}

int main() {
  ios_base::sync_with_stdio(false);
  load();
  solve();
  return 0;
}


