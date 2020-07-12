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

const int MAXN = 1000010;
const int smjerx[] = {1, 0, -1, 0};
const int smjery[] = {0, 1, 0, -1};

int n, m;

vector <vector <int> > p, nju, old, bio;
int cookie;

vector <int> color, ncolor;
vector <int> v[MAXN];

void rebuild() {
  old = nju;
  cookie++;

  int cnt = 0;
  queue <pii> q;

  REP(i, n) {
    REP(j, m) {
      if (bio[i][j] != cookie) {
        q.push({i, j});
        bio[i][j] = cookie;
        int x, y;
        while (!q.empty()) {
          x = q.front().fi;
          y = q.front().sec;
          q.pop();
          nju[x][y] = cnt;
          REP(k, 4) {
            int nx = x + smjerx[k];
            int ny = y + smjery[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || bio[nx][ny] == cookie) continue;
            if (color[old[nx][ny]] != color[old[x][y]]) continue;
            q.push({nx, ny});
            bio[nx][ny] = cookie;
          }
        }
      }
      ncolor[cnt] = color[old[i][j]];
      cnt++;
    }
  }

  REP(i, n * m) v[i].clear();
  color = ncolor;

  REP(i, n) {
    REP(j, m) {
      REP(k, 4) {
        int nx = i + smjerx[k];
        int ny = j + smjery[k];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        if (color[nju[i][j]] != color[nju[nx][ny]]) {
          v[nju[i][j]].pb(nju[nx][ny]);
          v[nju[nx][ny]].pb(nju[i][j]);
        }
      }
    }
  }
}

int Bio[MAXN];

void kveri() {
  int a, b, c;
  scanf("%d %d %d",&a,&b,&c);
  a--; b--;
  cookie++;
  int start = nju[a][b];
  Bio[start] = cookie;
  int cvor;
  queue <int> q;
  q.push(start);
  while (!q.empty()) {
    cvor = q.front();
    q.pop();
    for (auto &ncvor : v[cvor]) {
      if (Bio[ncvor] == cookie || color[ncvor] != color[cvor]) continue;
      q.push(ncvor);
      Bio[ncvor] = cookie;
    }
    color[cvor] = c;
  }
}

int main() {
  scanf("%d %d",&n,&m);
  
  p.resize(n);
  REP(i, n) p[i].resize(m);

  color.resize(n * m);
  ncolor = color;

  nju = old = bio = p;

  REP(i, n) {
    REP(j, m) {
      scanf("%d",&p[i][j]);
      nju[i][j] = i * m + j;
      color[nju[i][j]] = p[i][j];
    }
  }


  int q;
  scanf("%d",&q);

  int K = sqrt(q);

  REP(i, q) {
    if (i % K == 0) rebuild();
    kveri();
  }

  REP(i, n) {
    REP(j, m) printf("%d ",color[nju[i][j]]);
    puts("");
  }

  return 0;
}

