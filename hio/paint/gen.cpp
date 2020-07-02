#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  int n = atoi(argv[2]);
  int m = atoi(argv[3]);
  int q = atoi(argv[4]);
  int c = 5;
  if (argc > 5) c = atoi(argv[5]);

  cout << n << " " << m << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << 1 + rand() % c;
      cout << " \n"[j + 1 == m];
    }
  }

  cout << q << endl;
  for (int i = 0; i < q; ++i ) {
    cout << 1 + rand() % n << " ";
    cout << 1 + rand() % m << " ";
    cout << 1 + rand() % c << endl;
  }

  return 0;
}
