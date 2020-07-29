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

ll a_sum = 0;
ll b_sum = 0;
set<int> active;

ll query() {
  ll aa = 0;
  ll bb = b_sum;
  ll ans = 0;
  auto it = active.begin();
  for (int i = 0; it != active.end() && i < 100; ++i) {
    int ind = pos[*it];
    aa += a[ind].first;
    ans = max(ans, aa + bb);
    bb -= a[ind].second;
    it++;
  }
  aa = a_sum;
  bb = 0;
  it = active.end(); it--;
  for (int i = 0; it != active.begin() && i < 100; ++i) {
    int ind = pos[*it];
    bb += a[ind].second;
    ans = max(ans, aa + bb);
    aa -= a[ind].first;
    it--;
  }
  return ans;
}

void dodaj(int ind) {
  active.insert(pos_inv[ind]);
  a_sum += a[ind].first;
  b_sum += a[ind].second;
}

void brisi(int ind) {
  active.erase(pos_inv[ind]);
  a_sum -= a[ind].first;
  b_sum -= a[ind].second;
}

int main(void) {
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
    dodaj(i);
  }

  cout << query() << endl;

  for (const auto &q : queries) {
    int ind = q.second;
    if (q.first == 0) {
      dodaj(ind);
      cout << query() << endl;
    } else if (q.first == 1) {
      brisi(ind);
      cout << query() << endl;
    } else {
      vector<int> ans;
      for (int i : active) {
        ans.push_back(pos[i]);
      }
      for (auto ind : ans) cout << ind + 1 << " ";
      for (int i = 0; i < (int)ans.size(); ++i)
        cout << ans[i] + 1 << " \n"[i + 1 == ans.size()];
    }
  }

  return 0;
}
