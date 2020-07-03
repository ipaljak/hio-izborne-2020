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

const char KRAJ = 'Y'; // ovo promjeniti ovisno o tekstu

map <pii, int> bio, mapa;

const int smjerx[] = {0, 1, 0, -1};
const int smjery[] = {1, 0, -1, 0};

const char POMAK[] = "RDLU";

string s[3];

void pomak(int x) {
  cout << "POMAK " << POMAK[x] << endl;
  cout.flush();
}

void input() {
  REP(i, 3) cin >> s[i];
}

pii LAST;

void dfs(int x, int y) {
  TRACE(x _ y);
  input();
  TRACE("poslije");
  bio[mp(x, y)] = 1;
  if (s[1][1] == KRAJ) LAST = mp(x, y);
  REP(i, 4) {
    int nx = 1 + smjerx[i];
    int ny = 1 + smjery[i];
    if (s[nx][ny] == '#' || bio.count(mp(x + smjerx[i],y + smjery[i]))) continue;
    pomak(i);
    dfs(x + smjerx[i], y + smjery[i]);
    pomak((i + 2) % 4);
    input();
  }
}

int solve(int x, int y) {
  mapa = bio;
  bio.clear();
  queue <int> q;
  q.push(x);
  q.push(y);
  q.push(0);
  bio[mp(x, y)] = 1;
  int d;
  while (!q.empty()) {
    x = q.front(); q.pop();
    y = q.front(); q.pop();
    d = q.front(); q.pop();
    if (mp(x, y) == LAST) return d;
    REP(i, 4) {
      int nx = x + smjerx[i];
      int ny = y + smjery[i];
      if (mapa.count(mp(x, y))) {
        q.push(nx);
        q.push(ny);
        q.push(d + 1);
      }
    }
  }
  return -1;
}

int main() {
  dfs(0, 0);
  TRACE("vani");
  cout << "! " << solve(0, 0) << endl;
  cout.flush();
  return 0;
}

