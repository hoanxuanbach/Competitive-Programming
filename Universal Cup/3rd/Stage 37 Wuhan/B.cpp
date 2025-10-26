#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;

void Hollwo_Pelw();

signed main(){
#ifndef hollwo_pelw_local
	if (fopen(".inp", "r"))
		assert(freopen(".inp", "r", stdin)), assert(freopen(".out", "w", stdout));
#else
	using namespace chrono;
	auto start = steady_clock::now();
#endif
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
	int testcases = 1;
	// cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = steady_clock::now();
	cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

const int N = 2e5 + 5, K = 11;

int dsu_par[N];

inline int find(int u) {
	return dsu_par[u] == u ? u : dsu_par[u] = find(dsu_par[u]);
}

int n, k, eu[N], ev[N], par[N];
vector<int> adj[N];

int dp[N][K];
long long res = 0;

void dfs(int u, int p) {
	par[u] = p;
	dp[u][0] = 1;

	for (int v : adj[u]) if (v != p) {
		dfs(v, u);
		for (int i = 1; i <= k; i++) {
			res += 1ll * dp[u][i - 1] * dp[v][k - i];
		}
		for (int i = 1; i <= k; i++) {
			dp[u][i] += dp[v][i - 1];
		}
	}
}

// make sure dsu_par[u] = u
long long calc(int v, int u, int offset) {
	long long ans = 0;

	for (int p = u, i = offset, last = v; p && i <= k; i++, last = p, p = find(par[p])) {
		for (int x = 0; x <= k - i; x++) {
			int sub = (x == k - i || (offset == 0 && last == v)) ? 0 : dp[last][k - i - x - 1];
			ans += 1ll * dp[v][x] * (dp[p][k - i - x] - sub);
		}

	}

	return ans;
}

void update(int v, int u, int offset, int sgn) {
	for (int p = u, i = offset; p && i <= k; i++, p = find(par[p])) {
		for (int x = i; x <= k; x++) {
			dp[p][x] += sgn * dp[v][x - i];
		}
	}
}

void Hollwo_Pelw(){
	cin >> n >> k;
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		eu[i] = u;
		ev[i] = v;
	}

	for (int i = 1; i <= n; i++) {
		dsu_par[i] = i;
	}

	dfs(1, 0);

	for (int _ = 1; _ < n; _++) {
		int i; cin >> i;
		i = (i + res) % (n - 1) + 1;

		int u = eu[i], v = ev[i];

		if (par[u] == v) {
			swap(u, v);
		}

		v = find(v), u = find(u);

		res -= calc(v, u, 1);
		update(v, u, 1, -1);

		res += calc(v, u, 0);
		update(v, u, 0, +1);

		dsu_par[v] = u;

		cout << res << '\n';
	}
}