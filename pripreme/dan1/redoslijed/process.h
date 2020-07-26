#include <bits/stdc++.h>
using namespace std;

struct Operation {
  int lft, rig, clr;
  void output() const {
    printf("%d %d %d\n", lft, rig, clr);
  }
};

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
