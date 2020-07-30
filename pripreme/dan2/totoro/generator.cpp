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
  return rand() % (b - a + 1) + a;
}

int m;
int n;

vector<vector<int> > random_permutiraj(vector<vector<int> > v) {
  vector<vector<int> > ret; 
  vector<int> perm;
  REP(i, n) perm.push_back(i);
  random_shuffle(perm.begin(), perm.end());
  REP(i, m) {
    ret.push_back(vector<int> (n));
    REP(j, n)
      // j -> v[j]
      // perm[j] -> perm[v[j]]
      ret[i][perm[j]] = perm[v[i][j]];
  }
  return ret;
}

void validiraj(vector<vector<int> > v) {
  assert((int) v.size() == m);
  REP(i, m) {
    assert((int) v[i].size() == n);
    sort(v[i].begin(), v[i].end());
    REP(j, n)
      assert(v[i][j] == j);
  }
}

void ispisi_primjere(vector<vector<int> > ispis) {
  printf("%d %d\n", m, n);
  ispis = random_permutiraj(ispis);
  validiraj(ispis);
  REP(i, m) {
    REP(j, n) {
      printf("%d", ispis[i][j] + 1); 
      if(j < n - 1) printf(" ");
    }
    printf("\n");
  }
}

vector<int> napravi_cikluse(vector<int> velicine) {
  vector<int> ret(n);
  int pocetak = 0;
  REP(i, (int) velicine.size()) {
    vector<int> perm;
    REP(j, velicine[i]) perm.push_back(j);
    random_shuffle(perm.begin(), perm.end());
    REP(j, velicine[i] - 1)
      ret[pocetak + perm[j]] = pocetak + perm[j + 1];
    ret[pocetak + perm[velicine[i] - 1]] = pocetak + perm[0];
    pocetak += velicine[i];
  }
  REP(i, n) ret[i];
  return ret;
}

vector<int> generiraj_velicine() {
  int sum = 0;
  vector<int> niz; 
  int zeljena_velicina = n / m;
  if(n <= 10) zeljena_velicina = n; 
  else if(rnd(1, 5) == 1) 
    zeljena_velicina = min(30, n); 
  while(sum < n) {
    int gornja = max(1, min(zeljena_velicina, n - sum));
    int donja = max(1, gornja / 2);
    int x = rnd(donja, gornja);
    niz.push_back(x);
    sum += x; 
  }
  return niz;
}

void najbolji_generator() {
  vector<int> velicine = generiraj_velicine();
  vector<vector<int> > v;
  REP(i, m) {
    vector<int> niz = napravi_cikluse(velicine); 
    v.push_back(niz);
  }
  int pocetak = 0;
  REP(i, (int) velicine.size()) {
    int kraj = pocetak + velicine[i];
    if(rnd(1, 2) == 1) {
      FOR(j, 1, m) {
        FOR(k, pocetak, kraj)
          v[j][k] = v[0][k];
      }
    }
    pocetak = kraj;
  }
  ispisi_primjere(v);
}

void skromni_generator() {
  vector<int> velicine = generiraj_velicine();
  vector<vector<int> > v;
  REP(i, m) {
    vector<int> niz = napravi_cikluse(velicine); 
    v.push_back(niz);
  }
  int pocetak = 0;
  REP(i, (int) velicine.size()) {
    int kraj = pocetak + velicine[i];
    int r = rnd(1, 3);
    if(r == 1) {
      FOR(j, 1, m) {
        FOR(k, pocetak, kraj)
          v[j][k] = v[0][k];
      }
    }
    else if(r == 2) {
      FOR(j, 1, m) {
        FOR(k, pocetak, kraj)
          v[j][k] = v[0][kraj - 1 - k + pocetak];
      }
    }
    pocetak = kraj;
  }
  ispisi_primjere(v);
}

vector<vector<int>> M24 = {
  {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24},
  {1,2,17,13,4,6,9,18,3,7,12,23,14,19,20,15,10,11,5,22,16,21,8,24},
  {24,23,12,16,18,10,20,14,21,6,17,3,22,8,19,4,11,5,15,7,9,13,2,1},
  {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,1}
};

void mathieu_generator() {
  assert(n == 2164);
  assert(m == 4);
  vector<int> velicine = {24, 24, 2, 200, 13*125, 17*17};
  vector<vector<int> > v;
  REP(i, m) {
    vector<int> niz = napravi_cikluse(velicine); 
    v.push_back(niz);
  }


  int pocetak = 0;
  REP(i, (int) velicine.size()) {
    int kraj = pocetak + velicine[i];
    if (i == 0 || i == 1) {
      REP(j, m)
        REP(k, 24)
          v[j][k] = M24[j][k] - 1;
    }
    else if(i != 3) {
      FOR(j, 1, m) {
        FOR(k, pocetak, kraj)
          v[j][k] = v[0][k];
      }
    }
    pocetak = kraj;
  }
  ispisi_primjere(v);
}

void permutacija_s_jednim_ciklusom() {
  vector<int> perm;
  REP(i, n) perm.push_back(i);
  random_shuffle(perm.begin(), perm.end());
  vector<int> v(n);
  REP(i, n - 1) v[perm[i]] = perm[i + 1];
  v[perm[n - 1]] = perm[0];
  vector<vector<int> > ret;
  ret.push_back(v);
  ispisi_primjere(ret);
}

int main(int argc, char **argv) { 
  srand(time(0) * getpid());
  assert(argc == 2);
  if(!strcmp(argv[1], "prvi")) {
    m = rnd(5, 10);
    n = rnd(7, 9);
    najbolji_generator();
  }
  else if(!strcmp(argv[1], "drugi")) {
    m = 1;
    n = rnd(2400, 2500);
    permutacija_s_jednim_ciklusom();
  }
  else if(!strcmp(argv[1], "treci")) {
    m = 1;
    n = rnd(2400, 2500);
    najbolji_generator();
  }
  else if(!strcmp(argv[1], "cetvrti")) {
    m = rnd(1, 10);
    n = rnd(2400, 2500);
    najbolji_generator();
  }
  else if (!strcmp(argv[1], "s_mathieu")) {
    m = 4;
    n = 24 + 24 + 2 + 200 + 13*125 + 17*17;
    mathieu_generator();
  }
  else if (!strcmp(argv[1], "skromni")) {
    m = 7;
    n = 2400;
    skromni_generator();
  }
  else if (!strcmp(argv[1], "mali_skromni")) {
    m = 5;
    n = 8;
    skromni_generator();
  }
  else
    assert(false);
  return 0;
}

