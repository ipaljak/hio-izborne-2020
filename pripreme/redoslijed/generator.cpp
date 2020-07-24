#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAX = 5e5;

struct Operation {
  int lft, rig, clr;
  void output() const {
    printf("%d %d %d\n", lft, rig, clr);
  }
};

int get(int lo, int hi) {
  return uniform_int_distribution <int> (lo, hi)(rng);
}

vector <int> process_operations(int n, vector <Operation> ops, vector <int> perm) {
  int m = ops.size();
  vector <int> inv(m);
  for (int i = 0; i < m; i++)
    inv[--perm[i]] = i;
  vector <vector <int>> in(n), out(n);
  for (int i = 0; i < m; i++) {
    in[--ops[i].lft].push_back(i);
    out[--ops[i].rig].push_back(i);
  }
  set <int> active;
  vector <int> res(n);
  for (int i = 0; i < n; i++) {
    for (auto it : in[i])
      active.insert(inv[it]);
    res[i] = active.empty() ? 0 : ops[perm[*active.rbegin()]].clr;
    for (auto it : out[i])
      active.erase(inv[it]);
  }
  return res;
}

int main(int argc, char *argv[]) {
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);
  int distinct = atoi(argv[3]);
  int limit = atoi(argv[4]);
  assert(N <= MAX && M <= MAX && limit <= MAX);
  assert(distinct <= limit);
  
  unordered_set <int> curr;
  while (curr.size() < distinct)
    curr.insert(get(1, limit));
    
  vector <int> values;
  for (auto it : curr)
    values.push_back(it);
  
  printf("%d %d\n", N, M);  
  vector <Operation> input(M);
  for (auto &it : input) {
    it.lft = get(1, N);
    it.rig = get(it.lft, N);
    it.clr = values[get(0, distinct - 1)];
    it.output();
  }
  
  vector <int> order(M);
  for (int i = 0; i < M; i++)
    order[i] = i + 1;
  
  shuffle(order.begin(), order.end(), rng);
  
  vector <int> ans = process_operations(N, input, order);
  for (auto it : ans)
    printf("%d ", it);
  puts("");
  
  return 0;
}
