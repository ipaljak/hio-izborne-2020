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


const int MAXN = 1010;

int n, m;

vector <vector <char> > s;

int bio[MAXN][MAXN], cookie;

const int smjerx[] = {1, -1, 0, 0};
const int smjery[] = {0, 0, 1, -1};

pii get(int X, int Y) {
  vector <pii> v;
  cookie++;
  queue <int> q;
  q.push(X);
  q.push(Y);
  bio[X][Y] = cookie;
  int x, y;
  while (!q.empty()) {
    x = q.front(); q.pop();
    y = q.front(); q.pop();
    v.pb({x, y});
    REP(i, 4) {
      int nx = x + smjerx[i];
      int ny = y + smjery[i];
      if (bio[nx][ny] == cookie || s[nx][ny] == '#') continue;
      bio[nx][ny] = cookie;
      q.push(nx); q.push(ny);
    }
  }
  if (q.size() == 1) return {-1, -1};
  int r = rand()%(int)v.size();
  while (v[r] == mp(X, Y)) r = rand()%(int)v.size();
  return v[r];
}

void special(int n, int m) {
  puts("1 1");
  s[1][m] = 'B';
  FOR(i, 1, m) s[1][i] = '.';
  REP(i, n + 2) {
    REP(j, m + 2) {
      printf("%c",s[i][j]);
    }
    puts("");
  }
  exit(0);
}

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  int n = atoi(argv[2]);
  int m = atoi(argv[3]);
  int per = atoi(argv[4]);

  printf("%d %d\n",n+2,m+2);

  s.resize(n + 2);
  REP(i, n + 2) s[i].resize(m + 2);

  REP(i, n + 2) REP(j, m + 2) s[i][j] = '#';

  if (n == 1) special(n, m);

  vector <pii> tocke;
  FOR(i, 1, n + 1) {
    FOR(j, 1, m + 1) {
      if (rand()%100 < per) s[i][j] = '.';
      if (s[i][j] == '.') tocke.pb({i, j});
    }
  }

  int a = rand()%(int)tocke.size();
  pii b = get(tocke[a].fi, tocke[a].sec);

  while (b == mp(-1, -1)) {
    a = rand()%(int)tocke.size();
    b = get(tocke[a].fi, tocke[a].sec);
  }

  s[b.fi][b.sec] = 'B';

  printf("%d %d\n",tocke[a].fi, tocke[a].sec);

  REP(i, n + 2) {
    REP(j, m + 2) printf("%c",s[i][j]);
    puts("");
  }

  return 0;
}

