#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

using Guest = pair<int, pair<int, int>>;

int n, k;
vector<Guest> v, order;

llint get_time() {
  llint eat_queue = 0;
  llint total = 0;
  for (const auto &p : v) {
    int a = p.second.first, b = p.second.second;
    eat_queue = max(0LL, eat_queue - (llint) a);
    total += a;
    eat_queue += (llint) b;
  }
  return total + eat_queue;
}

  int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    v.push_back({i, {a, b}});
  }

  assert(k == 1);

  sort(v.begin(), v.end());
  llint sol = 1e18;
  do {
    int t = get_time();
    if (t < sol) {
      sol = t;
      order = v;
    }
  } while (next_permutation(v.begin(), v.end()));

  printf("%lld\n", sol);
  for (const auto &p : order) printf("%d ", p.first + 1);
  for (const auto &p : order) printf("%d ", p.first + 1);
  printf("\n");

  return 0;
}
