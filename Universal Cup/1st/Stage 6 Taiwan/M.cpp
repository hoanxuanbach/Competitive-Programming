#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 7;

struct DisjointSet {
	vector<int> lab;
	int n;

	DisjointSet(int _n = 0) {
		n = _n;
		lab.assign(n + 1, -1);
	}

	int root(int u) {
		if (lab[u] < 0) return u;
		return lab[u] = root(lab[u]);
	}

	bool merge(int u, int v) {
		u = root(u); v = root(v);
		if (u == v) return false;
		if (lab[u] > lab[v]) swap(u, v);
		lab[u] += lab[v];
		lab[v] = u;
		return true;
	}
};

void solve() {
	int n;
	cin >> n;
	DisjointSet dsu(N);
	for (int i = 1; i <= n; ++i) {
		int p, q;
		cin >> p >> q;
		if (dsu.merge(p, q)) {
			cout << "N\n";
		} else {
			cout << "Y\n";
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("main.inp", "r", stdin);
	freopen("main.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test = 1;
	// cin >> test;
	while (test--)
		solve();
	return 0;
}