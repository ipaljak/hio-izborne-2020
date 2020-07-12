#include <iostream>

using namespace std;

typedef long long ll;
#define x first
#define y second
#define mp make_pair

const int msk[11] = {10, 2, 9, 7, 18, 21, 12, 3, 29, 23};
const ll mod = (ll)1e9 + 7;
const int MAXN = 100;
const int seg_sz = 5;
ll n, k, X, sol[MAXN + 5];
int br, broj, gran;
bool dobar[(1 << (2 * seg_sz)) + 5];

void rek(int x, int mask){
	if(x % k == 0 && !dobar[mask])
		return;
	if(x == n){
		sol[mask]++;
		return;
	}
	for(int i = 0 ; i < broj ; ++i){
		rek(x + 1, mask ^ (1 << i));
	}
}

void prep_stuff(){
	for(int i = 0 ; i < gran ; ++i){
		int sad = msk[i % 10];
		if(br == 2){
			sad += (msk[i / 10] << seg_sz);
		}
		dobar[sad] = 1;
	}
}

int main(){
ios_base::sync_with_stdio(false);
cin.tie(0);
cout.tie(0);
cin >> br >> n >> k >> X;
broj = br * seg_sz;
gran = (br == 1 ? 10 : 100);
prep_stuff();
int poc = msk[X % 10];
if(br == 2){
	poc += (msk[X / 10] << seg_sz);
}
rek(0, poc);
for(int i = 0 ; i < gran ; ++i){
	int sad = msk[i % 10];
	if(br == 2){
		sad += (msk[i / 10] << seg_sz);
	}
	cout << sol[sad] << endl;
}

return 0;
}

