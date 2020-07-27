// PAZI OVO NIJE OK ZA CMS EVALUATOR
//
// Checker to be used by HSIN evaluator.
//
// Usage: [checker] [input] [official_output] [contestant_output]
//
// Score (real between 0.0 and 1.0) written on stdout.
// Textual description of the result written on stderr.

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <queue>

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
  const string PARTIAL = "Suboptimalno rješenje.";

  // Read official input
  int n, m;
  if (!(fin >> n >> m)) finish(0, TEST_DATA_ERROR);

  int opt = ceil(n * m, n + m) + 1;

  // Read contestant's output
  int N = 2 * n + 1, M = 3 * m + 1;
  vector<string> G(N);
  for (auto& row : G) {
      getline(fout, row);
      if ((int)row.size() != M) finish(0, WRONG_OUTPUT_FORMAT);
  }
  string garbage;
  if (fout >> garbage) finish(0, WRONG_OUTPUT_FORMAT);

  // Check if output is a valid graph
  for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
          if (i % 2 == 0) {
              if (j % 3 == 0 && G[i][j] != 'o') finish(0, WRONG);
              if (j % 3 == 1 && G[i][j] != G[i][j + 1]) finish(0, WRONG);
              if (j % 3 != 0 && G[i][j] != '-' && G[i][j] != ' ') finish(0, WRONG);
          } else {
              if (j % 3 == 0 && G[i][j] != '|' && G[i][j] != ' ') finish(0, WRONG);
              if (j % 3 != 0 && G[i][j] != ' ') finish(0, WRONG);
          }
      }
  }

  // Check if graph is connected
  vector<vector<bool>> vis(N, vector<bool>(M));
  queue<pair<int, int>> Q;
  Q.push({0, 0});
  while (!Q.empty()) {
      int i = Q.front().first, j = Q.front().second;
      Q.pop();
      if (i == -1 || i == N || j == -1 || j == M || G[i][j] == ' ') continue;
      if (vis[i][j]) continue;
      vis[i][j] = true;

      Q.push({i - 1, j});
      Q.push({i + 1, j});
      Q.push({i, j - 1});
      Q.push({i, j + 1});
  }
  for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
          if (G[i][j] != ' ' && !vis[i][j]) finish(0, WRONG);
      }
  }

  // Check if graph is a tree and count the score
  int score = 0, edges = 0;
  for (int i = 1; i < N; i += 2) {
      int cnt = 0;
      for (int j = 0; j < M; j += 3) cnt += G[i][j] == '|';
      score = max(score, cnt);
      edges += cnt;
  }
  for (int j = 1; j < M; j += 3) {
      int cnt = 0;
      for (int i = 0; i < N; i += 2) cnt += G[i][j] == '-';
      score = max(score, cnt);
      edges += cnt;
  }
  if (edges != n * m + n + m) finish(0, WRONG);

  // TOOO grading function
  if (score == opt) finish(1, CORRECT);
  else finish((double)score / opt, PARTIAL + " score:" + to_string(score) + " optimal:" + to_string(opt));

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
