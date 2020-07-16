// PAZI OVO NIJE OK ZA CMS EVALUATOR
//
// Checker to be used by HSIN evaluator.
//
// Usage: [checker] [input] [official_output] [contestant_output]
//
// Score (real between 0.0 and 1.0) written on stdout.
// Textual description of the result written on stderr.

#include <functional>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>

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

bool check_second_part(const vector <int> &c_recon, int n, const vector <vector <int>> &adj, const vector <int> &sheep) 
{  
  queue <int> Q;
  vector <int> dist(n + 1, -1);
  vector <bool> covered(n + 1, false);
  
  for (auto it : sheep) {
    dist[it] = 0;
    Q.push(it);
  }
  
  while (!Q.empty()) {
    int curr = Q.front();
    Q.pop();
    for (auto it : adj[curr])
      if (dist[it] == -1) {
        dist[it] = dist[curr] + 1;
        Q.push(it);
      }
  }
  
  function <void(int)> dfs_cover = [&](int x) {
    if (covered[x])
      return;
    covered[x] = true;
    for (auto it : adj[x])
      if (dist[x] == dist[it] + 1)
        dfs_cover(it);
  };
  
  for (auto it : c_recon) {
    if (it < 1 || it > n)
      return false;
    dfs_cover(it);
  }
  
  for (auto it : sheep)
    if (!covered[it])
      return false;
      
  return true;
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
  const string TEST_DATA_ERROR = "Greska u sluzbenom ulazu ili izlazu.";
  const string WRONG = "Netocno.";
  const string CORRECT = "Tocno.";
  const string PANIC = "Greska u checkeru. Posaljite clarification request.";
  const string PARTIAL_FIRST = "Prvi red je tocan, drugi nije.";

  // Read official input
  int N, K;
  vector <vector <int>> adj;
  vector <int> sheep;
  
  if (!(fin >> N)) finish(0, TEST_DATA_ERROR);
  if (!(fin >> K)) finish(0, TEST_DATA_ERROR);
  
  adj.resize(N + 1);
  sheep.resize(K);
  
  REP(i, N - 1) {
    int u, v;
    if (!(fin >> u)) finish(0, TEST_DATA_ERROR);
    if (!(fin >> v)) finish(0, TEST_DATA_ERROR);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  
  REP(i, K) 
    if (!(fin >> sheep[i])) 
      finish(0, TEST_DATA_ERROR);

  // Read official output
  int official_output_val;
  if (!(foff >> official_output_val)) 
    finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  int c_output;
  if (!(fout >> c_output)) 
    finish(0, WRONG_OUTPUT_FORMAT);
    
  if (c_output > official_output_val) 
    finish(0.0, WRONG);
  
  vector <int> c_recon(c_output);
  REP(i, c_output) 
    if (!(fout >> c_recon[i]))
      finish(0.0, WRONG);
    
  string excess;
  if (fout >> excess)
    finish(0.0, WRONG);
    
  if (check_second_part(c_recon, N, adj, sheep)) {
    if (c_output < official_output_val) 
      finish(1.0, PANIC); 
    finish(1.0, CORRECT);
  }
  else
    finish(0.0, WRONG);

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
