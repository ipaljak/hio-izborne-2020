#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

const int MAXPIXELS = 300000;
const int MAGIC = 400;

int n, m;

// Pomocna klasa koja pretvara 1D niz u 2D matricu dimenzije n x m.
template<class T>
class Array2d {
 public:
  T *operator[](size_t index) { return &data[index * m]; }

 private:
  T data[MAXPIXELS];
};

Array2d<int> mat;
Array2d<bool> vis;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

struct Component {
  int id;
  int color;
  bool large;
  vector<pair<int, int>> pixels;
  vector<int> larges;
  map<int, vector<int>> by_color;
};

vector<Component> C;

Array2d<int> comp_id;
int comp_visited[MAXPIXELS];  // koristi se s cookiejem
int comp_visited_cookie = 0;
int parent[MAXPIXELS];

int RealId(int comp) {
  if (parent[comp] == comp) return comp;
  return parent[comp] = RealId(parent[comp]);
}

void TraverseNeighbors(int id, function<void(int)> callback) {
  comp_visited_cookie++;
  for (const auto &pt : C[id].pixels) {
    for (int i = 0; i < 4; ++i) {
      int nx = pt.x + dx[i];
      int ny = pt.y + dy[i];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
      int nid = comp_id[nx][ny];
      if (nid != id && comp_visited[nid] != comp_visited_cookie) {
        callback(nid);
        comp_visited[nid] = comp_visited_cookie;
      }
    }
  }
}

vector<int> GetNeighborsByColor(int id, int color) {
  vector<int> ret;
  auto &comp = C[id];
  if (comp.large) {
    comp_visited_cookie++;
    for (const auto &nid_temp : comp.by_color[color]) {
      int nid = RealId(nid_temp);
      if (nid != id && C[nid].color == color &&
          comp_visited[nid] != comp_visited_cookie) {
        ret.push_back(nid);
        comp_visited[nid] = comp_visited_cookie;
      }
    }
    comp.by_color[color].clear();  /// <------
  } else {
    TraverseNeighbors(id, [&ret, color](int nid) {
      if (C[nid].color == color) ret.push_back(nid);
    });
  }
  return ret;
}

void DeclareLarge(int id) {
  C[id].large = true;
  TraverseNeighbors(id, [id](int nid) {
    C[nid].larges.push_back(id);
    C[id].by_color[C[nid].color].push_back(nid);
  });
}

void TraverseLarges(int id, function<void(int)> callback) {
  comp_visited_cookie++;
  for (const auto &nid_temp : C[id].larges) {
    int nid = RealId(nid_temp);
    if (nid != id && C[nid].large && comp_visited[nid] != comp_visited_cookie) {
      callback(nid);
      comp_visited[nid] = comp_visited_cookie;
    }
  }
}

void NeutralizeLarges(int id) {
  vector<int> new_larges;
  TraverseLarges(id, [&new_larges](int nid) { new_larges.push_back(nid); });
  C[id].larges.swap(new_larges);
}

int Merge(int id1, int id2) {
  if (!C[id1].large && C[id2].large) DeclareLarge(id1);
  if (C[id1].large && !C[id2].large) DeclareLarge(id2);

  // Spoji piksele
  if (C[id1].pixels.size() > C[id2].pixels.size()) swap(id1, id2);
  int nid = id2;
  parent[id1] = id2;
  for (const auto &pt : C[id1].pixels)
    comp_id[pt.x][pt.y] = nid;
  for (const auto &pixel : C[id1].pixels)
    C[id2].pixels.push_back(pixel);
  vector<pair<int, int>>().swap(C[id1].pixels);

  // Spoji listu velikih susjeda
  if (C[id1].larges.size() > C[id2].larges.size())
    C[id1].larges.swap(C[id2].larges);
  for (const auto &l : C[id1].larges)
    C[id2].larges.push_back(l);
  vector<int>().swap(C[id1].larges);
  NeutralizeLarges(id2);

  // Spoji susjede po bojama
  if (C[id1].by_color.size() > C[id2].by_color.size())
    C[id1].by_color.swap(C[id2].by_color);
  for (auto &entry : C[id1].by_color) {
    int color = entry.first;
    auto &list1 = entry.second;
    auto &list2 = C[id2].by_color[color];
    if (list1.size() > list2.size()) list1.swap(list2);
    for (const auto &el : list1)
      list2.push_back(el);
    vector<int>().swap(list1);
  }

  if (!C[nid].large && C[nid].pixels.size() > MAGIC)
    DeclareLarge(nid);

  return nid;
}

void Fill(int x, int y, int color) {
  int id = comp_id[x][y];
  C[id].color = color;
  for (const auto &nid : GetNeighborsByColor(id, color)) {
    id = Merge(id, nid);
  }
  TraverseLarges(id, [id, color](int nid) {
    C[nid].by_color[color].push_back(id);
  });
}

////////////////////////////////////////////////////////////////////////////////
// Initial processing

vector<pair<int, int>> traversal;

void FindComponent(int x, int y, int color) {
  if (x < 0 || y < 0 || x >= n || y >= m) return;
  if (mat[x][y] != color) return;
  if (vis[x][y]) return;
  vis[x][y] = true;
  traversal.emplace_back(x, y);
  for (int i = 0; i < 4; ++i) {  
    FindComponent(x + dx[i], y + dy[i], color);
  }
}

void Init() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (vis[i][j]) continue;
      traversal.clear();
      FindComponent(i, j, mat[i][j]);
      Component comp;
      comp.id = C.size();
      comp.color = mat[i][j];
      comp.large = false;
      comp.pixels = traversal;
      C.push_back(comp);
      for (const auto &pt : comp.pixels)
        comp_id[pt.x][pt.y] = comp.id;
    }
  }
  iota(parent, parent + n * m, 0);
  for (auto &comp : C) {
    if (comp.pixels.size() > MAGIC)
      DeclareLarge(comp.id);
  }
}

int main(void) {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }

  Init();

  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int x, y, color;
    cin >> x >> y >> color;
    Fill(x - 1, y - 1, color);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << C[comp_id[i][j]].color << " \n"[j + 1 == m];
    }
  }
  
  return 0;
}
