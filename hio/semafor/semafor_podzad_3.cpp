#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
#define x first
#define y second
#define mp make_pair

const int msk[11] = {10, 2, 9, 7, 18, 21, 12, 3, 29, 23};
const ll mod = (ll)1e9 + 7;
const int MAXN = 1500;
const int max_k = 1500;
const int seg_sz = 5;
ll n, k, X, dp[2][(1 << (2 * seg_sz + 1)) + 5], c[MAXN + 5][MAXN + 5], b[(1 << (2 * seg_sz + 1)) + 5];
int br, broj;

int main(){
ios_base::sync_with_stdio(false);
cin.tie(0);
cout.tie(0);
cin >> br >> n >> k >> X;
broj = br * seg_sz;
int gran = (br == 1 ? 10 : 100);
int sad = msk[X % 10];
if(br == 2){
	sad += (msk[X / 10] << seg_sz);
}
dp[0][sad] = 1;
for(int i = 1 ; i <= n ; ++i){
	memset(dp[i & 1], 0, sizeof(dp[i & 1]));
	for(int j = 0 ; j < (1 << broj) ; ++j){
		for(int v = 0 ; v < broj ; ++v){
			int novi = (j ^ (1 << v));
			dp[i & 1][novi] = (dp[i & 1][novi] + dp[(i & 1) ^ 1][j]) % mod;
		}
	}
	if(i % k == 0){
		memset(b, 0, sizeof(b));
		for(int kraj = 0 ; kraj < gran ; ++kraj){
			sad = msk[kraj % 10];
			if(br == 2){
				sad += (msk[kraj / 10] << seg_sz);
			}
			b[sad] = dp[i & 1][sad];
		}
		memset(dp[i & 1], 0, sizeof(dp[i & 1]));
		for(int kraj = 0 ; kraj < gran ; ++kraj){
			sad = msk[kraj % 10];
			if(br == 2){
				sad += (msk[kraj / 10] << seg_sz);
			}
			dp[i & 1][sad] = b[sad];
		}
	}
}
for(int kraj = 0 ; kraj < gran ; ++kraj){
	sad = msk[kraj % 10];
	if(br == 2){
		sad += (msk[kraj / 10] << seg_sz);
	}
	cout << dp[n & 1][sad] << endl;
}

return 0;
}
