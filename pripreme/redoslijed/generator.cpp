#include <bits/stdc++.h>
#include "process.h"
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAX = 5e5;

int get(int lo, int hi) {
  return uniform_int_distribution <int> (lo, hi)(rng);
}

int main(int argc, char *argv[]) {
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);
  int limit = atoi(argv[3]);
  assert(N <= MAX && M <= MAX && limit <= MAX);
  
  printf("%d %d\n", N, M);  
  vector <Operation> input(M);
  for (auto &it : input) {
    it.lft = get(1, N);
    it.rig = get(it.lft, N);
    it.clr = get(1, limit);
    it.output();
  }
  
  vector <int> order(M);
  for (int i = 0; i < M; i++)
    order[i] = i + 1;
  
  shuffle(order.begin(), order.end(), rng);
  
  vector <int> ans = process_operations(N, input, order);
  for (auto it : ans)
    printf("%d ", it);
  puts("");
  
  return 0;
}
