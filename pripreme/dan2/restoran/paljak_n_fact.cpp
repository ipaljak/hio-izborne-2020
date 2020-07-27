#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

int n, q;
vector<pair<int, int>> v;

llint get_time() {
  llint eat_queue = 0;
  llint total = 0;
  for (const auto &p : v) {
    int a = p.first, b = p.second;
    eat_queue = max(0LL, eat_queue - (llint) a);
    total += a;
    eat_queue += (llint) b;
  }
  return total + eat_queue;
}

int main(void) {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    v.emplace_back(a, b);
  }

  assert(q == 0);

  sort(v.begin(), v.end());
  llint sol = 1e18;
  do {
    sol = min(sol, get_time());
  } while (next_permutation(v.begin(), v.end()));

  printf("%lld\n", sol);

  return 0;
}
