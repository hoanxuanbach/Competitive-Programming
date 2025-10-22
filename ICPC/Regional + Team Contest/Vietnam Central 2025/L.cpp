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

#define int long long

const int N = 2e5 + 5;

int n, m, vc, dist[N], deg[N];

vector<pair<int, int>> adj[N];

void Hollwo_Pelw(){
	cin >> n >> m >> vc;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		deg[u] ++, deg[v] ++;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}

	memset(dist, 0x3f, sizeof dist);

	int s, t;
	cin >> s >> t;

	dist[s] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	pq.emplace(dist[s] = 0, s);

	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();

		if (dist[u] != d) continue;

		// cout << dist[u] << ' ' << u << '\n';

		if (u == t) {
			cout << fixed << setprecision(6) << (long double) dist[u] / vc - max(0ll, deg[u] - 2) << '\n';
			return ;
		}

		for (auto [v, w] : adj[u]) {
			int nd = d + w + max(0ll, deg[v] - 2) * vc;

			if (nd < dist[v]) {
				pq.emplace((dist[v] = nd), v);
			}
		}
	}
}
