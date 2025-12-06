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

const int N = 2e5 + 5;

int n, m, k, ok[N], vis[N];
vector<int> adj[N], res[N], ans;

void dfs(int u) {
	vis[u] = 1;
	if (!ok[u]) return ;

	ans.push_back(u);

	for (int v : adj[u]) {
		if (!vis[v]) {
			res[u].push_back(v);
			dfs(v);
		}
	}
}

void Hollwo_Pelw(){
	cin >> n >> m >> k;
	fill(ok + 1, ok + n + 1, 1);
	for (int x; k --; ) {
		cin >> x, ok[x] = 0;
	}

	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int rt = -1;

	for (int i = 1; i <= n; i++) {
		if (ok[i]) {
			rt = i;
			break ;
		}
	}

	if (rt == -1) {
		cout << "No\n";
		return ;
	}

	dfs(rt);

	int cnt = 0;

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			cout << "No\n";
			return ;
		}
		cnt += !res[i].empty();
	}

	cout << "Yes\n";

	cout << cnt << '\n';
	for (int i : ans) if (!res[i].empty()) {
		cout << i << " " << res[i].size() << " ";
		for (int j : res[i]) {
			cout << j << " ";
		}
		cout << '\n';
	}
}
