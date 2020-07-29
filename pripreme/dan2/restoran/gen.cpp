// Koristenje:
// ./gen $RANDOM n k [poredak da/ne (bool 0/1, default 1)] [max_a,b, default 1e9]

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  int n = atoi(argv[2]);
  int k = atoi(argv[3]);
  bool provjera = true;
  if (argc > 4) provjera = (bool)atoi(argv[4]);
  int maxval = 1000000000;
  if (argc > 5) maxval = atoi(argv[5]);

  cout << n << " " << k << endl;
  for (int i = 0; i < n; ++i) {
    cout << 1 + rand() % maxval << " " << 1 + rand() % maxval << endl;
  }

  set<int> active;
  for (int i = 0; i < n; ++i)
    active.insert(i);
  
  int poretci = 0;
  if (provjera) {
    poretci = 1 + rand() % min(n / 4, min(k, 10));
  }

  vector<int> mask(k, 0);
  for (int i = 0; i < poretci; ++i)
    mask[i] = 1;
  random_shuffle(mask.begin(), mask.end());
 
  int next_id = n;
  for (auto it : mask) {
    if (it) {
      cout << "POREDAK" << endl;
      continue;
    }
    if (active.empty() || rand() % 2) {
      cout << "DOLAZI " << 1 + rand() % maxval << " " << 1 + rand() % maxval << endl;
      active.insert(next_id++);
    } else {
      auto it = active.lower_bound(rand() % next_id);
      if (it == active.end()) it--;
      cout << "ODLAZI " << (*it + 1) << endl;
      active.erase(it);
    }
  }

  return 0;
}
