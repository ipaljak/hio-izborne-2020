#include <cstdio>

using namespace std;

long double n;

int main(void) {
  scanf("%Lf", &n);
  printf("%.10Lf\n", 1.0 / (9.0 * n * n * n * n) - 2.0 / (3.0 * n * n * n) +
                     7.0 / (9.0 * n * n) + 2.0 / (3.0 * n) + 1.0 / 9.0);
  return 0;
}
