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
#include "process.h"

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

bool check_second_part(const vector <int> &c_recon, int n, const vector <Operation> &ops, const vector <int> &seq) {
  int m = ops.size();
  if (c_recon.size() != m)
    return false;
  vector <bool> bio(m + 1);
  for (auto it : c_recon) {
    if (it < 1 || it > m || bio[it])
      return false;
    bio[it] = true;
  }
  return process_operations(n, ops, c_recon) == seq;
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
  const string PARTIAL_FIRST = "Prvi red je tocan, drugi nije.";

  // Read official input
  int N, M;

  if (!(fin >> N)) finish(0, TEST_DATA_ERROR);
  if (!(fin >> M)) finish(0, TEST_DATA_ERROR);
  
  vector <Operation> ops(M);
  REP(i, M) {
    if (!(fin >> ops[i].lft)) finish(0, TEST_DATA_ERROR);
    if (!(fin >> ops[i].rig)) finish(0, TEST_DATA_ERROR);
    if (!(fin >> ops[i].clr)) finish(0, TEST_DATA_ERROR);
  }
  
  vector <int> seq(N);
  REP(i, N)
    if (!(fin >> seq[i]))
      finish(0, TEST_DATA_ERROR);

  // Read official output
  string official_output_ans;
  if (!(foff >> official_output_ans)) 
    finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  string c_output;
  if (!(fout >> c_output)) 
    finish(0, WRONG_OUTPUT_FORMAT);
  
  vector <int> c_recon(M);
  if (c_output == "DA") 
    REP(i, M)
      if (!(fout >> c_recon[i]))
        finish(0.0, WRONG);
  
  string excess;
  if (fout >> excess)
    finish(0.0, WRONG);

  bool first_part = (official_output_ans == c_output);
  bool second_part = (c_output == "NE" || check_second_part(c_recon, N, ops, seq));
  
  if (first_part && second_part) 
    finish(1.0, CORRECT);
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
