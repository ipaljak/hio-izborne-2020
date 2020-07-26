/// Koristit kao:
/// ./gen $RANDOM n k [m]

#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

double random(double lo, double hi) {
  const int mx = 1000000;
  double k = (rand() % (mx + 1)) / (double)mx;
  return k * (hi - lo) + lo;
}

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  int n = atoi(argv[2]);
  int k = atoi(argv[3]);
  int m = 100;
  if (argc > 4) m = atoi(argv[4]);

  cout << n << " " << k << endl;
  
  set<pair<int, int>> pts;
  pts.insert({0, 0});
  pts.insert({m, 0});
  
  double r = m / 2.0 - 0.5;
  
  while (pts.size() < n) {
    double alpha = random(-pi, pi);
    double x = cos(alpha) * r;
    double y = sin(alpha) * r;
    if (rand() % 100 < 40) {
      x *= random(0.8, 1);
      y *= random(0.8, 1);
    }
    x = round(x + m / 2.0);
    y = round(y);
    if (x <= 0 || x >= m) continue;
    pts.insert({x, y});
  }

  for (const auto &pt : pts) {
    cout << pt.first << " " << pt.second << endl;
  }

  return 0;
}
