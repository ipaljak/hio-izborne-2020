#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

ll ccw(const pll& a, const pll& b, const pll& c) {
  return a.fi * (b.se - c.se)
       + b.fi * (c.se - a.se)
       + c.fi * (a.se - b.se);
}

ll area(const pll& a, const pll& b) {
  return (b.fi - a.fi) * (a.se + b.se);
}

vll solve(vector<pll> points) {
  sort(points.begin(), points.end());
  int n = points.size();

  vll sol(n - 1);
  for (int mask = 0; mask < (1 << (n - 2)); mask++) {
    int m = 0;
    vector<pll> hull;
    for (int i = 0; i < n; i++) {
      if (i != 0 && i != n - 1 && !((1 << (i - 1)) & mask)) continue;
      while (m >= 2 && ccw(points[i], hull[m - 1], hull[m - 2]) <= 0) m--;
      hull.push_back(points[i]);
      m++;
    }
    ll a = 0;
    for (int i = 0; i < m - 1; i++) a += area(hull[i], hull[i + 1]);
    sol[m - 2] = max(sol[m - 2], a);
  }

  for (int i = 1; i < n - 1; i++) sol[i] = max(sol[i], sol[i - 1]);
  return sol;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<pll> up, down;
    for (int i = 0; i < n; i++) {
      ll x, y;
      cin >> x >> y;
      if (y >= 0) up.push_back({x, y});
      if (y <= 0) down.push_back({x, -y});
    }

    vll dp1 = solve(up), dp2 = solve(down);
    int k1 = (int)dp1.size() - 1, k2 = (int)dp2.size() - 1;
    k = min(k - 2, k1 + k2);
    ll sol = 0;
    for (int i = max(0, k - k2); i <= min(k1, k); i++)
      sol = max(sol, dp1[i] + dp2[k - i]);

    cout << sol / 2;
    if (sol % 2) cout << ".5";
    cout << '\n';

    return 0;
}

