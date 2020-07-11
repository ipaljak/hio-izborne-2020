#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 1e6 + 10;

llint vrati_broj(string s) {
  llint ret = 0;
  REP(i, (int) s.size())
    ret = 10 * ret + s[i] - '0';
  return ret;
}

int main() {
  string s;
  cin >> s;
  llint n;
  cout << fixed;
  if((int) s.size() <= 12) {
    n = vrati_broj(s);
    if(n >= 1e6)
      cout << setprecision(10) << 1.0 / 9 + 2.0 / 3 / n << endl;
    else if(n >= 1e4)
      cout << setprecision(10) << 1.0 / 9 + 2.0 / 3 / n + 7.0 / 9 / n / n << endl;
    else if(n >= 1e3)
      cout << setprecision(10) << 1.0 / 9 + 2.0 / 3 / n + 7.0 / 9 / n / n - 2.0 / 3 / n / n / n << endl;
    else
      cout << setprecision(10) << 1.0 / 9 + 2.0 / 3 / n + 7.0 / 9 / n / n - 2.0 / 3 / n / n / n + 1.0 / 9 / n / n / n / n << endl;
  }
  else
    cout << setprecision(10) << 1.0 / 9 << endl;
  return 0;
}

