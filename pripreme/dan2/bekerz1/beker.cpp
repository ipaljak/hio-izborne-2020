#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 5;
const int MOD = 1e9 + 7;

int N, M;
vector <int> adj[MAXN];
int subtree[MAXN], going_up[MAXN];
bool bad_up[MAXN], bad_overall[MAXN];
int disc[MAXN], fin[MAXN], low[MAXN];
int min_clique = MAXN, occ_min;
bool all_cliques = true;
int cnt_comp, cnt_good;
vector <int> curr_comp;
int timer = 1;

void load() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

int dfs(int x, int p) {
  curr_comp.push_back(x);
  disc[x] = low[x] = timer++;
  vector <bool> separate;
  vector <int> ch_fin, ch_sub;
  for (auto it : adj[x])  
    if (!disc[it]) {
      ch_sub.push_back(dfs(it, x));
      ch_fin.push_back(fin[it]);
      if (low[it] >= disc[x])
        separate.push_back(true);
      else {
        low[x] = min(low[x], low[it]);
        separate.push_back(false);
      }
    }
    else if (it != p) 
      low[x] = min(low[x], disc[it]);

  fin[x] = timer;  
  int sz = ch_sub.size();
  vector <int> going_down(sz);
  for (auto it : adj[x]) 
    if (disc[it] < disc[x] || disc[it] >= fin[x])
      going_up[x]++;
    else
      going_down[upper_bound(ch_fin.begin(), ch_fin.end(), disc[it]) - ch_fin.begin()]++;
  
  bad_up[x] = true;
  subtree[x] = accumulate(ch_sub.begin(), ch_sub.end(), 1);
  for (int i = 0; i < sz; i++) {
    bool conn_to_all = going_down[i] == ch_sub[i]; 
    if (separate[i])
      bad_overall[x] |= conn_to_all;
    else
      bad_up[x] &= conn_to_all;
  }

  return subtree[x];
}

void finish(int moves, ll ways) {
  assert(ways);
  for (int i = 1; i <= moves; i++)  
    ways = ways * i % MOD;
  printf("%d\n%lld\n", moves, ways);
  exit(0);
}

void process_comp(int root) {
  curr_comp.clear();
  dfs(root, 0);
  bool is_clique = true;
  int comp_size = curr_comp.size();
  for (auto it : curr_comp) {
    is_clique &= adj[it].size() == comp_size - 1;
    bad_up[it] &= going_up[it] == comp_size - subtree[it];
    bad_overall[it] |= bad_up[it];
    cnt_good += !bad_overall[it];
  }
  if (comp_size == 1 || !is_clique)
    all_cliques = false;
  else if (comp_size <= min_clique) {
    min_clique = comp_size;
    if (comp_size < min_clique)
      occ_min = 0;
    occ_min++;
  }
  cnt_comp++;
}

void solve() {
  for (int i = 1; i <= N; i++)
    if (!disc[i]) 
      process_comp(i);
  
  if (cnt_comp == 1)
    finish(0, 1);
  
  if (all_cliques) {
    if (cnt_comp == 2)
      finish(min_clique, occ_min);
    finish(2, (ll)N * (N - 1) / 2 - M + (min_clique == 2 ? occ_min : 0));
  }
  
  finish(1, cnt_good);
}

int main() {
  load();
  solve();
  return 0;
}
