#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
#define x first
#define y second
#define mp make_pair

const int msk_val[11] = {10, 2, 9, 7, 18, 21, 12, 3, 29, 23};
const int seg_sz = 5;
const int MAXN = (1 << (2 * seg_sz));
ll n, k, X, br, c[MAXN + 5][MAXN + 5], res[MAXN + 5][MAXN + 5], h[MAXN + 5][MAXN + 5], g[MAXN + 5][MAXN + 5];
const ll mod = (ll)1e9 + 7;

void pomnozi(ll (&a)[MAXN + 5][MAXN + 5], ll (&b)[MAXN + 5][MAXN + 5], int dim){
	memset(c, 0, sizeof(c));
	for(int i = 0 ; i < dim ; ++i){
		for(int j = 0 ; j < dim ; ++j){
			for(int v = 0 ; v < dim ; ++v){
				c[i][j] = (c[i][j] + (a[i][v] * b[v][j]) % mod) % mod;
			}
		}
	}
	for(int i = 0 ; i < dim ; ++i){
		for(int j = 0 ; j < dim ; ++j){
			a[i][j] = c[i][j];
		}
	}
}

void potenciraj(ll (&a)[MAXN + 5][MAXN + 5], ll pot, int dim){
	memset(res, 0, sizeof(res));
	for(int i = 0 ; i < dim ; ++i){
		res[i][i] = 1;
	}
	while(pot){
		if(pot & 1){
			pomnozi(res, a, dim);
		}
		pomnozi(a, a, dim);
		pot >>= 1;
	}
	for(int i = 0 ; i < dim ; ++i){
		for(int j = 0 ; j < dim ; ++j){
			a[i][j] = res[i][j];
		}
	}
}

int main(){
cin >> br >> n >> k >> X;
int gran = (br == 1 ? 10 : 100);
int broj = br * seg_sz;
for(int i = 0 ; i < (1 << broj) ; ++i){
	for(int j = 0 ; j < broj ; ++j){
		int novi = i ^ (1 << j);
		h[i][novi]++;
	}
}
potenciraj(h, k, (1 << broj));
memset(c, 0, sizeof(c));
for(int i = 0 ; i < gran ; ++i){
	int prvi = msk_val[i % 10];
	if(br == 2){
		prvi += (msk_val[i / 10] << seg_sz);
	}
	for(int j = 0 ; j < gran ; ++j){
		int drugi = msk_val[j % 10];
		if(br == 2){
			drugi += (msk_val[j / 10] << seg_sz);
		}
		c[i][j] = h[prvi][drugi];
	}
}
for(int i = 0 ; i < gran ; ++i){
	for(int j = 0 ; j < gran ; ++j){
		h[i][j] = c[i][j];
	}
}
potenciraj(h, n / k, gran);
int ostalo = n % k;
for(int i = 0 ; i < gran ; ++i){
	for(int j = 0 ; j < gran ; ++j){
		g[i][j] = h[i][j];
	}
}
memset(h, 0, sizeof(h));
for(int i = 0 ; i < (1 << broj) ; ++i){
	for(int j = 0 ; j < broj ; ++j){
		int novi = i ^ (1 << j);
		h[i][novi]++;
	}
}
potenciraj(h, ostalo, (1 << broj));
for(int i = 0 ; i < gran ; ++i){
	int prvi = msk_val[i % 10];
	if(br == 2){
		prvi += (msk_val[i / 10] << seg_sz);
	}
	ll sol = 0;
	for(int j = 0 ; j < gran ; ++j){
		int drugi = msk_val[j % 10];
		if(br == 2){
			drugi += (msk_val[j / 10] << seg_sz);
		}
		sol = (sol + (g[X][j] * h[drugi][prvi]) % mod) % mod;
	}
	cout << sol << endl;
}

return 0;
}
