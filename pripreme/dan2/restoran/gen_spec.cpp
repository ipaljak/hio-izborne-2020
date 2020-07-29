// Koristenje:
// ./gen seed n k [poredak da/ne (bool 0/1, default 1)]

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  int n = atoi(argv[2]);
  int k = atoi(argv[3]);
  bool provjera = true;
  if (argc > 4) provjera = (bool)atoi(argv[4]);
  int maxval = 10000000;

  cout << n << " " << k << endl;
  vector<pair<int, int>> vvv;

  auto randval = [maxval](){
    return 20000 + rand() % (maxval - 2*20000);
  };

  for (int i = 0; i < n; ++i) {
    if (i < n/2) vvv.push_back({2*i+1, 2*i+2});
    else vvv.push_back({maxval-2*i, maxval-2*i-1});
  }
  
  random_shuffle(vvv.begin(), vvv.end());
  for (auto it : vvv) {
    cout << it.first << " " << it.second << endl;
  }

  set<int> active;
  for (int i = 0; i < n; ++i)
    active.insert(i);
  
  int poretci = 0;
  if (provjera && k > 0) {
    poretci = 1 + rand() % (1+min(n / 4, min(k, 10)));
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
      cout << "DOLAZI " << randval() << " " << randval() << endl;
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
