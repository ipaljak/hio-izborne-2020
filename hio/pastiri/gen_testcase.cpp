#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

mt19937 engine;

int rand_int(int lo, int hi) {
    uniform_int_distribution distribution(lo, hi);
    return distribution(engine);
}

void output(vector<pii> edges, vi sheep, bool shuffle_labels = true) {
    if (shuffle_labels) {
        vi p(edges.size() + 2);
        iota(p.begin() + 1, p.end(), 1);
        shuffle(p.begin() + 1, p.end(), engine);

        for (auto& e : edges) {
            e.fi = p[e.fi];
            e.se = p[e.se];
        }
        for (auto& s : sheep) s = p[s];
        shuffle(edges.begin(), edges.end(), engine);
        shuffle(sheep.begin(), sheep.end(), engine);
    }

    cout << edges.size() + 1 << ' ' << sheep.size() << '\n';
    for (auto e : edges) cout << e.fi << ' ' << e.se << '\n';
    for (auto s : sheep) {
        cout << s;
        if (s != sheep.back()) cout << ' ';
        else cout << '\n';
    }
}

// d = parametar koji kontrolira dubinu, t = koliko puta random pomaknemo ovce
// (da parnosti vise ne budu dobre)
void obicno(int n, int k, int d, int t) {
    vi color(n), black;
    vector<pii> edges(n - 1);

    for (int i = 2; i <= n; i++) {
        int p = rand_int(max(1, i - d), i - 1);
        edges[i - 2] = {p, i};
        color[i - 1] = 1 - color[p - 1];
        if (color[i - 1]) black.push_back(i);
    }

    k = min(k, (int)black.size());
    shuffle(black.begin(), black.end(), engine);
    black.resize(k);
    
    while (t--) black[rand_int(0, k - 1)] = rand_int(1, n);
    sort(black.begin(), black.end());
    black.erase(unique(black.begin(), black.end()), black.end());

    output(edges, black);
}

// r = radijus za pastire, d = parametar koji kontrolira dubinu
void obicno_2(int n, int k, int r, int d) {
    vi color(n), black, sheep;
    vector<pii> edges(n - 1);

    for (int i = 2; i <= n; i++) {
        int p = rand_int(max(1, i - d), i - 1);
        edges[i - 2] = {p, i};
        color[i - 1] = 1 - color[p - 1];
        if (color[i - 1]) black.push_back(i);
    }

    vector<vi> edg(n + 1);
    for (auto& it : edges) {
        edg[it.fi].push_back(it.se);
        edg[it.se].push_back(it.fi);
    }
    vi vis(n + 1);

    shuffle(black.begin(), black.end(), engine);

    for (auto x : black) {
        queue<pii> Q;
        Q.push({x, 0});
        vis[x] = x;
        while (!Q.empty()) {
            auto [y, dist] = Q.front();
            Q.pop();
            if (dist == r) {
                sheep.push_back(y);
                if ((int)sheep.size() == k) break;
            } else {
                for (auto z : edg[y]) {
                    if (vis[z] == x) continue;
                    vis[z] = x;
                    Q.push({z, dist + 1});
                }
            }
        }
        if ((int)sheep.size() == k) break;
    }

    sort(sheep.begin(), sheep.end());
    sheep.erase(unique(sheep.begin(), sheep.end()), sheep.end());

    output(edges, sheep);
}

// m = broj krakova
void zvijezda(int n, int m) {
    int r = (n - 1) / m;
    assert(r >= 3);
    n = m * r + 1;

    vector<pii> edges(n - 1);
    vi sheep(2 * m);

    int x = 2;
    for (int i = 0; i < m; i++, x++) {
        sheep[2 * i] = x;
        sheep[2 * i + 1] = x + 2;

        for (int j = 0; j < r - 1; j++, x++) edges[x - 2] = {x, x + 1};
        edges[x - 2] = {1, x};
    }
    
    output(edges, sheep);
}

// n1 = duljina glavnog lanca, n2 = ukupna duljina nastavaka, l = max duljina
// nastavka
void gusjenica(int n1, int n2, int l) {
    vector<pii> edges;
    vi sheep;
    int n = n1 + n2;

    for (int i = 1; i < n1; i++) edges.push_back({i, i + 1});
    int x = n1 + 1;
    while (x <= n) {
        int a = rand_int(1, n1), b = rand_int(1, min(l, n - x + 1));
        if ((a + b) % 2) {
            if (a == 1) a++;
            else a--;
        }
        edges.push_back({a, x});
        for (int i = 0; i < b - 1; i++) edges.push_back({x + i, x + i + 1});
        sheep.push_back(x + b - 1);
        x += b;
    }

    output(edges, sheep);
}

// n = duljina (ukupno n(n+1)/2 + n cvorova), k = koliko jos ovaca dodam
void vodopad(int n, int k) {
    vector<pii> edges;
    vi sheep; 

    for (int i = 1; i < n; i++) edges.push_back({i, i + 1});
    int x = n + 1;
    for (int i = 1; i <= n; i++) {
        edges.push_back({i, x});
        for (int j = 0; j < i - 1; j++, x++) edges.push_back({x, x + 1});
        sheep.push_back(x++);
    }

    while (k--) sheep.push_back(2 * rand_int(1, n / 2));
    sort(sheep.begin(), sheep.end());
    sheep.erase(unique(sheep.begin(), sheep.end()), sheep.end());

    output(edges, sheep);
}

// kao vodopad ali su ovce random, n = duljina (ukupno n(n+1)/2 + n cvorova)
void vodopad_2(int n, int k) {
    vector<pii> edges;
    vi black; 

    for (int i = 1; i < n; i++) edges.push_back({i, i + 1});
    for (int i = 1; i <= n; i += 2) black.push_back(i);
    int x = n + 1;
    for (int i = 1; i <= n; i++) {
        edges.push_back({i, x});
        for (int j = 0; j < i - 1; j++, x++) {
            edges.push_back({x, x + 1});
            if (j % 2 == i % 2) black.push_back(x);
        }
        x++;
    }

    k = min(k, (int)black.size());
    shuffle(black.begin(), black.end(), engine);
    black.resize(k);

    output(edges, black);
}

// potpuno m-arno stablo
void potpuno_stablo(int n, int k, int m) {
    vi color(n + 1), black;
    vector<pii> edges(n - 1);

    for (int i = 2; i <= n; i++) {
        int p = (i - 2) / m + 1;
        edges[i - 2] = {p, i};
        color[i] = 1 - color[p];
        if (color[i]) black.push_back(i);
    }

    k = min(k, (int)black.size());
    shuffle(black.begin(), black.end(), engine);
    black.resize(k);

    output(edges, black);
}

// n = max ukupni broj čvorova, k1/k2 = broj ovaca sa svake strane, t =
// parametar koji kontrolira broj grana
void posebni_1(int n, int k1, int k2, int t) {
    int l = (n - 1 - 2 * k2) / (k1 + k2);
    assert(l >= 1);

    vi depth(n + 1);
    depth[1] = 0;

    vector<pii> edges;
    vi sheep;

    int x = 2;
    vi possible_p = {1};
    for (int i = 0; i < k1; i++) {
        int p = possible_p[rand_int(0, (int)possible_p.size() - 1)];
        if (rand_int(0, t)) p = 1;
        while (depth[p] != l) {
            edges.push_back({p, x});
            depth[x] = depth[p] + 1;
            p = x++;
            possible_p.push_back(p);
        }
        possible_p.pop_back();
        sheep.push_back(x - 1);
    }

    int x0 = x;
    possible_p = {1};
    for (int i = 0; i < k2; i++) {
        int p = possible_p[rand_int(0, (int)possible_p.size() - 1)];
        if (p == x0 - 1) p = 1;
        if (rand_int(0, t)) p = 1;
        while (depth[p] != l + 2) {
            edges.push_back({p, x});
            depth[x] = depth[p] + 1;
            p = x++;
            possible_p.push_back(p);
        }
        possible_p.pop_back();
        sheep.push_back(x - 1);
    }

    output(edges, sheep);
}

void pravac(int n, int k, bool good_parity) {
    vector<pii> edges(n - 1);
    vi sheep;

    for (int i = 1; i < n; i++) {
        edges[i - 1] = {i, i + 1};
        if (i % 2 || !good_parity) sheep.push_back(i);
    }

    shuffle(sheep.begin(), sheep.end(), engine);
    sheep.resize(k);

    output(edges, sheep, false);
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    engine.seed(atoi(argv[1]));

    string type = argv[2];
    if (type == "obicno") obicno(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    else if (type == "obicno_2") obicno_2(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    else if (type == "zvijezda") zvijezda(atoi(argv[3]), atoi(argv[4]));
    else if (type == "gusjenica") gusjenica(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    else if (type == "vodopad") vodopad(atoi(argv[3]), atoi(argv[4]));
    else if (type == "vodopad_2") vodopad_2(atoi(argv[3]), atoi(argv[4]));
    else if (type == "potpuno_stablo") potpuno_stablo(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    else if (type == "posebni_1") posebni_1(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    else if (type == "pravac") pravac(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    else assert(false);

    return 0;
}

