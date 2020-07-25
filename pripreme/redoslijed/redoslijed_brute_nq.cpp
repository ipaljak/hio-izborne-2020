#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;

int N, M;
int final[MAXN];
bool covered[MAXN];
int lft[MAXN], rig[MAXN], clr[MAXN];
int bad[MAXN];

void load() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; i++) {
    scanf("%d%d%d", lft + i, rig + i, clr + i);
    lft[i]--;
  }
  for (int i = 0; i < N; i++) 
    scanf("%d", final + i);
}

void bye() {
  puts("NE");
  exit(0);
}

void set_zero(int pos) {
  if (!final[pos])
    return;
  for (int i = 0; i < M; i++)
    if (pos >= lft[i] && pos < rig[i] && clr[i] != final[pos]) 
      bad[i]--;
  final[pos] = 0;
}

void solve() {    
  for (int i = 0; i < M; i++)
    for (int j = lft[i]; j < rig[i]; j++) {
      if (final[j] && final[j] != clr[i])
        bad[i]++;
      covered[j] = true;
    }
    
  for (int i = 0; i < N; i++) 
    if (covered[i] ^ !!final[i])
      bye();
  
  vector <int> ans;
  for (int i = 0; i < M; i++) {
    int curr = -1;
    for (int j = 0; j < M; j++)
      if (!bad[j]) {
        curr = j;
        break;
      }
    if (curr == -1)
      bye();
    for (int j = lft[curr]; j < rig[curr]; j++)
      set_zero(j);
    ans.push_back(curr);
    bad[curr] = -1;
  }
  
  puts("DA");
  reverse(ans.begin(), ans.end());  
  for (auto it : ans)
    printf("%d ", it + 1);
  puts("");
}

int main() {
  double st = clock();
  load();
  solve();
  fprintf(stderr, "%lf\n", (clock() - st) / CLOCKS_PER_SEC);
  return 0;
}
