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

int n, m, k, a[N], d[N], res[N];
vector<int> adj[N];

void Hollwo_Pelw(){
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1, u, v; i <= m;  i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	queue<int> q;
	memset(d, -1, sizeof d);
	q.push(1);
	d[1] = 0;

	while (!q.empty()) {
		int u = q.front(); q.pop();

		for (int v : adj[u]) if (d[v] == -1) {
			d[v] = d[u] + 1;
			q.push(v);
		}
	}


	for (int i = 1; i <= n; i++) {
		res[a[i]] = max(res[a[i]], d[i]);
	}


	for (int i = 1; i <= k; i++) {
		cout << res[i] << " \n"[i == k];
	}
}