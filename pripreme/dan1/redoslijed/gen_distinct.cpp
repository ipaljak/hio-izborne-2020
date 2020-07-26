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
   
  int curr_color = 1;
  vector <Operation> input(M);
  for (auto &it : input) {
    it.lft = get(1, N);
    it.rig = get(it.lft, N);
    it.clr = curr_color++;
  }
  
  vector <int> order(M);
  for (int i = 0; i < M; i++)
    order[i] = i + 1;
    
  vector <int> ans = process_operations(N, input, order);

  shuffle(order.begin(), order.end(), rng);
  
  printf("%d %d\n", N, M); 
  for (auto it : order)
    input[it - 1].output();
  for (auto it : ans)
    printf("%d ", it);
  puts("");
  
  return 0;
}
