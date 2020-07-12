#include <cstdio>

typedef long long llint;

using namespace std;

int n;

int main(void) {
  scanf("%d", &n);
  llint p = 0, q = (llint) n * n * n * n * n * n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      p += (llint) (2 * (i + 1) * (n - i) - 1) * (2 * (j + 1) * (n - j) - 1);

  printf("%.10lf\n", (double) p / q);
  return 0;
}
