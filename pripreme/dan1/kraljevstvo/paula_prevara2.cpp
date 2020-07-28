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
    for (int k = 1; k < n - 1; k++) {
        for (int i = 0; i < n; i++) {
            dp[i] = 0;
            for (int j = max(0, i - 500); j < i; j++)
                dp[i] = max(dp[i], prev[j] + area(points[j], points[i]));
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

