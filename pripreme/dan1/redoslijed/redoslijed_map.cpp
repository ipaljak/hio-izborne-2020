#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pii;

const int MAXN = 5e5 + 5;
const int offset = 1 << 19;

int N, M;
int final[MAXN];
int covered[MAXN];
int lft[MAXN], rig[MAXN], clr[MAXN];
unordered_map <int, int> occ[2 * offset];
vector <int> queries[2 * offset];
int stage[2 * offset];
set <int> where[MAXN];
queue <int> active;
int cnt[MAXN];

bool becomes_zero(int &ref) {
  return !(--ref);
}

void recalc_node(int x) {
  auto decrease_cnt = [&](int idx) {
    if (becomes_zero(cnt[idx])) 
      active.push(idx);  
  };
  if (stage[x] == 2)
    return;
  if (occ[x].empty()) {
    for (auto it : queries[x])
      decrease_cnt(it);
    stage[x] = 2;
    return;
  }
  if (stage[x] == 1 || occ[x].size() > 1)
    return;
  vector <int> nxt;
  int remaining = occ[x].begin() -> first;
  for (auto it : queries[x])
    if (clr[it] == remaining)
      decrease_cnt(it);
    else
      nxt.push_back(it);
  queries[x] = nxt;
  stage[x] = 1;
}

void add(int pos) {
  where[final[pos]].insert(pos);
  for (int x = pos + offset; x; x /= 2)
    occ[x][final[pos]]++;
}

void remove(int pos) {
  where[final[pos]].erase(pos);
  for (int x = pos + offset; x; x /= 2) 
    if (becomes_zero(occ[x][final[pos]])) {
      occ[x].erase(final[pos]);
      recalc_node(x);
    }
}

void insert(int x, int lo, int hi, int from, int to, int idx) {
  if (lo >= to || hi <= from)
    return;
  if (lo >= from && hi <= to) {
    queries[x].push_back(idx);
    cnt[idx]++;
    return;
  }
  int mid = (lo + hi) / 2;
  insert(2 * x, lo, mid, from, to, idx);
  insert(2 * x + 1, mid, hi, from, to, idx);
}

void load() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; i++) {
    scanf("%d%d%d", lft + i, rig + i, clr + i);
    covered[--lft[i]]++;
    covered[rig[i]]--;
    insert(1, 0, offset, lft[i], rig[i], i);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", final + i);
    if (final[i])
      add(i);
  }
}

void bye() {
  puts("NE");
  exit(0);
}

void solve() {    
  for (int i = 0; i < MAXN; i++)
    where[i].insert(N);
  for (int i = 1; i < N; i++)
    covered[i] += covered[i - 1];
  for (int i = 0; i < N; i++) 
    if (!covered[i] ^ !final[i])
      bye();
	
  for (int i = 0; i < 2 * offset; i++)
    recalc_node(i);
    
  vector <int> ans;
  while (!active.empty()) {
    int curr = active.front();
    active.pop();
    ans.push_back(curr);
    while (1) {
      int tmp = *where[clr[curr]].lower_bound(lft[curr]);
      if (tmp >= rig[curr])
        break;
      remove(tmp);
    }
  }
	
  if (ans.size() < M) 
    bye();
		
  puts("DA");
  reverse(ans.begin(), ans.end());  
  for (auto it : ans)
    printf("%d ", it + 1);
  puts("");
}

int main() {
  double st = clock();
  load();
  solve();
  fprintf(stderr, "%lf\n", (clock() - st) / CLOCKS_PER_SEC);
  return 0;
}
