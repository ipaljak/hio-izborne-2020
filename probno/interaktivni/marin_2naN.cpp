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

map <pii, int> bio;

const int smjerx[] = {0, 1, 0, -1};
const int smjery[] = {1, 0, -1, 0};

const char POMAK[] = "RDLU";

string s[3];

void input() {
  REP(i, 3) cin >> s[i];
}

void pomak(int x) {
  cout << "POMAK " << POMAK[x] << endl;
  cout.flush();
}

int ans = 1;

bool dfs(int x, int y, int d) {
  if (d != ans || (ans == d && ans == 1)) input();
  if (s[1][1] == 'B') return 1;
  if (!d) return 0;

  bio[mp(x, y)] = 1;

  bool ret = 0;
  REP(i, 4) {
    if (ret) continue;
    int nx = x + smjerx[i];
    int ny = y + smjery[i];
    if (bio[mp(nx, ny)]) continue;
    if (s[smjerx[i] + 1][smjery[i] + 1] == '#') continue;
    pomak(i);
    ret |= dfs(nx, ny, d - 1);
    pomak((i + 2) % 4);
    input();
  }
  bio[mp(x, y)] = 0;
  return ret;
}

int main() {
  while (!dfs(0, 0, ans)) {
    bio.clear();
    ans++;
  }
  cout << "! " << ans << endl;
  return 0;
}

