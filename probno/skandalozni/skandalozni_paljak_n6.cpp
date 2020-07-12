#include <algorithm>
#include <cstdio>

using namespace std;

int n;

int main(void) {
  scanf("%d", &n);
  int p = 0, q = 0;
  for (int a = 0; a < n; ++a) {
    for (int b = 0; b < n; ++b) {
      for (int c = 0; c < n; ++c) {
        for (int d = 0; d < n; ++d) {
          for (int e = 0; e < n; ++e) {
            for (int f = 0; f < n; ++f) {
              // (a, b) -- (a, c) && (e, d) -- (f, d)
              ++q;
              p += min(b, c) <= d && d <= max(b, c) &&
                   min(e, f) <= a && a <= max(e, f);
            }
          }
        }
      }
    }
  }

  printf("%.10lf\n", (double) p / q);
  return 0;
}
