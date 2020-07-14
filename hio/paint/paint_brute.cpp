#include <bits/stdc++.h>
using namespace std;

const int MAXPIXELS = 300000;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int n, m;

template<class T>
class Array2d {
 public:
  T *operator[](size_t index) { return &data[index * m]; }

 private:
  T data[MAXPIXELS];
};

Array2d<int> mat;
Array2d<int> vis;
int cookie = 0;

void fill(int x, int y, int color, int orig_color) {
  if (x < 0 || y < 0 || x >= n || y >= m) return;
  if (mat[x][y] != orig_color) return;
  if (vis[x][y] == cookie) return;
  vis[x][y] = cookie;
  mat[x][y] = color;
  for (int i = 0; i < 4; ++i) {
    fill(x + dx[i], y + dy[i], color, orig_color);
  }
}

int main(void) {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int x, y, color;
    cin >> x >> y >> color;
    x--; y--;
    cookie++;
    if (color != mat[x][y])
      fill(x, y, color, mat[x][y]);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << mat[i][j] << " \n"[j + 1 == m];
    }
  }

  return 0;
}
