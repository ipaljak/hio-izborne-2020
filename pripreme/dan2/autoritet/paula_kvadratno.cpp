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
    vector<vi> e(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        vector<bool> vis(n, false);
        bool ok = true;

        for (int j = 0; j < n; j++) {
            if (j == i || vis[j]) continue;
            int all = 0, con = 0;

            queue<int> Q;
            Q.push(j);
            while (!Q.empty()) {
                int x = Q.front();
                Q.pop();
                if (vis[x]) continue;
                vis[x] = true;
                all++;
                
                for (auto y : e[x]) {
                    if (y == i) con++;
                    else Q.push(y);
                }
            }

            if (all == con) ok = false;
        }

        if (ok) cnt++;
    }

    vector<bool> vis(n, false);
    vi sz;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        sz.push_back(0);

        queue<int> Q;
        Q.push(i);
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            if (vis[x]) continue;
            vis[x] = true;
            sz.back()++;
            
            for (auto y : e[x]) Q.push(y);
        }
    }

    if (sz.size() == 1) {
        cout << "0\n1\n";
    } else if (cnt != 0) {
        cout << "1\n" << cnt << '\n';
    } else if (sz.size() == 2) {
        int k = min(sz[0], sz[1]), sol = 1;
        for (int i = 2; i <= k; i++) sol = (ll)sol * i % MOD;
        if (sz[0] == sz[1]) sol = (ll)sol * 2 % MOD;
        cout << k << '\n' << sol << '\n';
    } else {
        ll sol = 0;
        for (auto i : sz) {
            if (i == 2) sol += 2 * (n - 1);
            else sol += (ll)i * (n - i);
        }
        cout << "2\n" << sol << '\n';
    }

    return 0;
}

