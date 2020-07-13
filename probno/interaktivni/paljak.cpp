#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

const string dir = "RDLU";

const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

map<pair<int, int>, int> dist;
map<pair<int, int>, char> grid;
set<pair<int, int>> bio;

vector<string> get_env() {
  vector<string> ret;
  for (int i = 0; i < 3; ++i) {
    string s;
    cin >> s;
    ret.push_back(s);
  }
  return ret;
}

void move(char dir) {
  cout << "POMAK " << dir << endl;
}

void ans(int dist) {
  cout << "! " << dist << endl;
  exit(0);
}

void dfs(int r, int s) {
  vector<string> env = get_env();
  bio.insert({r, s});
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      grid[{r + i - 1, s + j - 1}] = env[i][j];

  for (int k = 0; k < 4; ++k) {
    int rr = r + dr[k], ss = s + ds[k];
    if (bio.find({rr, ss}) != bio.end() || env[1 + dr[k]][1 + ds[k]] == '#')
      continue;
    move(dir[k]);
    dfs(rr, ss);
    move(dir[(k + 2) % 4]);
    auto dummy = get_env();
  }
}

int bfs() {
  queue<pair<int, int>> Q;
  Q.push({0, 0});
  dist[{0, 0}] = 0;
  while (!Q.empty()) {
    int r = Q.front().first, s = Q.front().second;
    Q.pop();
    if (grid[{r, s}] == 'B') return dist[{r, s}];
    for (int k = 0; k < 4; ++k) {
      int rr = r + dr[k], ss = s + ds[k];
      if (dist.find({rr, ss}) != dist.end() || grid[{rr, ss}] == '#') continue;
      dist[{rr, ss}] = dist[{r, s}] + 1;
      Q.push({rr, ss});
    }
  }
  return -1;
}

int main(void) {
  dfs(0, 0);
  ans(bfs());
  return 0;
}
