#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
#define x first
#define y second
#define mp make_pair

const int msk[11] = {10, 2, 9, 7, 18, 21, 12, 3, 29, 23};
const ll mod = (ll)1e9 + 7;
const int MAXN = 100;
const int max_k = 1500;
const int seg_sz = 5;
ll n, k, X, val[MAXN + 5][MAXN + 5], dp[max_k + 5][(1 << (2 * seg_sz + 1)) + 5], c[MAXN + 5][MAXN + 5], d[MAXN + 5][MAXN + 5];
int br, broj, gran;

void pomnozi(ll (&a)[MAXN + 5][MAXN + 5], ll (&b)[MAXN + 5][MAXN + 5]){
	memset(c, 0, sizeof(c));
	for(int i = 0 ; i < gran ; ++i){
		for(int j = 0 ; j < gran ; ++j){
			for(int v = 0 ; v < gran ; ++v){
				c[i][j] = (c[i][j] + (a[i][v] * b[v][j]) % mod) % mod;
			}
		}
	}
	for(int i = 0 ; i < gran ; ++i){
		for(int j = 0 ; j < gran ; ++j){
			a[i][j] = c[i][j];
		}
	}
}

void potenciraj(ll (&a)[MAXN + 5][MAXN + 5], ll y){
	memset(d, 0, sizeof(d));
	for(int i = 0 ; i < gran ; ++i){
		d[i][i] = 1;
	}
	while(y > 0){
		if(y & 1){
			pomnozi(d, a);
		}
		pomnozi(a, a);
		y >>= 1;
	}
	for(int i = 0 ; i < gran ; ++i){
		for(int j = 0 ; j < gran ; ++j){
			a[i][j] = d[i][j];
		}
	}
}

int main(){
ios_base::sync_with_stdio(false);
cin.tie(0);
cout.tie(0);
cin >> br >> n >> k >> X;
broj = br * seg_sz;
gran = (br == 1 ? 10 : 100);
for(int st = 0 ; st < gran ; ++st){
	memset(dp, 0, sizeof(dp));
	int sad = msk[st % 10];
	if(br == 2){
		sad += (msk[st / 10] << seg_sz);
	}
	dp[0][sad] = 1;
	for(int i = 1 ; i <= k ; ++i){
		for(int j = 0 ; j < (1 << broj) ; ++j){
			for(int v = 0 ; v < broj ; ++v){
				int novi = (j ^ (1 << v));
				dp[i][novi] = (dp[i][novi] + dp[i - 1][j]) % mod;
			}
		}
	}
	for(int kraj = 0 ; kraj < gran ; ++kraj){
		sad = msk[kraj % 10];
		if(br == 2){
			sad += (msk[kraj / 10] << seg_sz);
		}
		val[st][kraj] = dp[k][sad];
	}
}
potenciraj(val, n / k);
memset(dp, 0, sizeof(dp));
for(int kraj = 0 ; kraj < gran ; ++kraj){
	int sad = msk[kraj % 10];
	if(br == 2){
		sad += (msk[kraj / 10] << seg_sz);
	}
	dp[0][sad] = val[X][kraj];
}
for(ll i = 1 ; i <= n % k ; ++i){
	for(int j = 0 ; j < (1 << broj) ; ++j){
		for(int v = 0 ; v < broj ; ++v){
			int novi = (j ^ (1 << v));
			dp[i][novi] = (dp[i][novi] + dp[i - 1][j]) % mod;
		}
	}
}
for(int kraj = 0 ; kraj < gran ; ++kraj){
	int sad = msk[kraj % 10];
	if(br == 2){
		sad += (msk[kraj / 10] << seg_sz);
	}
	cout << dp[n % k][sad] << endl;
}

return 0;
}
