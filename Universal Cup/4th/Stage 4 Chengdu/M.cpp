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

const int N = 3e5 + 5, inf = 1e18;

int n, m, k, a[N], dist[N], res[N], dis[N], idx[N];
vector<pair<int, int>> adj[N];

void solve(int T) {
	priority_queue<tuple<int, int, int>> pq;

	fill(dis + 1, dis + n + 1, inf);
	fill(idx + 1, idx + n + 1, -1);

	for (int i = 1; i <= k; i++) {
		pq.emplace(dis[a[i]] = 0, a[i], idx[a[i]] = i);
	}

	auto check = [&](int u, int v, int w) -> int {
		// u move to v, v come back a distance to meet u
		int du = dis[u] + w;
		int dv = dis[v];
		if (du + dist[v] > T || dv + dist[v] > T) {
			return -1;
		}
		if (du < dv) {
			// meet at v
			return 2 * T - 2 * dv;
		} else {
			// meet in w(u, v)
			return 2 * T - (du + dv);
		}
	};

	while (!pq.empty()) {
		auto [d, u, id] = pq.top(); d = -d;
		pq.pop();



		if (dis[u] != d || idx[u] != id) continue;
		
		// cout << d << ' ' << u << ' ' << id << '\n';

		for (auto [v, w] : adj[u]) {
			if (idx[v] != -1 && idx[v] != id) {

				int value = max(check(u, v, w), check(v, u, w));

				// cout << value << '\n';

				res[idx[v]] = max(res[idx[v]], value);
				res[id] = max(res[id], value);

			}
			if (d + w + dist[v] > T) continue; // cannot get to this

			int nd = d + w;
			if (dis[v] > nd) {
				pq.emplace(- (dis[v] = nd), v, idx[v] = id);
			}
		}
	}
}

void Hollwo_Pelw(){
	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++) {
		cin >> a[i];
		res[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		adj[i].clear();
	}
	for (int i = 1, u, v, w; i <= m; i++) {
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	fill(dist + 1, dist + n + 1, inf);

	priority_queue<pair<int, int>> pq;

	pq.emplace(dist[1] = 0, 1);

	while (!pq.empty()) {
		auto [d, u] = pq.top(); d = -d;
		pq.pop();

		if (dist[u] != d) continue;

		for (auto [v, w] : adj[u]) {
			int nd = d + w;
			if (dist[v] > nd) {
				pq.emplace(-(dist[v] = nd), v);
			}
		}
	}

	int T = 0;
	for (int i = 1; i <= k; i++)
		T = max(T, dist[a[i]]);

	// cout << "--------------------------\n";
	// for (int i = 1; i <= n; i++) {
	// 	cout << dist[i] << " \n"[i == n];
	// }
	// cout << T << '\n';

	solve(T);

	for (int i = 1; i <= k; i++) {
		cout << res[i] / 2 << "." << "05"[res[i] % 2] << " \n"[i == k];
	}
}