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

void print() {
    for (auto& row : sol) cout << row << '\n';
}

int ceil(int a, int b) { return (a - 1) / b + 1; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    initialize();

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            if (j <= n && i != 0) add_edge(i, j, 'U');
            else if (j != 0) add_edge(i, j, 'L');

    print();

    return 0;
}

