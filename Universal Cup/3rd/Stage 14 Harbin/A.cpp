#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define CNT(mask) __builtin_popcount(mask)
#define BIT(x, i) (((x) >> (i)) & 1)
#define int long long

using namespace std;
const int N = 1010;

struct Edge {
	int u, v, w;
};
vector<Edge> adj[N];
int n = 0;
int id[N];
int sta, fin;
int l, r;
int root = 0;

void build(int i) {
	if (i < 0) return;
	if (id[i] != 0) return;
	id[i] = ++n;
	build(i - 1);
	adj[id[i]].push_back({id[i], i == 0 ? fin : id[i - 1], 0});
	adj[id[i]].push_back({id[i], i == 0 ? fin : id[i - 1], 1});
}

int calc(int i, bool greater, bool smaller, bool zero) {
	if (i < 0) return fin;
	if (greater && smaller) {
		build(i);
		return id[i];
	}
	int u;
	if (!zero) {
		u = ++n;
	} else {
		if (root == 0) {
			u = ++n;
			root = u;
		} else {
			u = root;
			// cout << n + 1 << " " << root << '\n';
		}
	}

	for (int j = greater ? 0 : BIT(l, i); j <= (smaller ? 1 : BIT(r, i)); j++) {
		int _g = greater || (j > BIT(l, i));
		int _s = smaller || (j < BIT(r, i));
		int _z = zero && (j == 0);
		int v = calc(i-1, _g, _s, _z);
		if (!zero || j != 0) adj[u].push_back({u, v, j});
	}
	return u;
}

void solve() {
	cin >> l >> r;

	memset(id, 0, sizeof(id));
	int lg = log2(r);

	fin = ++n;
	sta = calc(lg, false, false, true);

	cout << n << "\n";
	for (int u = 1; u <= n; u++) {
		cout << (int)adj[u].size() << " ";
		
		for (auto e : adj[u]) {
			cout << e.v << " " << e.w << " ";
		}
		cout << "\n";
	}

	cout << "\n";
}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    cin.tie(0), cout.tie(0)->sync_with_stdio(0);
    int testcases = 1;
    // cin >> testcases;
    for (int test = 1; test <= testcases; test++) {
        solve();
    }
}
