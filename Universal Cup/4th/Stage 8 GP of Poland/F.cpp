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
	cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = steady_clock::now();
	cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

#define int long long

const int N = 1e6 + 5;

int n, m, a[N], tin[N], low[N], timer;

vector<pair<int, int>> adj[N], g[N];

int st[N], top, comp_cnt, idx[N], val[N];
 
void tarjan(int u, int p) {
	tin[u] = low[u] = ++ timer;
	st[++ top] = u;
 
	for (auto [v, w] : adj[u]) if (v != p) {
		if (tin[v]) {
			low[u] = min(low[u], tin[v]);
		} else {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
	}
 
	if (tin[u] <= low[u]) { // no back edge
 
		++ comp_cnt;
		while (top) {
			int v = st[top --];

			idx[v] = comp_cnt;
			val[comp_cnt] += a[v];

			if (v == u) break ;
		};
 
	}
}

bool ok;

void dfs(int u, int p) {
	for (auto [v, w] : g[u]) if (v != p) {
		dfs(v, u);
		if (abs(val[v]) > w) {
			ok = 0;
		}
		val[u] += val[v];
	}

}

void Hollwo_Pelw(){
	cin >> n >> m;

	top = timer = comp_cnt = 0;
	for (int i = 1; i <= n; i++) {
		g[i].clear();
		adj[i].clear();
		idx[i] = val[i] = 0;
		tin[i] = low[i] = 0;
	}

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	tarjan(1, 0);

	for (int i = 1; i <= n; i++) {
		for (auto [j, w] : adj[i]) if (idx[i] != idx[j]) {
			g[idx[i]].push_back({idx[j], w});
			// cout << idx[i] << " -> " << idx[j] << '\n';
		}
	}

	ok = 1;
	dfs(1, 0);

	if (ok) {
		cout << "TAK\n";
	} else {
		cout << "NIE\n";
	}
}