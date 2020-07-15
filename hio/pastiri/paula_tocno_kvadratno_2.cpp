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

const int MAXN = 1e6 + 10;

int n, k;
vi e[MAXN], sheep;

int r[MAXN];

vi sol;
bool vis[MAXN];
int p[MAXN];

void input() {
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    sheep.resize(k);
    for (int i = 0; i < k; i++) cin >> sheep[i];
}

void calc_radiuses() {
    fill(r + 1, r + n + 1, -1);
    queue<int> Q;
    for (auto x : sheep) {
        r[x] = 0;
        Q.push(x);
    }

    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();

        for (auto y : e[x]) {
            if (r[y] == -1) {
                r[y] = r[x] + 1;
                Q.push(y);
            }
        }
    }
}

int find_farthest(int x) {
    p[x] = -1;
    queue<int> Q;
    Q.push(x);
    int ret = x;

    while (!Q.empty()) {
        int y = Q.front();
        Q.pop();
        if (r[y] == 0) ret = y;
        
        for (auto z : e[y]) {
            if (z == p[y]) continue;
            if (!vis[z]) {
                p[z] = y;
                Q.push(z);
            }
        }
    }

    return ret;
}

void visit(int x) {
    queue<int> Q;
    Q.push(x);
    while (!Q.empty()) {
        int y = Q.front();
        Q.pop();
        vis[y] = true;

        for (auto z : e[y]) {
            if (r[z] == r[y] - 1 && !vis[z]) Q.push(z);
        }
    }
}

void solve() {
    random_shuffle(sheep.begin(), sheep.end());
    for (auto x : sheep) {
        while (!vis[x]) {
            int y = find_farthest(x);
//            y = find_farthest(y);

            while (p[y] != -1 && r[p[y]] == r[y] + 1) y = p[y];
            sol.push_back(y);
            visit(y);
        }
    }
}

void output() {
    cout << sol.size() << '\n';
    for (auto it : sol) cout << it << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));

    input();

    calc_radiuses();

    solve();

    output();

    return 0;
}

