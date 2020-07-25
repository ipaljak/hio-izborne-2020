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
  int n = points.size(), m = 0;
  for (int i = 0; i < n; i++) {
    while (m >= 2 && ccw(points[i], points[m - 1], points[m - 2]) <= 0) m--;
    points[m++] = points[i];
  }
  points.resize(m);
  n = m;

  vll dp(n), prev(n), sol(n - 1);
  for (int i = 0; i < n; i++) prev[i] = area(points[0], points[i]);

  vi p = {n / 2}, l(n), r(n), lo = {0}, hi = {n};
  for (int i = 0; i < n; i++) {
    if (lo[i] != p[i]) {
      l[p[i]] = (lo[i] + p[i]) / 2;
      p.push_back(l[p[i]]);
      lo.push_back(lo[i]);
      hi.push_back(p[i]);
    } else l[p[i]] = -1;
    if (p[i] + 1 != hi[i]) {
      r[p[i]] = (p[i] + 1 + hi[i]) / 2;
      p.push_back(r[p[i]]);
      lo.push_back(p[i] + 1);
      hi.push_back(hi[i]);
    } else r[p[i]] = -1;
  }
  vi mi(n), ma(n);

  for (int k = 1; k < n - 1; k++) {
    mi[p[0]] = 0;
    ma[p[0]] = n;
    for (int i : p) {
      dp[i] = 0;
      int opt = mi[i];
      for (int j = mi[i]; j < min(i, ma[i]); j++) {
        ll a = prev[j] + area(points[j], points[i]);
        if (a > dp[i]) {
          dp[i] = a;
          opt = j;
        }
      }

      if (l[i] != -1) {
        mi[l[i]] = mi[i];
        ma[l[i]] = opt + 1;
      }
      if (r[i] != -1) {
        mi[r[i]] = opt;
        ma[r[i]] = ma[i];
      }
    }
    sol[k] = dp[n - 1];
    prev = dp;
  }

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

