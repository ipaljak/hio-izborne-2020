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

int n, m;
vector<string> sol;

void initialize() {
    sol.resize(2 * n + 1, string(3 * m + 1, ' '));
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            sol[2 * i][3 * j] = 'o';
}

void add_edge(int x, int y, char dir) {
    if (dir == 'L') sol[2 * x][3 * y - 1] = sol[2 * x][3 * y - 2] = '-';
    if (dir == 'R') sol[2 * x][3 * y + 1] = sol[2 * x][3 * y + 2] = '-';
    if (dir == 'U') sol[2 * x - 1][3 * y] = '|';
    if (dir == 'D') sol[2 * x + 1][3 * y] = '|';
}

void add_edge(const pair<pii, pii>& e) {
    const pii& a = e.fi, b = e.se;
    if (a.fi == b.fi && a.se == b.se + 1) add_edge(a.fi, a.se, 'L');
    if (a.fi == b.fi && a.se == b.se - 1) add_edge(a.fi, a.se, 'R');
    if (a.se == b.se && a.fi == b.fi + 1) add_edge(a.fi, a.se, 'U');
    if (a.se == b.se && a.fi == b.fi - 1) add_edge(a.fi, a.se, 'D');
}

void print() {
    for (auto& row : sol) cout << row << '\n';
}

int ceil(int a, int b) { return (a - 1) / b + 1; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));

    cin >> n >> m;

    initialize();

    vector<pair<pii, pii>> E;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i != n) E.push_back({{i, j}, {i + 1, j}});
            if (j != m) E.push_back({{i, j}, {i, j + 1}});
        }
    }
    random_shuffle(E.begin(), E.end());
    
    vi p((n + 1) * (m + 1));
    iota(p.begin(), p.end(), 0);
    for (auto& e : E) {
        int a = e.fi.fi * (m + 1) + e.fi.se, u = a;
        int b = e.se.fi * (m + 1) + e.se.se, v = b;
    
        while (p[a] != a) a = p[a];
        while (p[b] != b) b = p[b];
        while (u != a) {
            int t = u;
            u = p[t];
            p[t] = a;
        }
        while (v != b) {
            int t = v;
            v = p[t];
            p[t] = b;
        }

        if (a != b) {
            add_edge(e);
            if (rand() & 1) swap(a, b);
            p[a] = b;
        }
    }

    print();

    return 0;
}

