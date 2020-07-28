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
  int m = 1000000;
  if (argc > 4) m = atoi(argv[4]);
  int p_inside = 20;
  int p_down = 50;
  if (argc > 5) p_inside = atoi(argv[5]);
  if (argc > 6) p_down = atoi(argv[6]);

  cout << n << " " << k << endl;
  
  set<pair<int, int>> pts;
  pts.insert({0, 0});
  pts.insert({m, 0});
  
  double r = m / 2.0 - 0.5;
 
  double scale = random(0.2, 5);

  while (pts.size() < n) {
    double rr = r;
    if (rand() % 100 < p_inside)
      rr = r * (0.75 + 0.25 * (rand() % 1000) / 1000.0);

    double alpha = random(0, pi);
    double x = cos(alpha) * rr;
    double y = sin(alpha) * rr;

    if (rand() % 100 < p_down) y = -y;
    
    x = round(x + m / 2.0);
    y = round(y * scale);
    if (x <= 0 || x >= m) continue;
    pts.insert({x, y});
  }

  cout << 0 << " " << 0 << endl;
  cout << m << " " << 0 << endl;
  pts.erase(pts.begin());
  auto it = pts.end(); --it; pts.erase(it);

  for (const auto &pt : pts) {
    cout << pt.first << " " << pt.second << endl;
  }

  return 0;
}
