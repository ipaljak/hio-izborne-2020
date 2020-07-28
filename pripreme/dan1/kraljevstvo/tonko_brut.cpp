#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<int, int> Pt;

const int N = 5005;

int n, k;
Pt pts[N];

ll ccw(Pt a, Pt b, Pt c) {
  return (ll)a.x * (b.y - c.y) + (ll)b.x * (c.y - a.y) + (ll)c.x * (a.y - b.y);
}

ll solve(vector<Pt> &sub_pts) {
  sort(sub_pts.begin(), sub_pts.end());
  vector<Pt> hull;
  for (int step = 0; step < 2; ++step) {
    auto start = hull.size();
    for (const auto &pt : sub_pts) {
      while (hull.size() >= start + 2 &&
             ccw(hull[hull.size() - 2], hull.back(), pt) >= 0) {
        hull.pop_back();
      }
      hull.push_back(pt);
    }
    hull.pop_back();
    reverse(sub_pts.begin(), sub_pts.end());
  }
  ll area = 0;
  for (size_t i = 0; i < hull.size(); ++i)
    area += ccw({0, 0}, hull[(i + 1) % hull.size()], hull[i]);
  return area;
}

int main(void) {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> pts[i].x >> pts[i].y;
  }

  ll ans = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    if ((mask & 3) != 3 ||
        __builtin_popcount(mask) != k)
      continue;
    vector<Pt> sub_pts;
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i))
        sub_pts.push_back(pts[i]);
    }
    ans = max(ans, solve(sub_pts));
  }

  cout << ans / 2 << (ans % 2 == 0 ? "" : ".5") << endl;

  return 0;
}
