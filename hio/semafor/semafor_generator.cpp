#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>

using namespace std;

typedef long long ll;
#define x first
#define y second
#define mp make_pair

struct testni{
	int br;
	ll n, k, X;
};

const int rnd_base = 100003;
const ll MAXN = (ll)1e15;

bool provjeri_testni(testni x, int idx){
	ll gran_n = MAXN;
	if(idx == 1){
		gran_n = 12;
	}
	if(idx == 3){
		gran_n = 1500;
	}
	ll gran_k = (idx == 4 ? min(x.n, 15LL) : x.n);
	int br = (idx <= 2 ? 1 : 2);
	int gran = (br == 1 ? 10 : 100);
	if(idx == 3 && x.k != x.n)
		return 0;
	//cout << x.br << ' ' << x.n << ' ' << x.k << ' ' << x.X << endl;
	if(x.br != br)
		return 0;
	if(x.n < 1 || x.n > gran_n)
		return 0;
	if(x.k < 1 || x.k > gran_k)
		return 0;
	if(x.X < 0 || x.X >= gran)
		return 0;
	return 1;
}

void napisi_u_file(testni x, int sad, char c){
	string ime = "semafor.";
	if(sad == -1){
		ime += "dummy.";
	}
	ime += "in.";
	if(sad != -1){
		ime.push_back(sad + '0');
	}
	ime.push_back(c);
	ofstream kout;
	kout.open(ime);
	kout << x.br << ' ' << x.n << ' ' << x.k << ' ' << x.X << endl;
	kout.close();
}

void gen_dummys(){
	testni prvi, drugi, treci;
	prvi = (testni){1, 2, 1, 5};
	drugi = (testni){1, 3, 3, 8};
	treci = (testni){1, 4, 2, 4};
	if(!provjeri_testni(prvi, 1)){
		cout << "Dummy testni primjer nije ispravan!" << endl;
		exit(0);
	}
	if(!provjeri_testni(drugi, 1)){
		cout << "Dummy testni primjer nije ispravan!" << endl;
		exit(0);
	}
	if(!provjeri_testni(treci, 1)){
		cout << "Dummy testni primjer nije ispravan!" << endl;
		exit(0);
	}
	napisi_u_file(prvi, -1, '1');
	napisi_u_file(drugi, -1, '2');
	napisi_u_file(treci, -1, '3');
}

void gen_subtask_1(){//br = 1, 1 <= k <= n <= 12
	char sad = 'a';
	for(int i = 1 ; i <= 12 ; i += min(2 * i, 3)){
		int br = 1;
		int gran = (br == 1 ? 10 : 100);
		ll n = i;
		ll k = rand() % n + 1;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 1)){
			cout << "Greska pri izradi testnih primjera za subtask 1!" << endl;
			exit(1);
		}
		napisi_u_file(t, 1, sad);
		sad++;
	}
}

ll veliki_rand(){
	ll ret = ((ll)rand() << 46);
	ret += ((ll)rand() << 30);
	ret += ((ll)rand() << 14);
	ret += ((ll)rand() >> 2);
	return ret;
}

void gen_subtask_2(){//br = 1, 1 <= k <= n <= 10^15
	char c = 'a';
	int br = 1;
	int gran = (br == 1 ? 10 : 100);
	ll val = (ll)1e4;
	ll sad = val;
	for(int i = 0 ; i < 3 ; ++i){//n = 10^4, 10^8, 10^12, k random X random
		ll n = sad;
		ll k = veliki_rand() % n + 1;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 2)){
			cout << "Greska pri izradi testnih primjera za subtask 2!" << endl;
			exit(2);
		}
		napisi_u_file(t, 2, c);
		sad *= val;
		c++;
	}
	val = (ll)1e14;
	ll dif = (ll)9e14;
	for(int i = 0 ; i < 4 ; ++i){// 10^14 <= n < 10^15, k random
		ll n = val + veliki_rand() % dif;
		ll k = veliki_rand() % n + 1;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 2)){
			cout << "Greska pri izradi testnih primjera za subtask 2!" << endl;
			exit(2);
		}
		napisi_u_file(t, 2, c);
		c++;
	}
	ll n = MAXN;//n = 10^15, k = 1
	ll k = 1;
	ll X = rand() % gran;
	testni t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 2)){
		cout << "Greska pri izradi testnih primjera za subtask 2!" << endl;
		exit(2);
	}
	napisi_u_file(t, 2, c);
	c++;
	n = MAXN;//n = 10^15, k rand <= 15
	k = rand() % 15 + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 2)){
		cout << "Greska pri izradi testnih primjera za subtask 2!" << endl;
		exit(2);
	}
	napisi_u_file(t, 2, c);
	c++;
	n = MAXN;//n = 10^15, k rand
	k = veliki_rand() % n + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 2)){
		cout << "Greska pri izradi testnih primjera za subtask 2!" << endl;
		exit(2);
	}
	napisi_u_file(t, 2, c);
	c++;
	n = MAXN;//n = 10^15, k = rand >= 10^15 - 15
	k = MAXN - rand() % 16;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 2)){
		cout << "Greska pri izradi testnih primjera za subtask 2!" << endl;
		exit(2);
	}
	napisi_u_file(t, 2, c);
	c++;
	n = MAXN;//n = 10^15, k = 10^15
	k = MAXN;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 2)){
		cout << "Greska pri izradi testnih primjera za subtask 2!" << endl;
		exit(2);
	}
	napisi_u_file(t, 2, c);
	c++;
}

void gen_subtask_3(){//br = 2, n = 1500, k = n
	char c = 'a';
	int br = 2;
	int gran = (br == 1 ? 10 : 100);
	for(int i = 10 ; i <= 1000 ; i *= 10){//n = 10, 100, 1000, k = n
		ll n = i;
		ll k = n;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 3)){
			cout << "Greska pri izradi testnih primjera za subtask 3!" << endl;
			exit(3);
		}
		napisi_u_file(t, 3, c);
		c++;
	}
	for(int i = 0 ; i < 3 ; ++i){// 1000 <= n rand <= 1500, k = n
		ll n = 1000 + rand() % 501;
		ll k = n;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 3)){
			cout << "Greska pri izradi testnih primjera za subtask 3!" << endl;
			exit(3);
		}
		napisi_u_file(t, 3, c);
		c++;
	}
	ll n = 1500;//n = 1500, k = n
	ll k = n;
	ll X = rand() % gran;
	testni t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 3)){
		cout << "Greska pri izradi testnih primjera za subtask 3!" << endl;
		exit(3);
	}
	napisi_u_file(t, 3, c);
	c++;
	n = 1500;//n = 1500, k = n
	k = n;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 3)){
		cout << "Greska pri izradi testnih primjera za subtask 3!" << endl;
		exit(3);
	}
	napisi_u_file(t, 3, c);
	c++;
	n = rand() % 1500 + 1;//n rand <= 1500, k = n, X rand < 10
	k = n;
	X = rand() % 10;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 3)){
		cout << "Greska pri izradi testnih primjera za subtask 3!" << endl;
		exit(3);
	}
	napisi_u_file(t, 3, c);
	c++;
}

void gen_subtask_4(){//br = 2, 1 <= n <= 10^15, k <= 15
	char c = 'a';
	int br = 2;
	int gran = (br == 1 ? 10 : 100);
	ll val = (ll)1e4;
	ll sad = val;
	for(int i = 0 ; i < 3 ; ++i){//n = 10^4, 10^8, 10^12, k random <= 15
		ll n = sad;
		ll k = veliki_rand() % min(15LL, n) + 1;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 4)){
			cout << "Greska pri izradi testnih primjera za subtask 4!" << endl;
			exit(4);
		}
		napisi_u_file(t, 4, c);
		sad *= val;
		c++;
	}
	val = (ll)1e14;
	ll dif = (ll)9e14;
	for(int i = 0 ; i < 4 ; ++i){// 10^14 <= n < 10^15, k random <= 15
		ll n = val + veliki_rand() % dif;
		ll k = veliki_rand() % min(n, 15LL) + 1;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 4)){
			cout << "Greska pri izradi testnih primjera za subtask 4!" << endl;
			exit(4);
		}
		napisi_u_file(t, 4, c);
		c++;
	}
	ll n = MAXN;//n = 10^15, k = 1
	ll k = 1;
	ll X = rand() % gran;
	testni t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 4)){
		cout << "Greska pri izradi testnih primjera za subtask 4!" << endl;
		exit(4);
	}
	napisi_u_file(t, 4, c);
	c++;
	n = MAXN;//n = 10^15, k rand <= 15
	k = rand() % 15 + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 4)){
		cout << "Greska pri izradi testnih primjera za subtask 4!" << endl;
		exit(4);
	}
	napisi_u_file(t, 4, c);
	c++;
	n = MAXN;//n = 10^15, k = 15
	k = 15;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 4)){
		cout << "Greska pri izradi testnih primjera za subtask 4!" << endl;
		exit(4);
	}
	napisi_u_file(t, 4, c);
	c++;
	n = rand() % 15 + 1;//n rand <= 15, k rand <= n
	k = rand() % n + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 4)){
		cout << "Greska pri izradi testnih primjera za subtask 4!" << endl;
		exit(4);
	}
	napisi_u_file(t, 4, c);
	c++;
	n = rand() % 15 + 1;//n rand <= 15, k rand <= n
	k = rand() % n + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 4)){
		cout << "Greska pri izradi testnih primjera za subtask 4!" << endl;
		exit(4);
	}
	napisi_u_file(t, 4, c);
	c++;
	n = veliki_rand() % MAXN + 1;//n rand <= 10^15, k <= min(n, 15), X rand < 10
	k = rand() % min(n, 15LL) + 1;
	X = rand() % 10;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 4)){
		cout << "Greska pri izradi testnih primjera za subtask 4!" << endl;
		exit(4);
	}
	napisi_u_file(t, 4, c);
	c++;
}

void gen_subtask_5(){//br = 2, 1 <= k <= n <= 10^15
	char c = 'a';
	int br = 2;
	int gran = (br == 1 ? 10 : 100);
	ll val = (ll)1e4;
	ll sad = val;
	for(int i = 0 ; i < 3 ; ++i){//n = 10^4, 10^8, 10^15, k random X random
		ll n = sad;
		ll k = veliki_rand() % n + 1;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 5)){
			cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
			exit(5);
		}
		napisi_u_file(t, 5, c);
		sad *= val;
		c++;
	}
	val = (ll)1e14;
	ll dif = (ll)9e14;
	for(int i = 0 ; i < 4 ; ++i){// 10^14 <= n < 10^15, k random
		ll n = val + veliki_rand() % dif;
		ll k = veliki_rand() % n + 1;
		ll X = rand() % gran;
		testni t = (testni){br, n, k, X};
		if(!provjeri_testni(t, 5)){
			cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
			exit(5);
		}
		napisi_u_file(t, 5, c);
		c++;
	}
	ll n = MAXN;//n = 10^15, k = 1
	ll k = 1;
	ll X = rand() % gran;
	testni t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 5)){
		cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
		exit(5);
	}
	napisi_u_file(t, 5, c);
	c++;
	n = MAXN;//n = 10^15, k rand <= 15
	k = rand() % 15 + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 5)){
		cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
		exit(5);
	}
	napisi_u_file(t, 5, c);
	c++;
	n = MAXN;//n = 10^15, k rand
	k = veliki_rand() % n + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 5)){
		cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
		exit(5);
	}
	napisi_u_file(t, 5, c);
	c++;
	n = MAXN;//n = 10^15, k = rand >= 10^15 - 15
	k = MAXN - rand() % 16;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 5)){
		cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
		exit(5);
	}
	napisi_u_file(t, 5, c);
	c++;
	n = MAXN;//n = 10^15, k = 10^15
	k = MAXN;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 5)){
		cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
		exit(5);
	}
	napisi_u_file(t, 5, c);
	c++;
	n = 10;//n = 10, k rand <= n
	k = rand() % n + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 5)){
		cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
		exit(5);
	}
	napisi_u_file(t, 5, c);
	c++;
	n = 100;//n = 100, k rand <= n
	k = rand() % n + 1;
	X = rand() % gran;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 5)){
		cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
		exit(5);
	}
	napisi_u_file(t, 5, c);
	c++;
	n = veliki_rand() % MAXN + 1;//n rand <= 10^15, k <= n, X rand < 10
	k = veliki_rand() % n + 1;
	X = rand() % 10;
	t = (testni){br, n, k, X};
	if(!provjeri_testni(t, 5)){
		cout << "Greska pri izradi testnih primjera za subtask 5!" << endl;
		exit(5);
	}
	napisi_u_file(t, 5, c);
	c++;
}

int main(){
srand(rnd_base);
gen_dummys();
gen_subtask_1();
gen_subtask_2();
gen_subtask_3();
gen_subtask_4();
gen_subtask_5();

return 0;
}

