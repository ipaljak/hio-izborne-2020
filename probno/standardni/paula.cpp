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

int max_diff(set<int>& S) {
    int max_dx = 0;
    for (auto it1 = S.begin(), it2 = ++S.begin(); it2 != S.end(); ++it1, ++it2)
        max_dx = max(max_dx, *it2 - *it1);
    return max_dx;
}

void update(int x, set<int>& S, int& max_dx) {
    S.erase(x);
    auto it1 = S.lower_bound(x), it2 = it1--;
    max_dx = max(max_dx, *it2 - *it1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int a, b, n;
    cin >> a >> b >> n;
    
    set<int> X = {0, a}, Y = {0, b};
    vector<pair<char, int>> q(n);
    for (auto& it : q) {
        cin >> it.fi >> it.se;
        if (it.fi == 'H') Y.insert(it.se);
        else X.insert(it.se);
    }
    reverse(q.begin(), q.end());

    int max_dx = max_diff(X), max_dy = max_diff(Y);
    vector<ll> sol;
    for (auto& it : q) {
        sol.push_back((ll)max_dx * max_dy);
        if (it.fi == 'H') update(it.se, Y, max_dy);
        else update(it.se, X, max_dx);
    }
    reverse(sol.begin(), sol.end());

    for (auto it : sol) cout << it << '\n';

    return 0;
}

