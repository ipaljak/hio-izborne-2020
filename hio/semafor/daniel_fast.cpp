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

ll modpot(ll b, ll pot) {
  ll ret = 1;
  for (; pot; pot >>= 1) {
    if (pot & 1) ret = (ret * b) % mod;
    b = (b * b) % mod;
  }
  return ret;
}

ll modinv(ll b) {
  return modpot(b, mod-2);
}

int binom[55][55];
void precompute_binoms(int n) {
  for (int i = 0; i <= n; i++) {
    binom[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      binom[i][j] = binom[i-1][j] + binom[i-1][j-1];
    }
  }
}

ll N, M, K;
int X;
int sz;
int nums;
int numbits;
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
    ok &= is_digit[(mask & halves[1]) >> 5];
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
  Matrix P(numbits + 1, 0);
  P.a[0][1] = numbits;
  for (int i = 1; i < numbits; i++) {
    P.a[i][i-1] = i;
    P.a[i][i+1] = numbits - i; 
  } 
  P.a[numbits][numbits-1] = numbits;
  //cerr << P << endl;

  P = P ^ pot; 
  //cerr << P << endl;

  Matrix A(sz, 0);
  REP(i, sz) REP(j, sz) {
    int r = __builtin_popcount(i ^ j);
    A.a[i][j] = P.a[0][r] * modinv(binom[numbits][r]) % mod;
  }
  return A;
}
 
void solve() {
  //TRACE(K);
  precompute_binoms(numbits + 1);
  Matrix A = get_intermediate_matrix(K);
  Matrix B = get_intermediate_matrix(N % K);
  map<int, int> new_index;

  int cnt = 0;
  REP(i, sz) {
    if (is_good(i)) {
      new_index[i] = cnt++;
    }
  }
  assert(cnt == nums);
  Matrix C(nums, 0), D(nums, 0);

  REP(i, sz) REP(k, sz) {
    if (is_good(i) && is_good(k)) {
      C[new_index[i]][new_index[k]] = A.a[i][k]; 
      D[new_index[i]][new_index[k]] = B.a[i][k]; 
    }
    else {
      A.a[i][k] = 0;
      B.a[i][k] = 0;
    }
  }


  C = C ^ (N/K);

  C = C * D;


  for (int Y = 0; Y < nums; Y++) {
    cout << C.a[new_index[to_mask(X)]][new_index[to_mask(Y)]] << endl;
  }
}

void load() {
  cin >> M >> N >> K >> X;
  assert(M == 1 || M == 2);
  sz = (M == 1) ? 32 : 1024;
  nums = (M == 1) ? 10 : 100;
  numbits = (M == 1) ? 5 : 10;

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

