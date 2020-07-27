#include <bits/stdc++.h>
#include "process.h"
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAX = 5e5;

int get(int lo, int hi) {
  return uniform_int_distribution <int> (lo, hi)(rng);
}

int N, M, L;
vector <Operation> input;
vector <int> order;
vector <int> ans;

void purely_random() {
  for (auto &it : input) {
    it.lft = get(1, N);
    it.rig = get(it.lft, N);
    it.clr = get(1, L);
  }
}

void distinct_colours() {
  vector <int> colours(M);
  for (int i = 0; i < M; i++)
    colours[i] = i;
  shuffle(colours.begin(), colours.end(), rng);
  for (int i = 0; i < M; i++) {
    input[i].lft = get(1, N);
    input[i].rig = get(input[i].lft, N);
    input[i].clr = colours[i];
  }
}

void mixed_lengths() {
  int small = sqrt(N);
  int period = sqrt(M);
  for (int i = 0; i < M; i++) {
    if (!(i % period)) {
      input[i].lft = get(1, N);
      input[i].rig = get(input[i].lft, N);    
    }
    else {
      input[i].lft = get(1, N - small + 1);
      input[i].rig = input[i].lft + small - 1;
    }
    input[i].clr = get(1, L);
  }
}

void process() {
  order.resize(M);
  for (int i = 0; i < M; i++)
    order[i] = i + 1;
  ans = process_operations(N, input, order);
  shuffle(order.begin(), order.end(), rng);
}

void output() {
  printf("%d %d\n", N, M); 
  for (auto it : order)
    input[it - 1].output();
  for (auto it : ans)
    printf("%d ", it);
  puts("");
}

int main(int argc, char *argv[]) {
  N = atoi(argv[1]);
  M = atoi(argv[2]);
  L = atoi(argv[3]);
  string type = argv[4];
  
  assert(N <= MAX && M <= MAX && L <= MAX);
  
  input.resize(M);
  
  if (type == "random")
    purely_random();
  else if (type == "distinct")
    distinct_colours();
  else if (type == "mixed")
    mixed_lengths();
  else
    assert(false);
     
  process();
  output();
  
  return 0;
}
