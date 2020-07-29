#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

using Guest = pair<int, pair<int, int>>;

const int MAXN = 2e5 + 10;

bool _less(const pair<int, int> &A, const pair<int, int> &B) {
  if (A.first < A.second) {
    if (B.first < B.second) return A.first < B.first;
    return true;
  }
  if (B.first < B.second) return false;
  return A.second > B.second;
}

bool cmp(const Guest &AA, const Guest &BB) {
  auto A = AA.second, B = BB.second;
  if (_less(A, B) == _less(B, A)) return AA.first < BB.first;
  return _less(A, B);
}

int n, k;
int sort_id[2 * MAXN];

set<Guest, decltype(cmp)*> g_set(cmp), offline(cmp);
vector<pair<int, int>> g;

struct Query {
  int type;
  int a, b;
  Query() {}
  Query(int type, int a, int b) : type(type), a(a), b(b) {}
};

vector<Query> Q;

struct Tournament {
  int offset;
  vector<llint> tree;
  vector<llint> prop;

  Tournament() = delete;
  Tournament(int n) {
    for (offset = 1; offset <= n; offset <<= 1);
    tree.resize(2 * offset, 0);
    prop.resize(2 * offset, 0);
  }

  void merge(int node) {
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
  }

  void propagate(int node, int from, int to) {
    if (from + 1 == to) return;
    for (int i = 0; i < 2; ++i) {
      tree[2 * node + i] += prop[node];
      prop[2 * node + i] += prop[node];
    }
    prop[node] = 0;
  }

  void inc_interval(int node, int from, int to, int lo, int hi, int val) {
    if (to <= lo || hi <= from) return;
    if (from >= lo && to <= hi) {
      tree[node] += val;
      prop[node] += val;
      propagate(node, from, to);
      return;
    }
    propagate(node, from, to);
    inc_interval(2 * node, from, (from + to) / 2, lo, hi, val);
    inc_interval(2 * node + 1, (from + to) / 2, to, lo, hi, val);
    merge(node);
  }

  void set(int i, llint val) {
    i += offset;
    tree[i] = min(tree[i], val);
    i /= 2;
    for (; i > 0; i /= 2) tree[i] = min(tree[2 * i], tree[2 * i + 1]);
  }

  llint get_max(int node, int from, int to, int lo, int hi) {
    if (to <= lo || hi <= from) return 0;
    if (from >= lo && to <= hi) return tree[node];
    return max(get_max(2 * node, from, (from + to) / 2, lo, hi),
               get_max(2 * node + 1, (from + to) / 2, to, lo, hi));
  }

  llint get_max(int lo, int hi) { return get_max(1, 0, offset, lo, hi); }
  void inc_interval(int lo, int hi, int val) { return inc_interval(1, 0, offset, lo, hi, val); }
};

llint get_time() {
  llint eat_queue = 0;
  llint total = 0;
  for (const auto &p : g_set) {
    int a = p.second.first, b = p.second.second;
    eat_queue = max(0LL, eat_queue - (llint)a);
    total += a;
    eat_queue += (llint)b;
  }
  return total + eat_queue;
}

void print_order() {
  for (const auto &p : g_set) printf("%d ", p.first + 1);
  for (const auto &p : g_set) printf("%d ", p.first + 1);
  printf("\n");
}

int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    g_set.insert({i, {a, b}});
    offline.insert({i, {a, b}});
    g.emplace_back(a, b);
  }

  int id = n;
  for (int i = 0; i < k; ++i) {
    char s[10];
    scanf("%s", s);
    if (strcmp(s, "DOLAZI") == 0) {
      int a, b;
      scanf("%d%d", &a, &b);
      g.emplace_back(a, b);
      offline.insert({id, {a, b}});
      ++id;
      Q.emplace_back(0, a, b);
    }
    if (strcmp(s, "ODLAZI") == 0) {
      int x;
      scanf("%d", &x); --x;
      Q.emplace_back(1, x, -1);
    }
    if (strcmp(s, "POREDAK") == 0)
      Q.emplace_back(2, -1, -1);
  }

  int sid = 0;
  for (const auto &p : offline)
    sort_id[p.first] = sid++;

  Tournament T((int) g.size());
  for (int i = 0; i < n; ++i) {
    T.inc_interval(sort_id[i], id, g[i].first);
    T.inc_interval(0, sort_id[i] + 1, g[i].second);
  }

  printf("%lld\n", T.get_max(0, id));

  int i = n;
  for (const auto &q : Q) {
    if (q.type == 0) {
      g_set.insert({i, {q.a, q.b}});
      T.inc_interval(sort_id[i], id, g[i].first);
      T.inc_interval(0, sort_id[i] + 1, g[i].second);
      ++i;
      printf("%lld\n", T.get_max(0, id));
    }
    if (q.type == 1) {
      int x = q.a;
      auto it = g_set.find({x, g[x]});
      assert(it != g_set.end());
      g_set.erase(it);
      T.inc_interval(sort_id[x], id, -g[x].first);
      T.inc_interval(0, sort_id[x] + 1, -g[x].second);
      printf("%lld\n", T.get_max(0, id));
    }
    if (q.type == 2)
      print_order();
  }

  return 0;
}
