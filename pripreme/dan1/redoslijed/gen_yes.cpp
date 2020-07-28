#include <bits/stdc++.h>
#include "process.h"
using namespace std;

mt19937 rng;

const int MAX = 5e5;

int N, M, L;
vector <int> colours;
vector <Operation> input;
vector <int> order;
vector <int> ans;
bool distinct;
string type;

int get_uniform(int lo, int hi) {
  return uniform_int_distribution <int> (lo, hi)(rng);
}

int get_poisson(int param) {
  return max(min(poisson_distribution <int> (param)(rng), N), 1);
}

void gen_colours() {
  for (int i = 0; i < M; i++)
    colours.push_back(i + 1);
  shuffle(colours.begin(), colours.end(), rng);
  for (int i = 0; i < M; i++)
    input[i].clr = distinct ? colours[i] : get_uniform(1, L);
}

void purely_random() {
  for (int i = 0; i < M; i++) {
    input[i].lft = get_uniform(1, N);
    input[i].rig = get_uniform(input[i].lft, N);
  }
}

void mixed_lengths() {
  int small = ceil(log2(N));
  int large = (N - 1) / small + 1;
  for (int i = 0; i < M; i++) {
    int len = get_poisson(i < M / 5 ? large : small); 
    input[i].lft = get_uniform(1, N - len + 1);
    input[i].rig = input[i].lft + len - 1;
  } 
}

void decaying_lengths() {
  auto f = [](int x) -> double {
    return (double)x * x * x;
  };
  double coef = N / (10 * f(M));
  for (int i = 0; i < M; i++) {
    int curr = ceil(coef * f(M - i));
    int len = get_uniform(curr, min(10 * curr, N));
    input[i].lft = get_uniform(1, N - len + 1);
    input[i].rig = input[i].lft + len - 1;
  }
}

void generate() {
  input.resize(M);
  gen_colours();
  if (type == "random")
    purely_random();
  else if (type == "mixed")
    mixed_lengths();
  else if (type == "decay")
    decaying_lengths();
  else 
    assert(false);
}

void process() {
  order.resize(M);
  for (int i = 0; i < M; i++)
    order[i] = i + 1;
  ans = process_operations(N, input, order);
}

void output() {
  printf("%d %d\n", N, M); 
  shuffle(order.begin(), order.end(), rng);
  for (auto it : order)
    input[it - 1].output();
  for (auto it : ans)
    printf("%d ", it);
  puts("");
}

int main(int argc, char *argv[]) {
  int num = atoi(argv[1]);
  N = atoi(argv[2]);
  M = atoi(argv[3]);
  L = atoi(argv[4]);
  type = argv[5];
  distinct = atoi(argv[6]);
  
  assert(N <= MAX && M <= MAX && L <= MAX);
  
  rng.seed(num == -1 ? chrono::steady_clock::now().time_since_epoch().count() : num);
  
  generate();   
  process();
  output();
  
  return 0;
}
