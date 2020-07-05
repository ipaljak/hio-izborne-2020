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

bool query(int l, int r) {
    cout << "? " << l + 1 << ' ' << r + 1 << endl;
    bool ans;
    cin >> ans;
    return ans;
}

string solve(int l, int r) {
    if (l == r) return "";
    for (int i = l + 1; i < r; i += 2) {
        if (query(l, i))
            return "(" + solve(l + 1, i) + ")" + solve(i + 1, r);
    }
    return "?" + solve(l + 1, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    string sol = solve(0, n);

    int k = count(sol.begin(), sol.end(), '?');
    assert(k % 2 == 0);
    for (int i = 0; i < k; i++) {
        int j = sol.find('?');
        if (i < k / 2) sol[j] = ')';
        else sol[j] = '(';
    }

    cout << "! " << sol << endl;

    return 0;
}

