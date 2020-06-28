// Server to be used by evaluator.
//
// Usage: TASK_server input_file log_file output_file
//
// To test locally:
//   mkfifo temp
//   ./TASK_server test/TASK.in.1 flog foutput < temp | ./MY_SOLUTION > temp
//

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <unistd.h>

using namespace std;

#ifdef ENGLISH

/******************************* ENGLISH ***************************************/

#define CANNOT_READ_N "Input file error: cannot read integer n."
#define N_OUT_OF_BOUNDS "Input file error: n has to be between %d and %d."
#define CANNOT_READ_P "Input file error: cannot read the permutation element."
#define P_NOT_A_PERMUTATION "Input file error: initial permutation P is not a permutation."
#define CANNOT_READ_M "Input file error: cannot read integer m."
#define M_OUT_OF_BOUNDS "Input file error: m has to be between %d and %d."
#define CANNOT_READ_AB "Input file error: cannot read the %d-th pair a and b."
#define A_OUT_OF_BOUNDS "Input file error: a has to be between %d and %d."
#define B_OUT_OF_BOUNDS  "Input file error: b has to be between %d and %d."
#define AB_SAME "Input file error: a and b have to be different."
#define P_DOES_NOT_SATISFY_S "Input file error: the initial permutation P doesn't satisfy the requirements "
#define SENDING_N_AND_P "Sending n and the permutation P to contestant program..."
#define WAITING "Waiting for queries..."
#define WA_PREMATURE_TERMINATION "Wrong answer: Contestant program termimanted execution without sending a solution."
#define COMMAND_RECEIVED_PRE "Received command '"
#define COMMAND_RECEIVED_POST "' from the contestant program."
#define WA_TOO_MANY_QUERIES "Wrong answer: Contestant program asked too many queries."
#define WA_UNKNOWN_COMMAND "Wrong answer: Unknown command '%s'."
#define WA_CANNOT_READ_Q "Wrong answer: Cannot read the permutation in the %d-th query."
#define WA_Q_NOT_A_PERMUTATION "Wrong answer: The permutation in the %d-th query is not is not a permutation."
#define LOG_QUERY  "Query "
#define LOG_ANSWER ", Answer: "
#define WAITING_FOR_SOLUTION "Waiting for the solutions..."
#define WA_CANNOT_READ_A "Wrong answer: Cannot read the first permutation in the solution."
#define WA_A_NOT_A_PERMUTATION "Wrong answer: First permutation in the solution is not a permutation."
#define WA_CANNOT_READ_B "Wrong answer: Cannot read the second permutation in the solution."
#define WA_B_NOT_A_PERMUTATION "Wrong answer: Second permutation in the solution is not a permutation."
#define CONTESTANT_LOWEST "Contestant reported lowest permutation:"
#define CONTESTANT_HIGHEST "Contestant reported highest permutation:"
#define WA_INCORRECT "Wrong answer: the solution is not correct."
#define CORRECT "Correct! Queries used: "

#else

/******************************* CROATIAN ***************************************/

#define CANNOT_READ_N "Neispravna ulazna datoteka: ne mogu procitati broj n."
#define N_OUT_OF_BOUNDS "Neispravna ulazna datoteka: n mora biti izmedju %d i %d."
#define CANNOT_READ_P "Neispravna ulazna datoteka: ne mogu procitati element permutacije."
#define P_NOT_A_PERMUTATION "Neispravna ulazna datoteka: pocetna permutacija P nije permutacija."
#define CANNOT_READ_M "Neispravna ulazna datoteka: ne mogu procitati broj m."
#define M_OUT_OF_BOUNDS "Neispravna ulazna datoteka: m mora biti izmedju %d i %d."
#define CANNOT_READ_AB "Neispravna ulazna datoteka: ne mogu procitati %d-ti par a i b."
#define A_OUT_OF_BOUNDS "Neispravna ulazna datoteka: a mora biti izmedju %d i %d."
#define B_OUT_OF_BOUNDS  "Neispravna ulazna datoteka: b mora biti izmedju %d i %d."
#define AB_SAME "Neispravna ulazna datoteka: a i b moraju biti razliciti."
#define P_DOES_NOT_SATISFY_S "Neispravna ulazna datoteka: pocetna permutacije P ne zadovoljava uvjete "
#define SENDING_N_AND_P "Saljem broj n i permutaciju P programu..."
#define WAITING "Cekam upite..."
#define WA_PREMATURE_TERMINATION "Krivo rjesenje: Program je zavrsio izvodjenje prije nego sto je poslao rjesenje."
#define COMMAND_RECEIVED_PRE "Primio naredbu '"
#define COMMAND_RECEIVED_POST "' od programa."
#define WA_TOO_MANY_QUERIES "Krivo rjesenje: Program je postavio previse upita."
#define WA_UNKNOWN_COMMAND "Krivo rjesenje: Nepoznata naredba '%s'."
#define WA_CANNOT_READ_Q "Krivo rjesenje: Ne mogu procitati permutaciju u %d-tom upitu."
#define WA_Q_NOT_A_PERMUTATION "Krivo rjesenje: Permutacija Q u %d-tom upitu nije permutacija."
#define LOG_QUERY  "Upit "
#define LOG_ANSWER ", Odgovor: "
#define WAITING_FOR_SOLUTION "Cekam rjesenja..."
#define WA_CANNOT_READ_A "Krivo rjesenje: Ne mogu procitati prvu permutaciju u rjesenju."
#define WA_A_NOT_A_PERMUTATION "Krivo rjesenje: Prva permutacija u rjesenju nije permutacija."
#define WA_CANNOT_READ_B "Krivo rjesenje: Ne mogu procitati drugu permutaciju u rjesenju."
#define WA_B_NOT_A_PERMUTATION "Krivo rjesenje: Druga permutacija u rjesenju nije permutacija."
#define CONTESTANT_LOWEST "Natjecatelj kaze da je najmanja permutacija:"
#define CONTESTANT_HIGHEST "Natjecatelj kaze da je najveca permutacija:"
#define WA_INCORRECT "Krivo rjesenje: Najmanja ili najveca permutacija nije ispravna."
#define CORRECT "Tocno! Broj upita: "

#endif

ifstream finput;   // read from the input file (test case description)
ofstream flog;     // write to an unofficial log for debugging purposes
ofstream foutput;  // write the output, first the score for the test case,
                   // then the output the contestants will see in the system

// assert a condition, awards 0 points if condition fails, same format as a regular printf
void test_condition(bool condition, const char* format, ...) {
  if (!condition) {
    static char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);
    va_end(argptr);

    foutput << 0 << endl << dest << endl;
    flog << dest << endl;
    exit(0);
  }
}

// Check if P[i] < P[j] for every (i, j) in S.
// - P: a permutation of integers 0, ..., n-1
// - S: a list of pairs of different integers between 0 and n-1 inclusive
//
int satisfies(const vector<int> &P, const vector<pair<int, int>> &S) {
  for (int i=0; i<(int)S.size(); i++)
    if (!(P[S[i].first] < P[S[i].second]))
      return 0;
  return 1;
}

// Check if Q is a permutation of elements 0 ... n-1 where
// n is the size of Q.
int is_permutation(const vector<int> &Q) {
  int n = (int)Q.size();
  for (int i=0; i<n; i++)
    if (Q[i] < 0 || Q[i] > n-1)
      return 0;
  vector<int> cnt(n, 0);
  for (int i=0; i<n; i++)
    cnt[Q[i]]++;
  for (int i=0; i<n; i++)
    if (cnt[i] != 1)
      return 0;
  return 1;
}

// Find lowest (or highest) permutation of integes of integers 0, ..., n-1
// satisfiying the requirements in S.
struct solver {
  int n;
  vector<vector<int>> g;
  vector<int> done;
  vector<int> out;

  solver(int _n, const vector<pair<int, int>> &S) {
    n = _n;
    g = vector<vector<int>>(n, vector<int>(n, 0));
    for (int i=0; i<(int)S.size(); i++)
      g[S[i].first][S[i].second] = 1;
    for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        for (int k=0; k<n; k++)
          g[j][k] |= g[j][i] & g[i][k];
  }

  void do_solve(const vector<int> &x, int lowest) {
    if ((int)x.size() == 0)
      return ;
    for (int i=0; i<(int)x.size(); i++) {
      if (done[x[i]])
        continue ;
      vector<int> y;
      done[x[i]] = 1;
      for (int j=0; j<(int)x.size(); j++) {
        if (done[x[j]])
          continue ;
        if (i == j)
          continue ;
        if ((lowest && g[x[j]][x[i]]) || (!lowest && !g[x[i]][x[j]]))
          y.push_back(x[j]);
      }
      do_solve(y, lowest);
      out.push_back(x[i]);
    }
  }

  vector<int> solve(int lowest) {
    vector<int> x;
    for (int i=0; i<n; i++)
      x.push_back(i);
    done = vector<int>(n, 0);
    out = vector<int>();
    do_solve(x, lowest);
    vector<int> p(n, 0);
    for (int i=0; i<n; i++)
      p[out[i]] = i;
    return p;
  }
};


// - read the test case from finput,
// - read the contestant's output from cin
// - write to the contestant's input with cout
// - log with flog
// - score and explanation to foutput
void main_problem_interaction() {
  const int MIN_N = 2;
  const int MAX_N = 100;
  const int MIN_M = 0;
  const int MAX_M = 10000;

  const string QUERY_COMMAND = "query";
  const string END_COMMAND = "end";

  const int QUERY_LIMIT = 5000;

  int n; // size of the permutation
  int m; // number of pairs of elements with known order

  test_condition(bool(finput >> n), CANNOT_READ_N);
  test_condition(MIN_N <= n && n <= MAX_N, N_OUT_OF_BOUNDS, MIN_N, MAX_N);

  // Read the initial permutation P
  vector<int> P(n);
  for (int i=0; i<n; i++) {
    test_condition(bool(finput >> P[i]), CANNOT_READ_P);
    P[i]--;
  }

  // Check the permutation
  test_condition(is_permutation(P), P_NOT_A_PERMUTATION);

  test_condition(bool(finput >> m), CANNOT_READ_M);
  test_condition(MIN_M <= m && m <= MAX_M, M_OUT_OF_BOUNDS, MIN_M, MAX_M);

  // Read the pairs in S
  vector<pair<int, int>> S(m);
  for (int i=0; i<m; i++) {
    int a, b;
    test_condition(bool(finput >> a >> b), CANNOT_READ_AB, i+1);
    test_condition(1 <= a && a <= n, A_OUT_OF_BOUNDS, 1, n);
    test_condition(1 <= b && b <= n, B_OUT_OF_BOUNDS, 1, n);
    test_condition(a != b, AB_SAME);
    S[i] = {a-1, b-1};
  }

  // Check the consistency
  test_condition(satisfies(P, S), P_DOES_NOT_SATISFY_S);

  // Start interaction
  int query_count = 0;

  // Send n and P to program.

  flog << SENDING_N_AND_P << endl;
  flog << "n = " << n << endl;
  flog << "P =";
  for (int i=0; i<n; i++)
    flog << " " << P[i]+1;
  flog << endl;

  cout << n << endl;
  for (int i=0; i<n; i++) {
    if (i > 0)
      cout << " ";
    cout << P[i]+1;
  }
  cout << endl;

  flog << WAITING << endl;
  // Loop.
  while (true) {
    string cmd;
    test_condition(bool(cin >> cmd), WA_PREMATURE_TERMINATION);

    flog << COMMAND_RECEIVED_PRE << cmd << COMMAND_RECEIVED_POST << endl;

    if (cmd == END_COMMAND) {
      break ;
    }

    ++query_count;
    test_condition(query_count <= QUERY_LIMIT, WA_TOO_MANY_QUERIES);
    test_condition(cmd == QUERY_COMMAND, WA_UNKNOWN_COMMAND);

    vector<int> Q(n);
    for (int i=0; i<n; i++) {
      test_condition(bool(cin >> Q[i]), WA_CANNOT_READ_Q, query_count);
      Q[i]--;
    }

    // Check the permutation
    test_condition(is_permutation(Q), WA_Q_NOT_A_PERMUTATION, query_count);

    // Calculate the result
    int answer = satisfies(Q, S);

    flog << LOG_QUERY << query_count << ":";
    for (int i=0; i<n; i++)
      flog << " " << Q[i]+1;
    flog << LOG_ANSWER << answer << endl;

    // Send the answer
    cout << answer << endl;
  }

  // Read and check the output
  flog << WAITING_FOR_SOLUTION << endl;

  vector<int> A(n);
  for (int i=0; i<n; i++) {
    test_condition(bool(cin >> A[i]), WA_CANNOT_READ_A);
    A[i]--;
  }
  test_condition(is_permutation(A), WA_A_NOT_A_PERMUTATION);

  vector<int> B(n);
  for (int i=0; i<n; i++) {
    test_condition(bool(cin >> B[i]), WA_CANNOT_READ_B);
    B[i]--;
  }
  test_condition(is_permutation(B), WA_B_NOT_A_PERMUTATION);

  // Check the answers
  flog << CONTESTANT_LOWEST;
  for (int i=0; i<n; i++) flog <<" " << A[i]+1;
  flog << endl;

  flog << CONTESTANT_HIGHEST;
  for (int i=0; i<n; i++)
    flog << " " << B[i]+1;
  flog << endl;

  solver s(n, S);
  vector<int> myA = s.solve(true);
  vector<int> myB = s.solve(false);

  /*
  Ne zelimo im reci koje su najbolje permutacije.

  flog << "My calculated lowest permutation:";
  for (int i=0; i<n; i++)
    flog << " " << myA[i]+1;
  flog << endl;

  flog << "My calculated highest permutation:";
  for (int i=0; i<n; i++)
    flog << " " << myB[i]+1;
  flog << endl;
  */

  test_condition(A == myA && B == myB, WA_INCORRECT);

  foutput << "1" << endl;
  foutput << CORRECT << query_count << endl;

  flog << CORRECT << query_count << endl;
}

int main(int argc, char *argv[])
{
  assert(argc == 4);
  finput.open(argv[1]);
  flog.open(argv[2]);
  foutput.open(argv[3]);
  assert(!finput.fail() && !flog.fail() && !foutput.fail());
  main_problem_interaction();
  return 0;
}
