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
#include <math.h>

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

// Returns length of longest palindromic substring.
int manacher(const string& s) {
    int n = s.size();

    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    int l1 = 2 * (*max_element(d1.begin(), d1.end())) - 1;

    vector<int> d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
    int l2 = 2 * (*max_element(d2.begin(), d2.end()));

    return max(l1, l2);
}

double score(int out, int off) {
    return pow(1 + out - off, -0.4);
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
  const string PARTIAL = "Suboptimalno rjesenje.";

  // Read official input
  int n;
  if (!(fin >> n)) finish(0, TEST_DATA_ERROR);

  // Read official output
  string off_str;
  if (!(foff >> off_str)) finish(0, TEST_DATA_ERROR);
  if ((int)off_str.size() != n) finish(0, TEST_DATA_ERROR);
  if (off_str.find_first_not_of("01") != string::npos) finish(0, TEST_DATA_ERROR);
  int off_ans = manacher(off_str);

  // Read contestant's output
  string out_str;
  if (!(fout >> out_str)) finish(0, WRONG_OUTPUT_FORMAT);
  if ((int)out_str.size() != n) finish(0, WRONG_OUTPUT_FORMAT);
  if (out_str.find_first_not_of("01") != string::npos) finish(0, WRONG_OUTPUT_FORMAT);
  int out_ans = manacher(out_str);

  string garbage;
  if (fout >> garbage) finish(0, WRONG_OUTPUT_FORMAT);


  if (out_ans < off_ans) finish(0, TEST_DATA_ERROR);

  if (out_ans == off_ans) finish(1, CORRECT);
  else finish(score(out_ans, off_ans), PARTIAL);

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
