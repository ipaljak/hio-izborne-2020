#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

using Node = pair<int, int>;
using Edge = pair<Node, Node>;

int r, s;

vector<Edge> edges;

inline int ceil(int a, int b) {
  return (a + b - 1) / b;
}

void rot() {
  for (auto &edge : edges) {
    int a = edge.first.first, b = edge.first.second;
    int c = edge.second.first, d = edge.second.second;
    edge.first.second = a; edge.first.first = s - b;
    edge.second.second = c; edge.second.first = s - d;
  }
  swap(r, s);
}

void draw() {
  char canvas[2 * r + 1][3 * s + 2];
  memset(canvas, ' ', sizeof canvas);

  for (int i = 0; i <= r; ++i)
    for (int j = 0; j <= s; ++j)
      canvas[i * 2][j * 3] = 'o';

  for (const auto &edge : edges) {
    int a = edge.first.first, b = edge.first.second;
    int c = edge.second.first, d = edge.second.second;
    if (a == c)
      canvas[a * 2][min(b, d) * 3 + 1] = canvas[a * 2][min(b, d) * 3 + 2] = '-';
    else
      canvas[min(a, c) * 2 + 1][b * 3] = '|';
  }

  for (int i = 0; i < 2 * r + 1; ++i) {
    for (int j = 0; j < 3 * s + 1; ++j)
      printf("%c", canvas[i][j]);
    printf("\n");
  }
}

int main(void) {
  scanf("%d%d", &r, &s);

  bool rotate = r > s;
  if (rotate) swap(r, s);

  for (int i = 0; i <= r; i += 2)
    for (int j = 0; j < s; ++j)
      edges.push_back({{i, j}, {i, j + 1}});

  for (int i = 0; i < r; ++i)
    edges.push_back({{i, s}, {i + 1, s}});

  int b = ceil(r * s, r + s), a = max(0, s - 2 * b), st = 0;
  for (int i = 1; i <= r; i += 2) {
    for (int j = 0; j < a; ++j)
      edges.push_back({{i, (st + j) % s}, {i, (st + j) % s + 1}});
    for (int j = a; j < a + b; ++j) {
      if (i != r)
        edges.push_back({{i, (st + j) % s}, {i + 1, (st + j) % s}});
      else
        edges.push_back({{i, (st + j) % s}, {i, (st + j) % s + 1}});
    }
    for (int j = a + b; j < s; ++j)
      edges.push_back({{i - 1, (st + j) % s}, {i, (st + j) % s}});
    st += a;
  }

  assert(edges.size() == (r + 1) * (s + 1) - 1);
  if (rotate) rot();
  draw();

  return 0;
}
