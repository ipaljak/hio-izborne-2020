#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<int, int> Pt;

const int N = 305;

int n, k;
Pt pts[N];
ll up[N];
ll down[N];

ll ccw(Pt a, Pt b, Pt c) {
  return (ll)a.x * (b.y - c.y) + (ll)b.x * (c.y - a.y) + (ll)c.x * (a.y - b.y);
}

void calc(ll *output) {
  ll dp[2][N][N];
  for (int step = 0; step < 2; ++step) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dp[step][i][j] = -(1 << 30);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    output[i] = 0;
    dp[0][0][i] = 0;
  }
  for (int step = 3; step <= n; ++step) {
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        for (int jj = j + 1; jj < n; ++jj) {
          if (ccw(pts[i], pts[j], pts[jj]) >= 0)
            continue;
          ll w = ccw(pts[0], pts[jj], pts[j]);
          dp[1][j][jj] = max(dp[1][j][jj], dp[0][i][j] + w);
        }
      }
    }
    for (int i = 0; i < n - 1; ++i) {
      output[step] = max(output[step], dp[1][i][n - 1]);
      for (int j = 0; j < n; ++j) {
        dp[0][i][j] = dp[1][i][j];
        dp[1][i][j] = -(1 << 30);
      }
    }
  }
}

int main(void) {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> pts[i].x >> pts[i].y;
  }

  sort(pts, pts + n);
  calc(up);
  reverse(pts, pts + n);
  calc(down);

  for (int i = 2; i <= n; ++i) {
    cerr << i << " " << up[i] << " " << down[i] << endl;
  }

  ll ans = 0;
  for (int i = 2; i <= n; ++i) {
    for (int j = 2; j <= n; ++j) {
      if (i + j <= k + 2)
        ans = max(ans, up[i] + down[j]);
    }
  }

  cout << ans / 2 << (ans % 2 == 0 ? "" : ".5") << endl;

  return 0;
}
