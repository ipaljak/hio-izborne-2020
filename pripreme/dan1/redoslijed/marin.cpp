#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double lf;
typedef long double Lf;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define sec second
#define mp make_pair
#define pb push_back

const int MAXN = 500100;
const int offset = (1 << 19);
const int inf = (1 << 30);

void kraj() {
  puts("NE");
  exit(0);
}

int n, m, p[MAXN], boja[MAXN];
int a[MAXN], b[MAXN];
int com[MAXN];
int imam[MAXN];

queue <int> Q;
vector <int> ans;

struct tournament {
  vector <int> v[offset * 2];
  int mini[offset * 2], maks[offset * 2];
  bool prosao[offset * 2];

  tournament() {
    REP(i, offset * 2) {
      mini[i] = inf;
      maks[i] = -inf;
      prosao[i] = 0;
    }
  }

  void refresh(int x) {
    if (mini[x] < maks[x]) return;
    if (mini[x] == maks[x] && prosao[x]) return;
    if (mini[x] > maks[x]) {
      for (auto &t : v[x]) {
        imam[t]--;
        if (!imam[t]) Q.push(t);
      }
      v[x].clear();
    } else {
      vector <int> ostali;
      REP(i, (int)v[x].size()) {
        int t = v[x][i];
        if (boja[t] == mini[x]) {
          imam[t]--;
          if (!imam[t]) Q.push(t);
        } else {
          ostali.pb(t);
        }
      }
      v[x] = ostali;
      prosao[x] = 1;
    }
  }

  void ubaci(int cvor, int l, int r, int a, int b, int x) {
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
      v[cvor].pb(x);
      imam[x]++;
      return;
    }

    int mid = (l + r) / 2;

    ubaci(cvor * 2, l, mid, a, b, x);
    ubaci(cvor * 2 + 1, mid + 1, r, a, b, x);
  }

  void postavi(int x, int y) {
    if (!y) return;
    x += offset;
    while (x) {
      mini[x] = min(mini[x], y);
      maks[x] = max(maks[x], y);
      x /= 2;
    }
  }

  void update(int cvor, int l, int r, int a, int b) {
    if (l > b || r < a || l > r || maks[cvor] < mini[cvor]) return;
    if (l >= a && r <= b) {
      mini[cvor] = inf;
      maks[cvor] = -inf;
      refresh(cvor);
    }

    if (l == r) return;

    int mid = (l + r) / 2;

    update(cvor * 2, l, mid, a, b);
    update(cvor * 2 + 1, mid + 1, r, a, b);
    
    mini[cvor] = min(mini[cvor * 2], mini[cvor * 2 + 1]);
    maks[cvor] = max(maks[cvor * 2], maks[cvor * 2 + 1]);

    refresh(cvor);
  }
};

tournament T;

void obradi(int x) {
  T.update(1, 0, offset - 1, a[x], b[x]);
  ans.pb(x + 1);
}

void check() {
  int tmp = 0;
  REP(i, n) {
    tmp += com[i];
    if (tmp && !p[i] || !tmp && p[i]) {
      kraj();
    }
  }
}

int main() {
  scanf("%d %d",&n,&m);

  REP(i, m) {
    scanf("%d %d %d",&a[i],&b[i],&boja[i]);
    a[i]--; b[i]--;
    T.ubaci(1, 0, offset - 1, a[i], b[i], i);
    com[a[i]]++;
    com[b[i] + 1]--;
  }

  REP(i, n) scanf("%d",&p[i]);
  REP(i, n) T.postavi(i, p[i]);

  check();

  REP(i, offset * 2) T.refresh(i);

  while (!Q.empty()) {
    obradi(Q.front());
    Q.pop();
  }

  if ((int)ans.size() != m) kraj();

  reverse(all(ans));
  puts("DA");
  for (auto x : ans) printf("%d ", x);
  puts("");
    
  return 0;
}

