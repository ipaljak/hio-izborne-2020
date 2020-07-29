// PAZI OVO NIJE OK ZA CMS EVALUATOR
//
// Checker to be used by HSIN evaluator.
//
// Usage: [checker] [input] [official_output] [contestant_output]
//
// Score (real between 0.0 and 1.0) written on stdout.
// Textual description of the result written on stderr.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

/**
 * @param p fraction of points awarded to the contestant.
 * @pararm m error message displayed to the contestant.
 */
void finish(double p, const string& m);

int ceil(int a, int b) { return (a - 1) / b + 1; }

llint get_time(const vector<int> &order, const vector<pair<int, int>> &guest) {
  llint t = 0, prep_wait = 0, eat_wait = 0;
  int prep_id = 0, eat_id = (int) order.size() / 2;
  unordered_map<int, llint> prepared;
  while (prep_id < (int) order.size() / 2 || eat_id < (int) order.size()) {
    if (prep_id < (int) order.size() / 2 && t >= prep_wait) {
      prep_wait = t + (llint) guest[order[prep_id] - 1].first;
      prepared[order[prep_id]] = prep_wait;
      prep_id++;
    }
    if (eat_id < (int)order.size() && t >= eat_wait &&
        prepared.find(order[eat_id]) != prepared.end() &&
        t >= prepared[order[eat_id]]) {
      eat_wait = t + (llint) guest[order[eat_id] - 1].second;
      eat_id++;
    }
    if (min(prep_wait, eat_wait) > t)
      t = min(prep_wait, eat_wait);
    else
      t = max(prep_wait, eat_wait);
  }
  return t;
}

bool check_order(const vector<int> &off_order, const vector<int> &cont_order,
                 const vector<pair<int, int>> &guest) {
  llint A = get_time(off_order, guest), B = get_time(cont_order, guest);
  if (A != B) TRACE(A _ B);
  return get_time(off_order, guest) == get_time(cont_order, guest);
}

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream& fin, ifstream& foff, ifstream& fout)
{
  const string WRONG_OUTPUT_FORMAT = "Krivo formatiran izlaz.";
  const string TEST_DATA_ERROR = "Greška u službenom ulazu ili izlazu.";
  const string WRONG = "Netočno.";
  const string CORRECT = "Točno.";

  const int MAXN = 2e5 + 10;
  bool deleted[2 * MAXN];
  memset(deleted, false, sizeof deleted);

  // Read official input before queries
  int n, k;
  vector<pair<int, int>> guest;
  if (!(fin >> n >> k)) finish(0, TEST_DATA_ERROR);
  for (int i = 0; i < n; ++i) {
    int a, b;
    if (!(fin >> a >> b)) finish(0, TEST_DATA_ERROR);
    guest.emplace_back(a, b);
  }

  // Compare output before queries
  llint off_time, cont_time;
  if (!(foff >> off_time)) finish(0, TEST_DATA_ERROR);
  if (!(fout >> cont_time)) finish(0, WRONG_OUTPUT_FORMAT);
  if (off_time != cont_time) finish(0, WRONG);

  int guest_cnt = n;

  // Process queries
  for (int i = 0; i < k; ++i) {
    // Read query from official input
    string s;
    if (!(fin >> s)) finish(0, TEST_DATA_ERROR);

    if (s == "DOLAZI") {
      int a, b;
      if (!(fin >> a >> b)) finish(0, TEST_DATA_ERROR);
      guest.emplace_back(a, b);
      ++guest_cnt;
      llint off_time, cont_time;
      if (!(foff >> off_time)) finish(0, TEST_DATA_ERROR);
      if (!(fout >> cont_time)) finish(0, WRONG_OUTPUT_FORMAT);
      if (off_time != cont_time) finish(0, WRONG);
    }

    if (s == "ODLAZI") {
      int x;
      if (!(fin >> x)) finish(0, TEST_DATA_ERROR);
      if (deleted[x]) finish(0, TEST_DATA_ERROR);
      deleted[x] = true;
      --guest_cnt;
      if (guest_cnt <= 0) finish(0, TEST_DATA_ERROR);
      llint off_time, cont_time;
      if (!(foff >> off_time)) finish(0, TEST_DATA_ERROR);
      if (!(fout >> cont_time)) finish(0, WRONG_OUTPUT_FORMAT);
      if (off_time != cont_time) finish(0, WRONG);
    }

    if (s == "POREDAK") {
      vector<int> off_order, cont_order;
      for (int j = 0; j < 2 * guest_cnt; ++j) {
        int x;
        if (!(foff >> x)) finish(0, TEST_DATA_ERROR);
        off_order.emplace_back(x);
      }
      for (int j = 0; j < 2 * guest_cnt; ++j) {
        int x;
        if (!(fout >> x)) finish(0, WRONG_OUTPUT_FORMAT);
        if (x <= 0 || x >= 2 * MAXN - 5 || deleted[x]) finish(0, WRONG);
        cont_order.push_back(x);
      }
      set<int> off_lo, off_hi, cont_lo, cont_hi;
      for (int j = 0; j < 2 * guest_cnt; ++j) {
        if (j < guest_cnt) {
          off_lo.insert(off_order[j]);
          cont_lo.insert(cont_order[j]);
        } else {
          off_hi.insert(off_order[j]);
          cont_hi.insert(cont_order[j]);
        }
      }
      if ((int) off_lo.size() != guest_cnt || (int) off_hi.size() != guest_cnt)
        finish(0, TEST_DATA_ERROR);
      if (off_lo != cont_lo || off_hi != cont_hi) finish(0, WRONG);
      if (!check_order(off_order, cont_order, guest)) finish(0, WRONG);
    }
  }

  finish(1, CORRECT);
  // The function MUST terminate before this line via finish()!
}

void finish(double p, const string& m) {
  cout << p << endl;
  cout << m << endl;
  exit(0);
}

int main(int argc, char *argv[])
{
  assert(argc == 4);

  ifstream fin(argv[1]);
  ifstream foff(argv[2]);
  ifstream fout(argv[3]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, foff, fout);
  assert(false); // checker must terminate via finish() before exiting!

  return 0;
}
