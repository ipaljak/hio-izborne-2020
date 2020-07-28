#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

const double pi = acos(-1);

typedef long long ll;
typedef pair<int, int> Pt;

ll ccw(Pt a, Pt b, Pt c) {
  return (ll)a.x*(b.y-c.y) + (ll)b.x*(c.y-a.y) + (ll)c.x*(a.y-b.y);
}

vector<Pt> conv_hull(vector<Pt> v) {
  sort(v.begin(), v.end());
  vector<Pt> hull;
  for (const auto &p : v) {
    while (hull.size() >= 2 && ccw(hull[hull.size() -2], hull.back(), p) >= 0)
      hull.pop_back();
    hull.push_back(p);
  }
  return hull;
}

vector<Pt> jojo(int rad, int perc) {
  double from = 0;
  double to = perc / 100.0;
  double step = (to - from) / (600 + rand() % 400);
  double tiny = step / 20;

  vector<Pt> ret;
  for (double a = from; a < to; a += step) {
    int r = rad - rand() % 200;
    long double aa = a - tiny + 2*tiny*((rand() % 1000) / 1000.0);
    long double x = (long double)r * cosl((long double)aa);
    long double y = (long double)r * sinl((long double)aa);
    //cerr << aa << " " << x << " " << y << endl;
    int xx = roundl(x);
    int yy = roundl(y);
    ret.push_back({xx, yy});
  }
  return ret;
}

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  int n = atoi(argv[2]);
  int k = atoi(argv[3]);
  int H = atoi(argv[4]);
  int D = atoi(argv[5]);
  int R = atoi(argv[6]);
  int left = 80, right = 80;
  if (argc > 7) left = atoi(argv[7]);
  if (argc > 8) right = atoi(argv[8]);

  vector<Pt> pts_mid;
  for (int dd = D; H--; dd += (--D)) {
    pts_mid.push_back({-dd, H});
    pts_mid.push_back({dd, H});
  }

  // debug
  auto hull_mid = conv_hull(pts_mid);
  cerr << "hull_mid: size=" << hull_mid.size() << ", P="
       << ccw(hull_mid[0], hull_mid.back(), hull_mid[hull_mid.size() / 2])
       << ", dx=" << hull_mid.back().x - hull_mid[0].x << endl;

  auto pts_left = jojo(R, left);
  auto pts_right = jojo(R, right);
  //cerr << R << endl;


  // debug
  auto hull_left = conv_hull(pts_left);
  auto hull_right = conv_hull(pts_right);
  cerr << "hull_left: size=" << hull_left.size() << ", P1="
       << -ccw(hull_left[0], hull_left[1], hull_left[2]) << ","
       << -ccw(hull_left[11], hull_left[12], hull_left[13]) << endl;
  cerr << "hull_rigth: size=" << hull_right.size() << ", P1="
       << -ccw(hull_right[0], hull_right[1], hull_right[2]) << ","
       << -ccw(hull_right[11], hull_right[12], hull_right[13]) << endl;

  reverse(pts_right.begin(), pts_right.end());
  for (auto &p : pts_left) p.x = -p.x;

  int dx1 = pts_mid[0].x - pts_left.back().x;
  int dy1 = pts_mid[0].y - pts_left.back().y;
  int dx2 = pts_right[0].x - pts_mid.back().x;
  int dy2 = pts_right[0].y - pts_mid.back().y;


  vector<Pt> pts_all;
  for (auto p : pts_left) pts_all.push_back(p);
  pts_all.pop_back();
  for (auto p : pts_mid) pts_all.push_back({p.x - dx1, p.y - dy1});
  pts_all.pop_back();
  for (auto p : pts_right) pts_all.push_back({p.x - dx1 - dx2, p.y - dy1 - dy2});

  if (pts_all[0].y < pts_all.back().y) {
    pts_all.push_back({pts_all.back().x + 1, pts_all[0].y});
  } else {
    pts_all.push_back({pts_all[0].x - 1, pts_all.back(). y});
  }
  sort(pts_all.begin(), pts_all.end());

  // debug:
  auto hull_all = conv_hull(pts_all);
  cerr << "pts vs hull: " << pts_all.size() << " " << hull_all.size() << endl;


  int dyy = pts_all[0].y;
  for (auto &p : pts_all) p.y -= dyy;
  for (auto &p : pts_all) assert(p.y >= 0); 
  assert(pts_all[0].y == 0);
  assert(pts_all.back().y == 0);
  assert(pts_all[1].x > pts_all[0].x);
  assert(pts_all[pts_all.size() - 2].x < pts_all.back().x);

  int r2 = (pts_all.back().x - pts_all[0].x - 100) / 2;
  int center = (pts_all.back().x + pts_all[0].x) / 2;
  for (int iter = 0; iter < 300; ++iter) {
    double d = pi * ((rand() % 10000) / 10000.0);
    int x = cos(d) * (r2/2);
    int y = -sin(d) * (r2/2);
    if (y < 0) pts_all.push_back({x + center, y});
  }

  sort(pts_all.begin(), pts_all.end());
  int dxx = pts_all[0].x;
  for (auto &p : pts_all) p.x -= dxx;

  for (int iter = 0; iter < 200; ++iter) {
    int p = 1 + rand() % (pts_all.size() - 2);
    pts_all.erase(pts_all.begin() + p);
  }

  while (pts_all.size() > n) {
    int p = 1 + rand() % (pts_all.size() - 2);
    pts_all.erase(pts_all.begin() + p);
  }

  if (rand() % 2 == 0) {
    for (auto &p : pts_all) p.y = -p.y;
  }

  cerr << "final_size: " << pts_all.size() << endl;

  cout << pts_all.size() << " " << min((int)pts_all.size(), k) << endl;
  cout << pts_all[0].x << " " << pts_all[0].y << endl;
  cout << pts_all.back().x << " " << pts_all.back().y << endl;
  for (int i = 1; i < pts_all.size() - 1; ++i)
    cout << pts_all[i].x << " " << pts_all[i].y << endl;


  
  return 0;
}
