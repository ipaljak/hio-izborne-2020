#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300000;

int n;
int color[MAXN];


void fill(int x, int col) {
  int orig_c = color[x];
  for (int p = x; p >= 0 && color[p] == orig_c; --p)
    color[p] = col;
  for (int p = x + 1; p < n && color[p] == orig_c; ++p)
    color[p] = col;
}

int get_color(int x) {
  int d = 1;
  if (rand() % 2) d = -1;
  int p = x;
  while (p >= 0 && p < n && color[p] == color[x]) p += d;
  if (p < 0 || p >= n) return rand() % 100;
  return color[p];
}

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  n = atoi(argv[2]);
  int q = atoi(argv[3]);
  int c = 10000;

  for (int i = 0; i < MAXN; ++i) {
    color[i] = rand() % c;
  }

  int cc = rand() % c;
  for (int i = 0; i < n; i += 1 + rand() % 3) {
    color[i] = cc;
  }

  cout << 1 << " " << n << endl;
  for (int i = 0; i < n; ++i) {
    cout << color[i];
    cout << " \n"[i + 1 == n];
  }

  cout << q << endl;
 
  while (q) {
    int p = rand() % n;
    if (rand() % 100 < 90) {
      p = rand() % (n / 10) + (n / 2);
    }
    int col = get_color(p);
    cout << 1 << " " << p+1 << " " << col << endl;
    fill(p, col);
    q--;
  }

  return 0;
}
