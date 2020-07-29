#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<bool>> e(n, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        e[x][y] = e[y][x] = true;
    }

    int sol_len = 1e9, sol_cnt = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<bool> on(n), vis(n, false);
        for (int i = 0; i < n; i++) on[i] = mask & (1 << i);

        queue<int> Q;
        Q.push(0);
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (int y = 0; y < n; y++)
                if (e[x][y] != (on[x] != on[y])) Q.push(y);
        }

        if (find(vis.begin(), vis.end(), false) != vis.end()) continue;
        int len = __builtin_popcount(mask);
        if (len < sol_len) {
            sol_len = len;
            sol_cnt = 1;
        } else if (len == sol_len) {
            sol_cnt++;
        }
    }

    for (int i = 2; i <= sol_len; i++) sol_cnt = (ll)sol_cnt * i % MOD;
    cout << sol_len << '\n' << sol_cnt << '\n';

    return 0;
}

