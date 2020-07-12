#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 1e3 + 10;

int rnd(int a, int b) {
  return a + (rand() % (b - a + 1));
}

int main(int argc, char **argv) {
  srand(time(0) * getpid());
  char tip[MAXN];
  assert(argc == 2);
  sscanf(argv[1], "%s", tip);
  if(!strcmp(tip, "prvi")) {
    printf("%d\n", rnd(1, 15));
  }
  else if(!strcmp(tip, "drugi")) {
    printf("%d\n", rnd(51, 1000));
  }
  else if(!strcmp(tip, "treci")) {
    printf("%d\n", rnd(1001, 1e6));
  }
  else if(!strcmp(tip, "cetvrti")) {
    int z = rnd(1e6 - 50, 1e6);
    printf("%d", rnd(1, 9));
    REP(i, z - 1)
      printf("%d", rnd(0, 9));
    printf("\n");
  }
  else 
    assert(false);
  return 0;
}

