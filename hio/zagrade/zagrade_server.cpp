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

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<
 
#define fi first
#define sec second
#define mp make_pair
#define pb push_back

#ifdef ENGLISH

/******************************* ENGLISH ***************************************/

#define CANNOT_READ_N "Input file error: cannot read integer n."
#define N_OUT_OF_BOUNDS "Input file error: n has to be between %d and %d."
#define CANNOT_READ_S "Input file error: cannot read S."
#define WA_UNKNOWN_COMMAND "Netocno! Neispravna naredba!"
#define WA_INCORRECT "Netocno! Duljina puta nija tocna!"
#define PARTIAL_CORRECT "Tocno, ali previse upita za sve bodove!"
#define WA_CANNOT_READ_ANS "Netocno! Ne mogu procitati duljinu puta!"
#define WA_PREMATURE_TERMINATION "Netocno! Vas program je zavrsio prije nego je ispisao trazenu duljinu puta!"
#define WAITING "Cekam...."
#define WA_CANNOT_READ_POMAK "Netocno! Ne mogu procitati POMAK"
#define CORRECT "Tocno! Broj upita: "
#define WA_TOO_MANY_QUERIES "Netocno! Previse upita!"
#define WAITING_FOR_SOLUTION "Cekam rjesenje"
#define WA_INVALID_INTERVAL "Netocno, neispravan interval!"
#define WA_CANNOT_READ_INTERVAL "Ne mogu procitati interval."

#else

/******************************* CROATIAN ***************************************/

#define CANNOT_READ_N "Neispravna ulazna datoteka: ne mogu procitati broj n."
#define N_OUT_OF_BOUNDS "Neispravna ulazna datoteka: n mora biti izmedju %d i %d."
#define CANNOT_READ_S "Neispravna ulazna datoteka: ne mogu procitati Si."
#define WA_CANNOT_READ_INTERVAL "Ne mogu procitati interval."
#define WA_INVALID_INTERVAL "Netocno, neispravan interval!"
#define WA_UNKNOWN_COMMAND "Netocno, neispravna naredba!"
#define WA_INCORRECT "Netocno! Duljina puta nija tocna!"
#define WA_CANNOT_READ_ANS "Netocno! Ne mogu procitati duljinu puta!"
#define PARTIAL_CORRECT "Tocno, ali previse upita za sve bodove! Broj upita: "
#define WA_PREMATURE_TERMINATION "Netocno! Vas program je zavrsio prije nego je ispisao trazenu duljinu puta!"
#define WA_CANNOT_READ_POMAK "Netocno! Ne mogu procitati POMAK"
#define WAITING "Cekam...."
#define CORRECT "Tocno! Broj upita: "
#define WA_TOO_MANY_QUERIES "Netocno! Previse upita!"
#define WAITING_FOR_SOLUTION "Cekam rjesenje"

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

const int PARTIAL = 1000;

const int MAXN = 10000010;
const int offset = (1 << 20);
const int inf = (1 << 30);

struct tournament {
  int p[offset * 2];

  tournament() {
    REP(i, offset * 2) p[i] = inf;
  }

  void update(int a, int b) {
    a += offset;
    p[a] = b;
    a /= 2;
    while (a) {
      p[a] = min(p[a * 2], p[a * 2 + 1]);
      a /= 2;
    }
  }

  int get(int cvor, int l, int r, int a, int b) {
    if (l > b || r < a) return inf;
    if (l >= a && r <= b) return p[cvor];

    int mid = (l + r) / 2;

    int x = get(cvor * 2, l, mid, a, b);
    int y = get(cvor * 2 + 1, mid + 1, r, a, b);
    return min(x, y);
  }
};

tournament T;

int pref[MAXN];

void send_answer(int a, int b) {
  int ret = 0;
  if (pref[b] - pref[a - 1] == 0 && T.get(1, 0, offset - 1, a, b) >= pref[a - 1]) {
    ret = 1;
  }

  flog << "Query was (" << a << "," << b << "), answer is " << ret << endl;
  cout << ret << endl;
}



// - read the test case from finput,
// - read the contestant's output from cin
// - write to the contestant's input with cout
// - log with flog
// - score and explanation to foutput
void main_problem_interaction() {
  const string QUERY_COMMAND = "?";
  const string END_COMMAND = "!";


  int n; 
  test_condition(bool(finput >> n), CANNOT_READ_N);
    
  string s;
  test_condition(bool(finput >> s), CANNOT_READ_S);

  FOR(i, 1, n + 1) {
    pref[i] = pref[i - 1];
    if (s[i - 1] == '(') pref[i]++;
    else pref[i]--;
  }

  FOR(i, 1, n + 1) T.update(i, pref[i]);
  
  int QUERY_LIMIT = -1;
  if (n <= PARTIAL) {
    QUERY_LIMIT = n * n / 4;
  } else {
    QUERY_LIMIT = n - 1;
  }

  // Start interaction
  int query_count = 0;

  cout << n << endl;

  flog << WAITING << endl;
  // Loop.
  while (true) {
    string cmd;
    test_condition(bool(cin >> cmd), WA_PREMATURE_TERMINATION);

    if (cmd == END_COMMAND) {
      break ;
    }

    ++query_count;
    test_condition(query_count <= QUERY_LIMIT, WA_TOO_MANY_QUERIES);
    test_condition(cmd == QUERY_COMMAND, WA_UNKNOWN_COMMAND);

    int a, b;
    test_condition(bool(cin >> a >> b), WA_CANNOT_READ_INTERVAL, query_count);
    test_condition(1 <= a && a <= b && b <= n, WA_INVALID_INTERVAL);

    // Send the answer
    send_answer(a, b);
  }

  // Read and check the output
  flog << WAITING_FOR_SOLUTION << endl;

  string ans;

  test_condition(bool(cin >> ans), WA_CANNOT_READ_ANS);

  // Check the answers
  flog << "Contestant answer: " << ans << endl;

  test_condition(ans == s, WA_INCORRECT);

  foutput << "1" << endl;
  foutput << CORRECT << query_count << endl;
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
