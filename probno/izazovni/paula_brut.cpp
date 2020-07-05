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

int manacher(const string& s) {
    int n = s.size();

    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    int l1 = 2 * (*max_element(d1.begin(), d1.end())) - 1;

    vector<int> d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
    int l2 = 2 * (*max_element(d2.begin(), d2.end()));

    return max(l1, l2);
}

string bin(int a, int n) {
    string s(n, 0);
    for (int i = 0; i < n; i++) s[i] = '0' + ((a >> i) & 1);
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int sol = 1e9;
    string sol_s;

    for (int mask = 0; mask < (1 << n); mask++) {
        string s = bin(mask, n);
        int m = manacher(s);
        
        if (m < sol) {
            sol = m;
            sol_s = s;
        }
    }

    cout << sol_s << '\n';
    TRACE(sol);

    return 0;
}

