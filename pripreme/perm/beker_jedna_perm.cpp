#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e3 + 5;
const int MOD = 1e9 + 7;

int N, K;
int perm[MAXN];

void load() {
  scanf("%d%d", &K, &N);
  assert(K == 1);
  for (int i = 1; i <= N; i++)
    scanf("%d", perm + i);  
}

inline void add(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
}

inline int mul(int x, int y) {
  return (long long)x * y % MOD;
}

int pot(int x, int y) {
  int res = 1;
  for (; y; y /= 2) {
    if (y % 2)
      res = mul(res, x);
    x = mul(x, x);
  }
  return res;
}

int calc_cycles(const vector <int> &cyc1, const vector <int> &cyc2) {
  int len1 = cyc1.size();
  int len2 = cyc2.size();
  int gcd = __gcd(len1, len2);
  int lcm = len1 * len2 / gcd;
  vector <int> normal(gcd), inverted(gcd);
  for (int i = 0; i < len1; i++)
    for (int j = 0; j < len2; j++)
      if (cyc1[i] < cyc2[j])
        normal[(i - j + gcd) % gcd]++;
      else if (cyc1[i] > cyc2[j])
        inverted[(i - j + gcd) % gcd]++;
  int res = 0;
  for (int i = 0; i < gcd; i++)
    add(res, mul(normal[i], inverted[i]));
  return mul(res, pot(lcm, MOD - 2)); 
}

int solve() {
  vector <bool> bio(N + 1);
  vector <vector <int>> cycles;
  for (int i = 1; i <= N; i++) {
    vector <int> tmp;
    for (int x = i; !bio[x]; x = perm[x]) {
      tmp.push_back(x);
      bio[x] = true;
    }
    if (!tmp.empty())
      cycles.push_back(tmp);
  }
  
  int sol = 0;
  for (auto it1 : cycles)
    for (auto it2 : cycles)
      add(sol, calc_cycles(it1, it2));
  
  return sol;
}

int main() {
  load();
  printf("%d\n", solve());
  return 0;
}
