#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 1e5 + 10;

int n;
int a[MAXN], b[MAXN];

int get_min(int lo, int hi, int *arr) {
  int ret = arr[lo];
  for (int i = lo + 1; i <= hi; ++i)
    ret = min(ret, arr[i]);
  return ret;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d%d", &a[i], &b[i]);

  llint sol = 0;
  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j)
      sol = max(sol, (llint) (j - i + 1) * get_min(i, j, a) * get_min(i, j, b));

  printf("%lld\n", sol);
  return 0;
}
