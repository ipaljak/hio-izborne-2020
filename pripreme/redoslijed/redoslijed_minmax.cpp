#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;
const int offset = 1 << 19;

struct Node {
  int mn, mx;
  Node() : mn(MAXN), mx(0) {}
  Node(int mn, int mx) : mn(mn), mx(mx) {}
};

int N, M;
int final[MAXN];
int covered[MAXN];
int lft[MAXN], rig[MAXN], clr[MAXN];
vector <int> queries[2 * offset];
Node tour[2 * offset];
int stage[2 * offset];
queue <int> active;
set <int> non_zero;
int cnt[MAXN];

void recalc_node(int x) {
  auto decrease_cnt = [&](int idx) {
    if (!(--cnt[idx])) 
      active.push(idx);  
  };
  if (stage[x] == 2)
    return;
  if (!tour[x].mx) {
    for (auto it : queries[x])
      decrease_cnt(it);
    stage[x] = 2;
    return;
  }
  if (stage[x] == 1 || tour[x].mn != tour[x].mx)
    return;
  vector <int> nxt;
  for (auto it : queries[x])
    if (clr[it] == tour[x].mn)
      decrease_cnt(it);
    else
      nxt.push_back(it);
  queries[x] = nxt;
  stage[x] = 1;
}

Node merge(Node l, Node r) {
  return Node(min(l.mn, r.mn), max(l.mx, r.mx));
}

void update(int x, bool remove) {
  if (remove)
    non_zero.erase(x);
  else
    non_zero.insert(x);
  tour[x + offset] = remove ? Node() : Node(final[x], final[x]);
  for (x += offset; x; x /= 2) {
    if (x < offset)
      tour[x] = merge(tour[2 * x], tour[2 * x + 1]);
    if (remove)
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
      update(i, false);
  }
}

void bye() {
  puts("NO");
  exit(0);
}

void solve() {    
  non_zero.insert(N);  
  for (int i = 1; i < N; i++)
    covered[i] += covered[i - 1];
  for (int i = 0; i < N; i++)
    if (!!covered[i] ^ !!final[i])
      bye();
  
  for (int i = 0; i < 2 * offset; i++) 
    recalc_node(i);
    
  vector <int> ans;
  while (!active.empty()) {
    int curr = active.front();
    active.pop();
    ans.push_back(curr);
    while (1) {
      int pos = *non_zero.lower_bound(lft[curr]);
      if (pos >= rig[curr])
        break;
      update(pos, true);
    }
  }
  
  if (ans.size() < M) 
    bye();
		
  puts("YES");
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
