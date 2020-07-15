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

int r[MAXN], cnt[MAXN];

vi sol;
bool vis[MAXN];

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
    fill(cnt + 1, cnt + n + 1, 0);
    queue<int> Q;
    for (auto x : sheep) {
        r[x] = 0;
        cnt[x] = 1;
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
            if (r[y] == r[x] + 1) {
                cnt[y] += cnt[x];
            }
        }
    }
}

int find_best(int x) {
    int best = x;
    queue<int> Q;
    Q.push(x);
    while (!Q.empty()) {
        int y = Q.front();
        Q.pop();
        if (cnt[y] > cnt[best]) best = y;

        for (auto z : e[y]) {
            if (r[z] == r[y] + 1)
                Q.push(z);
        }
    }
    return best;
}

void decrease_count(int x) {
    queue<int> Q;
    Q.push(x);
    while (!Q.empty()) {
        int y = Q.front();
        Q.pop();
        cnt[y]--;

        for (auto z : e[y]) {
            if (r[z] == r[y] + 1) Q.push(z);
        }
    }
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

        if (r[y] == 0) decrease_count(y);
    }
}

void solve() {
    random_shuffle(sheep.begin(), sheep.end());

    for (auto x : sheep) {
        if (vis[x]) continue;
        int y = find_best(x);
        sol.push_back(y);
        visit(y);
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

