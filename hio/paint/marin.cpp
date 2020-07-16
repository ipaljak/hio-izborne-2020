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
const int GRANICA = 320;

const int smjerx[] = {1, -1, 0, 0};
const int smjery[] = {0, 0, -1, 1};

int n, m;

template<class T>
struct Array2d {
  T *operator[](int index) { return &data[index * m]; }
  T data[MAXN * MAXN];
};

int par[MAXN * MAXN];
pii tko[MAXN * MAXN];

Array2d<int> p;
Array2d<int> pos;
int sz[MAXN * MAXN];

Array2d<int> bio;
int cookie;

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

void napravi_veliku(int x, int y, int comp) {
  bio[x][y] = cookie;
  if (find(pos[x][y]) != comp) {
    comps[find(pos[x][y])].veliki.insert(comp);
    comps[comp].sus[get_color(pos[x][y])].push(find(pos[x][y]));
    return;
  }
  REP(i, 4) {
    int nx = x + smjerx[i];
    int ny = y + smjery[i];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    if (bio[nx][ny] == cookie) continue;
    napravi_veliku(nx, ny, comp);
  }
}

void merge(int a, int b) {
  a = find(a); b = find(b);
  if (a == b) return;
  if (comps[a].size < comps[b].size) swap(a, b); // iskreno nemam nikakvog pojima dal je oko ok
  // mozda bi trebalo gledati size + broj susjeda
  
  comps[a].size += comps[b].size;

  // uvijek velike susjede trebam prebaciti
  for (auto &x : comps[b].veliki) {
    comps[a].veliki.insert(x);
  }

  comps[b].veliki.clear(); // redukcija memorije, testirati bez ove linije

  if (comps[b].size > GRANICA) {
    for (auto &t : comps[b].sus) {
      while (!t.sec.empty()) {
        int x = find(t.sec.front());
        t.sec.pop();
        if (get_color(x) != t.fi) continue;
        comps[a].sus[t.fi].push(x);
      }
    }
  }

  // ako je b mala, a a velika, moramo susjede od b staviti u a.sus
  if (comps[b].size <= GRANICA && comps[a].size > GRANICA) {
    int tmpx = tko[b].fi, tmpy = tko[b].sec;
    queue <int> q;
    cookie++;
    q.push(tmpx); q.push(tmpy);
    bio[tmpx][tmpy] = cookie;

    while (!q.empty()) {
      tmpx = q.front(); q.pop();
      tmpy = q.front(); q.pop();
      REP(i, 4) {
        int nx = tmpx + smjerx[i];
        int ny = tmpy + smjery[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (bio[nx][ny] == cookie) continue;
        bio[nx][ny] = cookie;
        if (find(pos[nx][ny]) != b) {
          comps[a].sus[get_color(pos[nx][ny])].push(find(pos[nx][ny]));
          comps[find(pos[nx][ny])].veliki.insert(a);
        } else {
          q.push(nx);
          q.push(ny);
        }
      }
    }
  }

  par[b] = a;
  // ako mala komp postane velika
  if (comps[a].size > GRANICA && comps[a].size - comps[b].size <= GRANICA) {
    cookie++;
    napravi_veliku(tko[a].fi, tko[a].sec, a);
  }
}

void dfs(int x, int y, int k) {
  bio[x][y] = cookie;
  pos[x][y] = k;
  tko[k] = {x, y};
  sz[k]++;
  REP(i, 4) {
    int nx = x + smjerx[i];
    int ny = y + smjery[i];
    if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    if (bio[nx][ny] == cookie || p[nx][ny] != p[x][y]) continue;
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
        if (spojeno.count((ll)min(a,b) * MAXN * MAXN + max(a,b))) continue;
        spojeno[(ll)min(a,b) * MAXN * MAXN + max(a,b)] = 1;
        if (sz[a] > GRANICA) {
          comps[b].veliki.insert(a);
          comps[a].sus[p[nx][ny]].push(b);
        }
        if (sz[b] > GRANICA) {
          comps[a].veliki.insert(b);
          comps[b].sus[p[x][y]].push(a);
        }
      }
    }
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

void bfs(int x, int y, int comp, vector <int> &v, int color) {
  queue <int> q;
  q.push(x);
  q.push(y);
  cookie++;
  bio[x][y] = cookie;

  while (!q.empty()) {
    x = q.front(); q.pop();
    y = q.front(); q.pop();
    
    REP(i, 4) {
      int nx = x + smjerx[i];
      int ny = y + smjery[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
      if (bio[nx][ny] == cookie) continue;
      bio[nx][ny] = cookie;
      if (find(pos[nx][ny]) != comp) {
        if (color == comps[find(pos[nx][ny])].boja) {
          v.pb(find(pos[nx][ny]));
        }
      } else {
        q.push(nx);
        q.push(ny);
      }
    }
  }
}

void kveri() {
  int a, b, c;
  scanf("%d %d %d",&a,&b,&c);
  a--; b--;
  int x = find(pos[a][b]);
  if (comps[x].boja == c) return;
  comps[x].boja = c;

  vector <int> v;
  v.pb(x);
  if (comps[x].size > GRANICA) {
    while (!comps[x].sus[c].empty()) {
      int t = comps[x].sus[c].front();
      comps[x].sus[c].pop();
      if (comps[find(t)].boja != c) continue;
      v.pb(find(t));
    }
    for (auto &t : comps[x].veliki) {
      if (comps[find(t)].boja == c) {
        v.pb(find(t));
      }
    }
  } else {
    bfs(a, b, x, v, c);
  }

  FOR(i, 1, (int)v.size()) {
    merge(v[i - 1], v[i]);
  }

  x = find(x);
  for (auto &t : comps[x].veliki) {
    comps[find(t)].sus[comps[x].boja].push(x);
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
        cookie++;
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
