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

const int MAXN = 505;

int par[MAXN * MAXN];

int find(int x) {
  if (x == par[x]) return x;
  return par[x] = find(par[x]);
}

struct Komponenta {
  int ind;
  int boja;
  int size;
  
  unordered_set <int> veliki;

  unordered_map <int, queue <int> > sus;

  Komponenta(){}
  Komponenta(int _ind, int _boja, int _sz) {
    ind = _ind;
    boja = _boja;
    size = _sz;
  }
};

vector <Komponenta> comps;

int get_color(int x) {
  return comps[find(x)].boja;
}

void merge(int a, int b) {
  a = find(a); b = find(b);
  if (a == b) return;
  if (comps[a].size < comps[b].size) swap(a, b);
  
  par[b] = a;
  comps[a].size += comps[b].size;

  for (auto &x : comps[b].veliki) {
    comps[a].veliki.insert(x);
  }

  comps[b].veliki.clear(); // redukcija memorije, testirati bez ove linije

  for (auto &t : comps[b].sus) {
    while (!t.sec.empty()) {
      int x = find(t.sec.front());
      t.sec.pop();
      if (get_color(x) != t.fi) continue;
      comps[a].sus[t.fi].push(x);
    }
  }
}

int n, m, p[MAXN][MAXN];
int pos[MAXN][MAXN], sz[MAXN * MAXN];

const int smjerx[] = {1, -1, 0, 0};
const int smjery[] = {0, 0, -1, 1};

int bio[MAXN][MAXN];

void dfs(int x, int y, int k) {
  bio[x][y] = 1;
  pos[x][y] = k;
  sz[k]++;
  REP(i, 4) {
    int nx = x + smjerx[i];
    int ny = y + smjery[i];
    if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    if (bio[nx][ny] || p[nx][ny] != p[x][y]) continue;
    dfs(nx, ny, k);
  }
}

void napravi_susjede() {
  unordered_map <ll, int> spojeno;
  REP(x, n) {
    REP(y, m) {
      REP(i, 4) {
        int nx = x + smjerx[i];
        int ny = y + smjery[i];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        if (p[nx][ny] == p[x][y]) continue;
        int a = pos[x][y], b = pos[nx][ny];
        if (a > b) swap(a, b);
        if (spojeno.count((ll)a * MAXN * MAXN + b)) continue;
        spojeno[(ll)a * MAXN * MAXN + b] = 1;
        if (sz[a] > MAXN) {
          comps[b].veliki.insert(a);
        } else {
          comps[b].sus[p[x][y]].push(a);
        }
        if (sz[b] > MAXN) {
          comps[a].veliki.insert(b);
        } else {
          comps[a].sus[p[x][y]].push(b);
        }
      }
    }
  }
}

void kveri() {
  int a, b, c;
  scanf("%d %d %d",&a,&b,&c);
  a--; b--;
  int x = find(pos[a][b]);
  comps[x].boja = c;

  vector <int> v;
  if (comps[x].size > MAXN) {
    while (!comps[x].sus[c].empty()) {
      int t = comps[x].sus[c].front();
      comps[x].sus[c].pop();
      if (comps[find(t)].boja != c) continue;
      v.pb(find(t));
    }
  } else {
    for (auto &t : comps[x].veliki) {
      if (comps[find(t)].boja == c) {
        v.pb(find(t));
      }
    }
  }

  FOR(i, 1, (int)v.size()) {
    merge(v[i - 1], v[i]);
  }

  x = find(x);
  for (auto &t : comps[x].veliki) {
    comps[t].sus[comps[x].boja].push(x);
  }
}

void ispis() {
  REP(i, n) {
    REP(j, m) {
      printf("%d ",comps[find(pos[i][j])].boja);
    }
    puts("");
  }
}

int main() {
  REP(i, MAXN * MAXN) par[i] = i;
  scanf("%d %d",&n,&m);
  REP(i, n) REP(j, m) scanf("%d",&p[i][j]);

  int K = 0;
  REP(i, n) {
    REP(j, m) {
      if (!bio[i][j]) { 
        dfs(i, j, K);
        comps.pb(Komponenta(K, p[i][j], sz[K]));
        K++;
      }
    }
  }

  napravi_susjede();
  
  int q;
  scanf("%d",&q);
  REP(i, q) {
    kveri();
  }

  ispis();

  return 0;
}
