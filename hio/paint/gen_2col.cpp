#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  int n = atoi(argv[2]);
  int m = atoi(argv[3]);
  int q = atoi(argv[4]);
  int p = 20;
  if (argc >= 6) p = atoi(argv[5]);

  cout << n << " " << m << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (rand() % 100 == 0) {
        cout << rand() % 2;
      } else {
        cout << (i + j) % 2;
      }
      cout << " \n"[j + 1 == m];
    }
  }

  cout << q << endl;
  for (int i = 0; i < q; ++i) {
    int x = rand() % n;
    int y = rand() % m;
    if (rand() % 100 < p) {
      y = rand() % (2*m/5 + 1);
    }
    cout << x+1 << " " << y+1 << " " << rand() % 2 << endl;
  }

  return 0;
}
