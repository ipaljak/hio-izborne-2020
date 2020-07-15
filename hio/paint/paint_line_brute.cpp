#include <bits/stdc++.h>
using namespace std;

int tmp;
int n, col[300000];

int main(void) {
  scanf("%d%d", &tmp, &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &col[i]);
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    int p, color;
    scanf("%d%d%d", &tmp, &p, &color);
    p--;
    int old_color = col[p];
    for (int pos = p; pos >= 0 && col[pos] == old_color; --pos)
      col[pos] = color;
    for (int pos = p + 1; pos < n && col[pos] == old_color; ++pos)
      col[pos] = color;
  }

  for (int i = 0; i < n; ++i) {
    printf("%d%c", col[i], " \n"[i + 1 == n]);
  }

  return 0;
}
