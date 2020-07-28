#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;
const int offset = 1 << 19;

struct Node {
  int x, lo, hi;
};

int N, M;
int which[MAXN];
int last[2 * offset];
int bio[MAXN + 2 * offset];
vector <int> queries[2 * offset];
vector <int> adj[MAXN + 2 * offset];
int lft[MAXN], rig[MAXN], clr[MAXN];
int final[MAXN];
vector <Node> nodes[MAXN]; 
vector <int> todo[MAXN];
vector <int> ans;

void insert(int x, int lo, int hi, int from, int to, int idx) {
  if (lo >= to || hi <= from)
    return;
  if (lo >= from && hi <= to) {
    queries[x].push_back(idx);
    nodes[idx].push_back({x, lo, hi});
    return;
  }
  int mid = (lo + hi) / 2;
  insert(2 * x, lo, mid, from, to, idx);
  insert(2 * x + 1, mid, hi, from, to, idx);
}

void load() {
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= M; i++) {
    scanf("%d%d%d", lft + i, rig + i, clr + i);
    insert(1, 0, offset, --lft[i], rig[i], i);
    which[clr[i]] = i;
  }
  for (int i = 0; i < N; i++)
    scanf("%d", final + i);
}

void add_edge(int u, int v) {
  adj[u].push_back(v);
}

void bye() {
  puts("NE");
  exit(0);
}

void build_graph(int pos) {
  int who = 0, node = 0;
  if (final[pos]) {
    who = which[final[pos]];
    if (!who)
      bye();
    for (auto it : nodes[who])
      if (pos >= it.lo && pos < it.hi) {
        node = it.x;
        break;
      }
    if (!node)
      bye();
    if (last[node] && last[node] != who)
      bye();  
    last[node] = who;
  }
  for (pos += offset; pos; pos /= 2)
    if (who) {
      add_edge(who, M + pos);
      if (pos != node)
        todo[who].push_back(pos);
    }
    else if (!queries[pos].empty())
      bye();
}

void dfs(int x) {
  if (bio[x] == 1)
    bye();
  if (bio[x] == 2)
    return;
  bio[x] = 1;
  for (auto it : adj[x])
    dfs(it);
  bio[x] = 2;
  if (x <= M)
    ans.push_back(x);
}

void solve() {
  for (int i = 0; i < N; i++)
    build_graph(i);
 
  for (int i = 1; i <= M; i++)
    for (auto it : todo[i])
      if (last[it])
        add_edge(i, last[it]);
         
  for (int i = 1; i < 2 * offset; i++)
    for (auto it : queries[i])
      if (it != last[i])
        add_edge(M + i, it);
  
  for (int i = 1; i < M + 2 * offset; i++)
    dfs(i);  
    
  puts("DA");
  for (auto it : ans)
    printf("%d ", it);
  puts(""); 
}

int main() {
  double st = clock();
  load();
  solve();
  fprintf(stderr, "%lf\n", (clock() - st) / CLOCKS_PER_SEC);
  return 0;
}
