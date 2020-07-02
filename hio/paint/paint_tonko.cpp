#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define x first
#define y second

const int MAXN = 500;
const int LIMIT = 7;

int n, m;
int mat[MAXN][MAXN];
bool vis[MAXN][MAXN];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

struct Component {
  int id;
  int color;
  bool large;
  list<pair<int, int>> pixels;
  list<int> larges;
  map<int, list<int>> by_color;
};

vector<Component> C;

int comp_id[MAXN][MAXN];
int comp_visited[MAXN * MAXN];  // used with cookie
int comp_visited_cookie = 0;
int parent[MAXN * MAXN];

int reals = 0;
int RealId(int comp) {
  reals++;
  if (parent[comp] == comp) return comp;
  return parent[comp] = RealId(parent[comp]);
}

#define ASSERT_ID(x) assert(parent[(x)] == (x))

void TraverseNeighbors(int id, function<void(int)> callback) {
  ASSERT_ID(id);
  comp_visited_cookie++;
  for (const auto &pt : C[id].pixels) {
    for (int i = 0; i < 4; ++i) {
      int nx = pt.x + dx[i];
      int ny = pt.y + dy[i];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
      int nid = comp_id[nx][ny];
      ASSERT_ID(nid);
      if (nid != id && comp_visited[nid] != comp_visited_cookie) {
        callback(nid);
        comp_visited[nid] = comp_visited_cookie;
      }
    }
  }
}

void TraverseNeighborsByColor(int id, int color, function<void(int)> callback) {
  ASSERT_ID(id);
  auto &comp = C[id];
  if (comp.large) {
    comp_visited_cookie++;
    for (const auto &nid_temp : comp.by_color[color]) {
      int nid = RealId(nid_temp);
      ASSERT_ID(nid);
      if (nid != id && C[nid].color == color &&
          comp_visited[nid] != comp_visited_cookie) {
        callback(nid);
        comp_visited[nid] = comp_visited_cookie;
      }
    }
    //comp.by_color[color].clear();  /// <------
  } else {
    TraverseNeighbors(id, [&callback, color](int nid) {
      if (C[nid].color == color)
        callback(nid);
    });
  }
}

void DeclareLarge(int id) {
  ASSERT_ID(id);
  C[id].large = true;
  TraverseNeighbors(id, [id](int nid) {
    C[nid].larges.push_back(id);
    C[id].by_color[C[nid].color].push_back(nid);
  });
}

void TraverseLarges(int id, function<void(int)> callback) {
  ASSERT_ID(id);
  comp_visited_cookie++;
  for (const auto &nid_temp : C[id].larges) {
    int nid = RealId(nid_temp);
    ASSERT_ID(nid);
    if (nid != id && C[nid].large && comp_visited[nid] != comp_visited_cookie) {
      callback(nid);
      comp_visited[nid] = comp_visited_cookie;
    }
  }
}

void NeutralizeLarges(int id) {
  ASSERT_ID(id);
  list<int> new_larges;
  TraverseLarges(id, [&new_larges](int nid) { new_larges.push_back(nid); });
  C[id].larges.swap(new_larges);
}

int Merge(int id1, int id2) {
  ASSERT_ID(id1);
  ASSERT_ID(id2);
  
  if (!C[id1].large && C[id2].large) DeclareLarge(id1);
  if (C[id1].large && !C[id2].large) DeclareLarge(id2);

  // Merge pixels...
  if (C[id1].pixels.size() > C[id2].pixels.size()) swap(id1, id2);
  int nid = id2;
  parent[id1] = id2;
  for (const auto &pt : C[id1].pixels)
    comp_id[pt.x][pt.y] = nid;
  C[id2].pixels.splice(C[id2].pixels.end(), C[id1].pixels);

  // Merge list of large neighbors
  C[id2].larges.splice(C[id2].larges.end(), C[id1].larges);
  NeutralizeLarges(id2);

  // Merge neighbors by color:i
  if (C[id1].by_color.size() > C[id2].by_color.size())
    C[id1].by_color.swap(C[id2].by_color);
  for (auto &entry : C[id1].by_color) {
    int color = entry.first;
    auto &list1 = entry.second;
    auto &list2 = C[id2].by_color[color];
    list2.splice(list2.end(), list1);
  }

  // Photo finish
  if (!C[nid].large && C[nid].pixels.size() > LIMIT)
    DeclareLarge(nid);

  return nid;
}

void Fill(int x, int y, int color) {
  int id = comp_id[x][y];
  C[id].color = color;
  vector<int> neighbors;
  TraverseNeighborsByColor(id, color, [&neighbors](int nid) {
    neighbors.push_back(nid);
  });
  for (const auto &nid : neighbors) {
    id = Merge(id, nid);
  }
  TraverseLarges(id, [id, color](int nid) {
    C[nid].by_color[color].push_back(id);
  });
}

////////////////////////////////////////////////////////////////////////////////
// Initial processing

list<pair<int, int>> traversal;

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
    if (comp.pixels.size() > LIMIT)
      DeclareLarge(comp.id);
  }
}

void debug() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) cerr << C[comp_id[i][j]].color << " ";
    for (int j = 0; j < m; ++j) cerr << " " << comp_id[i][j];
    cerr << endl;
  }
  cerr << "--------------------" << endl;
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
    // debug();
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << C[comp_id[i][j]].color << " \n"[j + 1 == m];
    }
  }
  
  return 0;
}
