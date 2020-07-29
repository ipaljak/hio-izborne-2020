#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 400100;
const int OFFSET = 1 << 19;

int n, q;
pair<int, int> a[MAXN];

vector<pair<int, int>> queries;

int pos[MAXN];  // na 0 je oznaka onog ko prvi jede, itd.
int pos_inv[MAXN];  // na i-toj poziciji je redni broj kada jede

inline bool kuhar(int index) { return a[index].first < a[index].second; }

struct Stats {
  ll a_sum;  // prefiks
  ll b_sum;  // sufiks
  ll ans;
};

const Stats ZERO = {0, 0, -(1LL << 60)};

Stats merge(Stats lhs, Stats rhs) {
  ll a_sum = lhs.a_sum + rhs.a_sum;
  ll b_sum = lhs.b_sum + rhs.b_sum;
  ll ans = max(lhs.a_sum + rhs.ans, lhs.ans + rhs.b_sum);
  return {a_sum, b_sum, ans};
}

Stats data[2 * OFFSET];

void update(int pos, Stats stats = ZERO) {
  pos += OFFSET;
  data[pos] = stats;
  for (pos /= 2; pos > 0; pos /= 2)
    data[pos] = merge(data[2 * pos], data[2 * pos + 1]);
}

Stats query(int from, int to, int node = 1, int lo = 0, int hi = OFFSET) {
  if (lo >= from && hi <= to) return data[node];
  if (lo >= to || hi <= from) return {0, 0, -(1LL << 60)};
  int mid = (lo + hi) / 2;
  return merge(query(from, to, 2 * node, lo, mid),
               query(from, to, 2 * node + 1, mid, hi));
}

int main(void) {
  for (int i = 0; i < 2 * OFFSET; ++i)
    data[i] = ZERO;

  cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }

  int total = n;
  for (int i = 0; i < q; ++i) {
    string cmd;
    cin >> cmd;
    if (cmd == "DOLAZI") {
      cin >> a[total].first >> a[total].second;
      queries.emplace_back(0, total);  // 0 je ulaz
      total++;
    }
    if (cmd == "ODLAZI") {
      int index;
      cin >> index;
      queries.emplace_back(1, index - 1);  // 1 je izlaz
    }
    if (cmd == "POREDAK") {
      queries.emplace_back(2, 0);
    }
  }

  iota(pos, pos + total, 0);
  sort(pos, pos + total, [](int i, int j) {
    if (kuhar(i)) {
      if (!kuhar(j)) return true;
      return a[i].first < a[j].first;
    }
    if (kuhar(j)) return false;
    return a[i].second > a[j].second;
  });

  for (int i = 0; i < total; ++i)
    pos_inv[pos[i]] = i;

  for (int i = 0; i < n; ++i) {
    update(pos_inv[i], {a[i].first, a[i].second, a[i].first + a[i].second});
  }

  cout << query(0, total).ans << endl;

  for (const auto &q : queries) {
    int ind = q.second;
    if (q.first == 0) {
      update(pos_inv[ind], {a[ind].first, a[ind].second, a[ind].first + a[ind].second});
      cout << query(0, total).ans << endl;
    } else if (q.first == 1) {
      update(pos_inv[ind], ZERO);
      cout << query(0, total).ans << endl;
    } else {
      vector<int> ans;
      for (int i = 0; i < total; ++i) {
        if (data[i + OFFSET].ans < 0) continue;
        ans.push_back(pos[i]);
      }
      for (auto ind : ans) cout << ind + 1 << " ";
      for (int i = 0; i < (int)ans.size(); ++i)
        cout << ans[i] + 1 << " \n"[i + 1 == ans.size()];
    }
  }

  return 0;
}
