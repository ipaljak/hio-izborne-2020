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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    
    string sol(n, 0);
    stack<int> S;

    for (int i = 0; i < n; i++) {
        if (!S.empty() && query(S.top(), i)) {
            sol[S.top()] = '(';
            sol[i] = ')';
            S.pop();
        } else {
            S.push(i);
        }
    }

    int k = S.size();
    assert(k % 2 == 0);
    for (int i = 0; i < k; i++) {
        if (i < k / 2) sol[S.top()] = '(';
        else sol[S.top()] = ')';
        S.pop();
    }

    cout << "! " << sol << endl;

    return 0;
}

