#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<
#define debug(...) fprintf(stderr, __VA_ARGS__)
typedef long long ll;
typedef std::pair<int, int> pii;
#define X first
#define Y second
#define double long double
typedef double db;
using namespace std;

const int MaxN = 1100;
const int Mod = 1e9 + 7;
// {0, 1, ..., N} \times {0, 1, ..., M}

struct Segment {
  char dir;
  pii prvi, drugi; // always sorted as pairs
};

int cceil(int a, int b) {
  return (a + b - 1) / b;
}

int M, N;
vector<Segment> sol;
bool gore[MaxN][MaxN], desno[MaxN][MaxN];
bool visited[MaxN][MaxN];
char pr[3*MaxN][3*MaxN];

bool good(int i, int k) {
  return i >= 0 && i <= N && k >= 0 && k <= M;
}

void addLeft(int i, int k) {
  assert(i >= 1 && good(i, k));
  Segment mov = {'H', {i-1, k}, {i, k}};
  sol.push_back(mov);
}

void addRight(int i, int k) {
  assert(i <= N-1 && good(i, k));
  Segment mov = {'H', {i, k}, {i+1, k}};
  sol.push_back(mov);
}

void addDown(int i, int k) {
  assert(k >= 1 && good(i, k));
  Segment mov = {'V', {i, k-1}, {i, k}};
  sol.push_back(mov);
}

void addUp(int i, int k) {
  assert(k <= M-1 && good(i, k));
  Segment mov = {'V', {i, k}, {i, k+1}};
  sol.push_back(mov);
}

void printMatrix() {
  // prva koord za stupce, druga za retke
  REP(i, N+1) REP(k, M+1) {
    pr[3*i][2*k] = 'o';
  }
  REP(i, N+1) REP(k, M+1) {
    if (gore[i][k]) {
      pr[3*i][2*k + 1] = '|';
    }
    if (desno[i][k]) {
      pr[3*i + 1][2*k] = '-';
      pr[3*i + 2][2*k] = '-';
    }
  }

  for (int r = 2*M; r >= 0; r--) {
    for (int s = 0; s <= 3*N; s++) {
      cout << pr[s][r];
    }
    cout << endl;
  }
}

void parse_sol() {
  for (auto &seg: sol) {
    if (seg.dir == 'H') {
      desno[seg.prvi.X][seg.prvi.Y] = true;
    }
    else if (seg.dir == 'V') {
      gore[seg.prvi.X][seg.prvi.Y] = true;
    }
    else {
      assert(false);
    }
  }
}


void daniel_solve() {
  int A = cceil(M*N, M + N);
  int D = cceil(N, A);

  REP(i, N) {
    addRight(i, 0);
  }
  REP(k, M) {
    addUp(0, k);
  }

  for (int i = D; i <= N; i += D) {
    REP(k, M) {
      addUp(i, k);
    }
    for (int j = i-D; j < i; j++) {
      for (int k = 1; k <= M; k++) {
        if ((j + k) % D != 0) {
          addRight(j, k);
        }
      }
    }
  }

  // deal with residue later
  if (N % D != 0) {
    REP(k, M) {
      addUp(N, k);
    }
    int G = N % D;
    for (int j = N-G; j < N; j++) {
      for (int k = 1; k <= M; k++) {
        if ((j + k) % G != 0) {
          addRight(j, k);
        }
      }
    }
  }

}

void solve() {
  daniel_solve();
  parse_sol();
  printMatrix();
}

void reset() {
  sol.clear();
  REP(i, MaxN) {
    REP(j, MaxN) {
      gore[i][j] = false;
      desno[i][j] = false;
      visited[i][j] = false;
    }
  }

  REP(i, 3*MaxN)
    REP(j, 3*MaxN)
      pr[i][j] = ' ';
}

void load() {
  cin >> N >> M;
  if (N < M) swap(N, M);
}

int main() {
  ios_base::sync_with_stdio(false);
  reset();
  load();
  solve();
  return 0;
}

