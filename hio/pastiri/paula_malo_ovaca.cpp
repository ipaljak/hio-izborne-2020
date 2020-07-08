// složenost: O(N + 3^K)

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

const int MAXN = 1e6 + 10, MAXK = 20;

vi e[MAXN];
int r[MAXN], sheep[MAXN];
int shepherd[1 << MAXK];
vi sol[1 << MAXK];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    fill(r + 1, r + n + 1, -1);
    fill(shepherd, shepherd + (1 << k), -1);

    queue<int> Q;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        Q.push(x);
        r[x] = 0;
        sheep[x] = 1 << i;
    }

    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();

        if (shepherd[sheep[x]] == -1) shepherd[sheep[x]] = x;

        for (auto y : e[x]) {
            if (r[y] == -1) {
                r[y] = r[x] + 1;
                Q.push(y);
            }
            if (r[y] == r[x] + 1) {
                sheep[y] |= sheep[x];
            }
        }
    }

    for (int mask = 1; mask < (1 << k); mask++) {
        for (int submask = mask; submask != 0; submask = (submask - 1) & mask) {
            if (shepherd[submask] == -1) continue;
            if (sol[mask].empty() ||
                (int)sol[mask ^ submask].size() + 1 < (int)sol[mask].size()) {
                sol[mask] = sol[mask ^ submask];
                sol[mask].push_back(shepherd[submask]);
            }
        }

        for (int submask = mask; submask != 0; submask = (submask - 1) & mask) {
            if ((int)sol[mask].size() < (int)sol[submask].size())
                sol[submask] = sol[mask];
        }
    }

    cout << sol[(1 << k) - 1].size() << '\n';
    for (auto it : sol[(1 << k) - 1]) cout << it << ' ';
    cout << '\n';

    return 0;
}

