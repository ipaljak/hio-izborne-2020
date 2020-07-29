#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pii;

const int MAX = 5e5;
const int ITER = 1e6;

mt19937 rng;

int param;
int n, m;
int N, M;
int cutpoints;
set <pii> edges;
string gen_tree;

int get_uniform(int lo, int hi) {
  return uniform_int_distribution <int> (lo, hi)(rng);
}

vector <pii> get_connected_graph(int ord, int sz) {
  string cmd = "bash gen_conn.sh ";
  cmd += gen_tree + " ";
  cmd += to_string(param) + " " + to_string(ord) + " " + to_string(sz);
  system(cmd.c_str());
  FILE *in = fopen("conn", "r");
  fscanf(in, "%*d%*d");
  vector <pii> res(sz);
  for (auto &it : res)
    fscanf(in, "%d%d", &it.first, &it.second);
  fclose(in);
  return res;
}

void add_edge(int u, int v) {
  if (u > v)
    swap(u, v);
  edges.insert({u, v});
}

void generate() {
  n = get_uniform(cutpoints, N - cutpoints);
  m = get_uniform(n - 1, M - N + n);
  vector <pii> base = get_connected_graph(n, m);
  for (auto it : base)
    add_edge(it.first, it.second);
  vector <vector <int>> conn_to(cutpoints + 1);
  for (int i = 1; i <= cutpoints; i++) {
    conn_to[i].push_back(n + i);
    add_edge(i, n + i);
  }
  for (int i = n + cutpoints + 1; i <= N; i++) {
    int tmp = get_uniform(1, cutpoints);
    conn_to[tmp].push_back(i);
    add_edge(i, tmp);
  }
  for (int i = 0; i < ITER && edges.size() < M; i++) {
    int curr = i % cutpoints + 1;
    int sz = conn_to[curr].size();
    if (sz == 1)
      continue;
    int x = get_uniform(0, sz - 2);
    int y = get_uniform(x + 1, sz - 1);
    add_edge(conn_to[curr][x], conn_to[curr][y]);
  }
}

void output() {
  vector <pii> out;
  for (auto it : edges)
    out.push_back(it);
  shuffle(out.begin(), out.end(), rng);
  printf("%d %d\n", N + 1, edges.size());
  for (auto &it : out) {
    if (get_uniform(0, 1))
      swap(it.first, it.second);
    printf("%d %d\n", it.first, it.second);
  }
}

int main(int argc, char *argv[]) {
  param = atoi(argv[1]);
  N = atoi(argv[2]);
  M = atoi(argv[3]);
  cutpoints = atoi(argv[4]);
  gen_tree = argv[5];
  
  assert(N <= MAX && M <= MAX && M >= N - 1 && cutpoints <= N / 2);
  
  generate();
  output();

  return 0;
}
