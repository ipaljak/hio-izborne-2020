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

vector<vi> e;
vi in, low;
vector<bool> cutpoint, ok;
vi comp_sz;

int t = 0;
stack<int> S;
vector<vi> blocks;
void dfs(int x, int p = -1) {
    comp_sz.back()++;
    in[x] = low[x] = t++;
    int cnt = 0;
    S.push(x);

    for (auto y : e[x]) {
        if (y == p) continue;
        if (in[y] != -1) low[x] = min(low[x], in[y]);
        else {
            dfs(y, x);
            low[x] = min(low[x], low[y]);
            cnt++;
            if (low[y] >= in[x]) {
                cutpoint[x] = (p != -1 || cnt > 1);
                
                blocks.push_back({x});
                while (blocks.back().back() != y) {
                    blocks.back().push_back(S.top());
                    S.pop();
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    e.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    in.resize(n, -1);
    low.resize(n, -1);
    cutpoint.resize(n, false);
    ok.resize(n, true);
    for (int i = 0; i < n; i++) {
        if (in[i] != -1) continue;
        comp_sz.push_back(0);
        S = stack<int>();
        blocks.clear();
        dfs(i);

        for (auto& block : blocks) {
            int p = -1;
            for (auto x : block) {
                if (!cutpoint[x])
                    ok[x] = (int)e[x].size() + 1 != (int)comp_sz.back();
                else if (p == -1) p = x;
                else p = -2;
            }

            if (p < 0) continue;
            int cnt = 0;
            for (auto x : block)
                for (auto y : e[x])
                    if (y == p) cnt++;
            if (cnt + 1 == (int)block.size()) ok[p] = false;
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) cnt += ok[i];

    if (comp_sz.size() == 1) {
        cout << "0\n1\n";
    } else if (cnt != 0) {
        cout << "1\n" << cnt << '\n';
    } else if (comp_sz.size() == 2) {
        int k = min(comp_sz[0], comp_sz[1]), sol = 1;
        for (int i = 2; i <= k; i++) sol = (ll)sol * i % MOD;
        if (comp_sz[0] == comp_sz[1]) sol = (ll)sol * 2 % MOD;
        cout << k << '\n' << sol << '\n';
    } else {
        ll sol = 0;
        for (auto i : comp_sz) {
            if (i == 2) sol += 2 * (n - 1);
            else sol += (ll)i * (n - i);
        }
        cout << "2\n" << sol << '\n';
    }

    return 0;
}

