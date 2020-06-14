#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MOD = 1e9 + 7;

struct Matrix {
  int n;
  vector<vector<int>> mat;

  Matrix() = delete;

  Matrix(int n) : n(n) {
    mat.resize(n, vector<int>(n, 0));
  }

  bool operator==(const Matrix &rhs) const { return rhs.mat == this->mat; }

  vector<int> &operator[](int i) { return mat[i]; }

  static Matrix I(int n) {
    Matrix ret(n);
    for (int i = 0; i < n; ++i)
      ret[i][i] = 1;
    return ret;
  }

  static Matrix Q(int n) {
    Matrix ret(1 << n);
    for (int i = 0; i < 1 << n; ++i)
      for (int j = 0; j < 1 << n; ++j)
        if (__builtin_popcount(i ^ j) == 1)
          ret[i][j] = 1;
    return ret;
  }
};

int add(int a, int b) {
  if (a + b >= MOD) return a + b - MOD;
  if (a + b < 0) return a + b + MOD;
  return a + b;
}

int mul(int a, int b) {
  return (llint) a * b % MOD;
}

Matrix std_mul(Matrix &A, Matrix &B) {
  Matrix ret(A.n);
  for (int k = 0; k < A.n; ++k)
    for (int i = 0; i < A.n; ++i)
      for (int j = 0; j < A.n; ++j)
        ret[i][j] = add(ret[i][j], mul(A[i][k], B[k][j]));
  return move(ret);
}

Matrix my_mul(Matrix &A, Matrix &B) {
  if (A.n == 2) return std_mul(A, B);
  Matrix X(A.n / 2), Y(A.n / 2), Z(A.n / 2), W(A.n / 2);
  for (int i = 0; i < A.n / 2; ++i) {
    for (int j = 0; j < A.n / 2; ++j) {
      X[i][j] = A[i][j];
      Y[i][j] = A[i][A.n / 2 + j];
      Z[i][j] = B[i][j];
      W[i][j] = B[i][A.n / 2 + j];
    }
  }
  Matrix XZ = my_mul(X, Z), XW = my_mul(X, W);
  Matrix YZ = my_mul(Y, Z), YW = my_mul(Y, W);
  Matrix ret(A.n);
  for (int i = 0; i < A.n; ++i) {
    for (int j = 0; j < A.n; ++j) {
      int n = A.n / 2;
      if (i < n && j < n) ret[i][j] = add(XZ[i][j], YW[i][j]);
      if (i < n && j >= n) ret[i][j] = add(XW[i][j - n], YZ[i][j - n]);
      if (i >= n && j < n) ret[i][j] = add(YZ[i - n][j], XW[i - n][j]);
      if (i >= n && j >= n) ret[i][j] = add(YW[i - n][j - n], XZ[i - n][j - n]);
    }
  }
  return move(ret);
}

Matrix pow(Matrix A, int exp, Matrix (*mul)(Matrix &, Matrix &)) {
  Matrix ret = Matrix::I(A.n);
  while (exp) {
    if (exp & 1) {
      ret = (*mul)(ret, A);
      --exp;
    }
    A = (*mul)(A, A);
    exp >>= 1;
  }
  return ret;
}

int main(void) {
  srand(time(NULL));
  for (int n = 1; n <= 7; ++n) {
    for (int t = 0; t < 25; ++t) {
      int k = rand() % MOD;
      TRACE(n _ k);
      Matrix Q = Matrix::Q(n);
      assert(pow(Q, k, my_mul) == pow(Q, k, std_mul));
    }
  }

  return 0;
}
