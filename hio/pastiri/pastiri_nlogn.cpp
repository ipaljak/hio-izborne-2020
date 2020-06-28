#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;

int N, K;
int sheep[MAXN];
vector <int> adj[MAXN];
int dep[MAXN], dist[MAXN];
int highest[MAXN];
bool bio[MAXN];

void load() {
  scanf("%d%d", &N, &K);
  for (int i = 1; i < N; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 0; i < K; i++)
    scanf("%d", sheep + i);
}

void dfs_init(int x, int p, int mx, int opt) {
  int sum = dep[x] + dist[x];
  if (sum > mx) {
    mx = sum;
    opt = x;
  }
  highest[x] = opt;
  for (auto it : adj[x])
    if (it != p) {
      dep[it] = dep[x] + 1;
      dfs_init(it, x, mx, opt);
    }
}

void bfs() {
  memset(dist, -1, sizeof dist);
  queue <int> Q;
  for (int i = 0; i < K; i++) {
    dist[sheep[i]] = 0;
    Q.push(sheep[i]);
  }
  while (!Q.empty()) {
    int curr = Q.front();
    Q.pop();
    for (auto it : adj[curr])
      if (dist[it] == -1) {
        dist[it] = dist[curr] + 1;
        Q.push(it);
      }
  }
}

void dfs_cover(int x) {
  bio[x] = true;
  for (auto it : adj[x])
    if (!bio[it] && dist[x] == dist[it] + 1)
      dfs_cover(it);
}

void solve() {
  bfs();
  dfs_init(1, 0, -1, 0);
  sort(sheep, sheep + K, [](int x, int y) { return dep[x] > dep[y]; });
  vector <int> ans;
  for (int i = 0; i < K; i++)
    if (!bio[sheep[i]]) {
      ans.push_back(highest[sheep[i]]);
      dfs_cover(highest[sheep[i]]);
    }
  printf("%d\n", ans.size());
  for (auto it : ans)
    printf("%d ", it);
  puts("");
}

int main() {
  load();
  solve();
  return 0;
}
