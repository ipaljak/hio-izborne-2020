#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef pair<int, int> Pt;
typedef long long ll;

const int N = 3010;

int n, k;
ll dp[2][N];
ll hull_dp[2][N];
int hull_sz[2];

ll ccw(Pt a, Pt b, Pt c) {
  return (ll)a.x * (b.y - c.y) + (ll)b.x * (c.y - a.y) + (ll)c.x * (a.y - b.y);
}

ll w(const vector<Pt> &pts, int i, int j) {
  return abs(ccw(pts[0], pts[i], pts[j]));
}

void f(const vector<Pt> &hull, int lox, int hix, int lok, int hik) {
  if (lox > hix) return;
  int mid = (lox + hix) / 2;
  int opt = lox;
  for (int i = lok; i <= hik; ++i) {
    if (i >= mid) break;
    ll cost = dp[0][i] + w(hull, i, mid);
    if (cost >= dp[1][mid]) {
      dp[1][mid] = cost;
      opt = i;
    }
  }
  f(hull, lox, mid - 1, lok, opt);
  f(hull, mid + 1, hix, opt, hik);
}

int main(void) {
  cin >> n >> k;
  vector<Pt> pts;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    pts.emplace_back(x, y);
  }

  vector<vector<ll>> hull_dp;
  sort(pts.begin(), pts.end());
  
  for (int step = 0; step < 2; ++step) {
    vector<Pt> hull;
    for (const auto &pt : pts) {
      while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), pt) >= 0)
        hull.pop_back();
      hull.push_back(pt);
    }

    const int sz = hull.size();
    
    dp[0][0] = 0;
    for (int i = 1; i < sz; ++i)
      dp[0][i] = -(1 << 30);
    
    vector<ll> hull_dp_current;
    for (int i = 1; i < sz; ++i) {
      for (int j = 0; j < sz; ++j)
        dp[1][j] = 0;
      f(hull, 0, sz - 1, 0, sz - 1);
      for (int j = 0; j < sz; ++j)
        swap(dp[0][j], dp[1][j]);
      hull_dp_current.push_back(dp[0][sz - 1]);
    }

    hull_dp.push_back(hull_dp_current);
    reverse(pts.begin(), pts.end());
  }
  
  ll ans = 0;
  for (int i = 0; i < hull_dp[0].size(); ++i) {
    for (int j = 0; j < hull_dp[1].size(); ++j) {
      if (i + j <= k - 2)
        ans = max(ans, hull_dp[0][i] + hull_dp[1][j]);
    }
  }

  cout << ans / 2 << (ans % 2 == 0 ? "" : ".5") << endl;

  return 0;
}
