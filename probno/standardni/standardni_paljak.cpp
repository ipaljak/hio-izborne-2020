#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MOD = 1e9 + 7;
const int MAXN = 5e5 + 10;

int w, h, n;

set<int> v_cut, h_cut;
multiset<int> v_sz, h_sz;

void make_cut(int x, set<int> &s_cut, multiset<int> &s_size) {
  auto it_up = s_cut.upper_bound(x);
  auto it_lo = it_up; --it_lo;
  assert(s_size.find(*it_up - *it_lo) != s_size.end());
  s_size.erase(s_size.find(*it_up - *it_lo));
  s_size.insert(x - *it_lo);
  s_size.insert(*it_up - x);
  s_cut.insert(x);
}

int main(void) {
  scanf("%d%d%d", &w, &h, &n);

  v_sz.insert(w);
  h_sz.insert(h);
  v_cut.insert(0); v_cut.insert(w);
  h_cut.insert(0); h_cut.insert(h);

  for (int i = 0; i < n; ++i) {
    char s[2];
    int x;
    scanf("%s%d", s, &x);
    if (s[0] == 'H') make_cut(x, h_cut, h_sz); else make_cut(x, v_cut, v_sz);
    printf("%lld\n", (llint) *v_sz.rbegin() * *h_sz.rbegin());
  }

  return 0;
}
