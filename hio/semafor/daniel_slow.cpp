#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<
#define debug(...) fprintf(stderr, __VA_ARGS__)
typedef long long ll;
typedef std::pair<ll, ll> pii;
#define double long double
typedef double db;
using namespace std;

 ll MaxN = 200100;
 ll mod = 1e9 + 7;

struct Matrix {
  vector<vector<ll>> a;
  int dim;
  vector<ll>& operator [] (ll r) { return a[r]; };

  Matrix(int DIM, ll x = 0) {
    dim = DIM;
    REP(i, DIM) a.emplace_back();
    REP(i, DIM) REP(j, DIM) a[i].push_back(0);
    if (x) REP(i, DIM) a[i][i] = x; // identity
  }
};

Matrix operator * ( Matrix &A,  Matrix &B) {
  int DIM = A.dim;
   ll mod2 = ll(mod) * mod;
  Matrix C(DIM);
  REP(i, DIM) REP(j, DIM) {
    ll w = 0;
    REP(k, DIM) {
      w += ll(A[i][k]) * B[k][j];
      if (w >= mod2) w -= mod2;
    }
    C[i][j] = w % mod;
  }
  return C;
}

Matrix operator ^ ( Matrix &A, ll b) {
  Matrix R = Matrix(A.dim, 1);
  for (; b > 0; b /= 2) {
    if (b % 2) R = R*A;
    A = A*A;
  }
  return R;
}

ostream& operator<< (ostream& f,  Matrix &A) {
  for (int i = 0; i < A.dim; i++) {
    for (int j = 0; j < A.dim; j++) {
      f << A.a[i][j];
      f << " ";
    }
    f << endl;
  }
  return f;
}

ll N, M, K;
int X;
int sz; 
int nums;
vector<int> halves = {31, 31 << 5};
vector<int> digits = {2+8,    2,    1+8,  1+2+4,     2+16, 
                      1+4+16, 4+8,  1+2,  1+4+8+16, 1+2+4+16};
bool is_digit[33];

int to_mask(int Y) {
  int ret = digits[Y % 10];
  if (M == 2) {
    ret += (digits[Y / 10] << 5);
  }
  return ret;
}

bool is_good(int mask) {
  bool ok = is_digit[mask & halves[0]];
  if (M == 2) { /* maybe unnecessary */
    ok &= is_digit[mask & halves[1]];
  }
  return ok;
}

Matrix power_hypercube(ll pot) {
  Matrix H(sz, 0);  
  REP(i, sz) REP(j, sz) {
    if (__builtin_popcount(i ^ j) == 1) {
      H.a[i][j] = 1;
    }
  }
  return H ^ pot; 
}

Matrix get_intermediate_matrix(ll pot) {
  return power_hypercube(pot);
}
 
void solve() {
  TRACE(K);
  Matrix A = get_intermediate_matrix(K);
//  cout << A << endl;
  Matrix B = get_intermediate_matrix(N % K);
//  cout << B << endl;
  TRACE("got matrices");
  REP(i, sz) REP(k, sz) {
    if (is_good(i) && is_good(k)) {
      TRACE(i _ k);    
    }
    else {
      A.a[i][k] = 0;
    }
  }

//  cout << A << endl;

  A = A ^ (N / K);
  A = A * B;

//  cout << A << endl;

  for (int Y = 0; Y < nums; Y++) {
    cout << A.a[to_mask(X)][to_mask(Y)] << endl;
  }
}

void load() {
  cin >> M >> N >> K >> X;
  assert(M == 1 || M == 2);
  sz = (M == 1) ? 32 : 1024;
  nums = (M == 1) ? 10 : 100;

  for (auto d: digits) {
    is_digit[d] = true;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  load();
  solve();
  return 0;
}

