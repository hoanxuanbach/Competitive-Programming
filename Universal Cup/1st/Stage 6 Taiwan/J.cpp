#include <bits/stdc++.h>

using namespace std;
const int N = 2e6 + 7;
const int INF = 5e8 + 7;

int n, k, m, q;
int a[N], sum[N];
set<int> s;

bool check(int l, int r) {
	if (l > r) {
		return true;
	}
	auto it = s.lower_bound(l);
	if (it == s.end() || *it > r) {
		return true;
	}
	return false;
}

int distance(int u, int v) {
	if (u > v) swap(u, v);
	int res = INF;
	if (u <= n && v <= n && check(u, v - 1)) {
		res = min(res, sum[v - 1] - sum[u - 1]);
	}
	if (u <= n && v <= n && check(1, u - 1) && check(v, n)) {
		res = min(res, sum[u - 1] + sum[n] - sum[v - 1]);
	}
	if (u > n && v > n && check(u + 1, v)) {
		res = min(res, sum[v] - sum[u]);
	}
	if (u == 1 && v > n && check(n + 1, v)) {
		res = min(res, sum[v] - sum[n]);
	} 
	if (u == k && v > n && check(v + 1, n + m + 1)) {
		res = min(res, sum[n + m + 1] - sum[v]);
	}
	if (u == 1 && v == k && check(n + 1, n + m + 1)) {
		res = min(res, sum[n + m + 1] - sum[n]);
	}
	return res;
}

int query(int u, int v) {
	int res = distance(u, v);
	res = min(res, distance(u, 1) + distance(1, v));
	res = min(res, distance(u, k) + distance(k, v));
	res = min(res, distance(u, 1) + distance(1, k) + distance(k, v));
	res = min(res, distance(u, k) + distance(k, 1) + distance(1, v));
	return res;
}

void solve() {
	cin >> n >> k >> m >> q;
	for (int i = 1; i <= n + m + 1; ++i) {
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}

	for (int i = 1; i <= q; ++i) {
		char type;
		cin >> type;
		if (type == 'q') {
			int u, v;
			cin >> u >> v;
			int ans = min(query(u, v), query(v, u));
			if (ans >= INF) {
				cout << "impossible\n";
			} else {
				cout << ans << '\n';
			}
		} else if (type == 'c') {
			int i;
			cin >> i;
			if (s.count(i)) {
				s.erase(i);
			} else {
				s.insert(i);
			}
		} else {
			int j;
			cin >> j;
			j += n + 1;
			if (s.count(j)) {
				s.erase(j);
			} else {
				s.insert(j);
			}
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