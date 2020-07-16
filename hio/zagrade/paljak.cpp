#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

const int MAXN = 1e5 + 10;

int n, q;
char sol[MAXN];

int ask(int a, int b) {
  printf("? %d %d\n", a + 1, b + 1);
  fflush(stdout);
  int ret;
  scanf("%d", &ret);
  return ret;
}

int ans() {
  printf("! %s\n", sol);
  fflush(stdout);
  exit(0);
}

int main(void) {
  scanf("%d %d", &n, &q);
  stack<int> S;
  for (int i = 0; i < n; ++i) {
    if (S.empty()) {
      S.push(i);
      continue;
    }
    int ok = ask(S.top(), i);
    if (ok) {
      sol[S.top()] = '(';
      sol[i] = ')';
      S.pop();
    } else {
      S.push(i);
    }
  }

  assert(S.size() % 2 == 0);
  int x = (int) S.size() / 2;
  for (int i = 0; i < x; ++i) {
    sol[S.top()] = '(';
    S.pop();
  }
  for (int i = 0; i < x; ++i) {
    sol[S.top()] = ')';
    S.pop();
  }

  ans();

  return 0;
}
