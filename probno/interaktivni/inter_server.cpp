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

typedef pair <int, int> pii;

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
#define CANNOT_READ_M "Input file error: cannot read integer m."
#define N_OUT_OF_BOUNDS "Input file error: n has to be between %d and %d."
#define CANNOT_READ_Si "Input file error: cannot read Si."
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

#else

/******************************* CROATIAN ***************************************/

#define CANNOT_READ_N "Neispravna ulazna datoteka: ne mogu procitati broj n."
#define CANNOT_READ_M "Neispravna ulazna datoteka: ne mogu procitati broj m."
#define N_OUT_OF_BOUNDS "Neispravna ulazna datoteka: n mora biti izmedju %d i %d."
#define CANNOT_READ_Si "Neispravna ulazna datoteka: ne mogu procitati Si."
#define WA_UNKNOWN_COMMAND "Netocno, neispravna naredba!"
#define WA_INCORRECT "Netocno! Duljina puta nija tocna!"
#define WA_CANNOT_READ_ANS "Netocno! Ne mogu procitati duljinu puta!"
#define PARTIAL_CORRECT "Tocno, ali previse upita za sve bodove!"
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

void send_position(pii pos, vector <string> &s) {
  flog << "Saljem oko " << pos.fi << ' ' << pos.sec << endl;
  for (int i = pos.fi - 1; i < pos.fi + 2; i++) {
    for (int j = pos.sec - 1; j < pos.sec + 2; j++) {
      cout << s[i][j];
    }
    cout << endl;
  }
}

const int smjerx[] = {0, 0, 1, -1};
const int smjery[] = {1, -1, 0, 0};

int solve(vector <string> &s) {
  int n = s.size();
  int m = s[0].size();
  queue <int> q;
  vector <vector <bool> > bio;
  bio.resize(n);
  REP(i, n) bio[i].resize(m);
  REP(i, n) {
    REP(j, m) {
      if (s[i][j] == 'X') {
        q.push(i); q.push(j);
        q.push(0);
        bio[i][j] = 0;
      }
    }
  }
  int x, y, d;
  while (!q.empty()) {
    x = q.front(); q.pop();
    y = q.front(); q.pop();
    d = q.front(); q.pop();
    if (s[x][y] == 'Y') return d;

    REP(i, 4) {
      int nx = x + smjerx[i];
      int ny = y + smjery[i];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
      if (bio[nx][ny] || s[nx][ny] == '#') continue;
      bio[nx][ny] = 1;
      q.push(nx);
      q.push(ny);
      q.push(d + 1);
    }
  }
  assert(0);
  return -1;
}


// - read the test case from finput,
// - read the contestant's output from cin
// - write to the contestant's input with cout
// - log with flog
// - score and explanation to foutput
void main_problem_interaction() {
  const string QUERY_COMMAND = "POMAK";
  const string END_COMMAND = "!";


  int n; //
  int m; // 

  test_condition(bool(finput >> n), CANNOT_READ_N);
  test_condition(bool(finput >> m), CANNOT_READ_M);

  vector <string> s;
  s.resize(n);

  for (int i = 0; i < n; i++) {
    test_condition(bool(finput >> s[i]), CANNOT_READ_Si);
  }

  int tocke = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      tocke += (s[i][j] != '#');
    }
  }

  pii pos;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == 'X') pos = {i, j};
    }
  }

  const int QUERY_LIMIT = tocke * tocke;
  const int QUERY_AC = tocke * 2;

  // Start interaction
  int query_count = 0;

  send_position(pos, s);

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

    string c;
    test_condition(bool(cin >> c), WA_CANNOT_READ_POMAK, query_count);

    // Move to next position

    if (c == "U") pos.first--;
    if (c == "D") pos.first++;
    if (c == "L") pos.second--;
    if (c == "R") pos.second++;

    // Send the answer
    send_position(pos, s);
  }

  // Read and check the output
  flog << WAITING_FOR_SOLUTION << endl;

  int ans;

  test_condition(bool(cin >> ans), WA_CANNOT_READ_ANS);

  // Check the answers
  flog << ans << endl;

  int sol = solve(s);

  test_condition(ans == sol, WA_INCORRECT);

  if (query_count > QUERY_AC) {
    foutput << "0.5" << endl;
    foutput << PARTIAL_CORRECT << endl;
  } else {
    foutput << "1" << endl;
    foutput << CORRECT << query_count << endl;
  }
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
