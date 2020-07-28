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

int n, m, N, M;

struct Solution {
    vector<string> sol;

    Solution() {
        sol.resize(N, string(M, ' '));
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

    int score() {
        int score = 0;
        for (int i = 1; i < N; i += 2) {
            int cnt = 0;
            for (int j = 0; j < M; j += 3) cnt += sol[i][j] == '|';
            score = max(score, cnt);
        }
        for (int j = 1; j < M; j += 3) {
            int cnt = 0;
            for (int i = 0; i < N; i += 2) cnt += sol[i][j] == '-';
            score = max(score, cnt);
        }
        return score;
    }
};

int ceil(int a, int b) { return (a - 1) / b + 1; }

Solution duguljaste() {
    Solution S;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            if (j <= n && i != 0) S.add_edge(i, j, 'U');
            else if (j != 0) S.add_edge(i, j, 'L');
    return S;
}

Solution skoro_kvadratne() {
    Solution S;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++)
            if (i % 2 == 0 || i == n) S.add_edge(i, j, 'R');
            else if (j < m / 2) S.add_edge(i, j, 'U');
            else S.add_edge(i, j, 'D');
        if (i != n) S.add_edge(i, m, 'D');
    }
    return S;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    N = 2 * n + 1, M = 3 * m + 1;

    auto S1 = duguljaste();
    auto S2 = skoro_kvadratne();

    int score = min(S1.score(), S2.score());
    if (S1.score() == score) S1.print();
    else S2.print();

    return 0;
}

