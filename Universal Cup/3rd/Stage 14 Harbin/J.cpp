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

const int N = 1e5 + 5;

int n, m, a[N], x[N], t[N], nxt[N], cur[N];

void Hollwo_Pelw(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	for (int i = 1; i <= m; i++) {
		cin >> x[i] >> t[i];
	}

	for (int i = 1; i <= n; i++) {
		cur[i] = m + 1;
	}

	for (int i = m; i >= 1; i--) {
		nxt[i] = cur[t[i]], cur[t[i]] = i;
	}

	priority_queue<pair<int, int>> pq;

	for (int i = 1; i <= n; i++) {
		pq.emplace(-cur[i], a[i]);
	}

	int res = x[m];

	for (int i = 1; i <= m; i++) {
		int dist = x[i] - x[i - 1];

		while (dist > 0 && !pq.empty()) {
			auto [nid, cost] = pq.top();
			pq.pop();
			if (-nid < i) {
				continue ;
			}
			int f = min(cost, dist);
			dist -= f;
			cost -= f;
			if (cost > 0) {
				pq.emplace(nid, cost);
			}
		}

		// cout << "FUCK " << x[i] << '\n';

		if (dist > 0) {
			res = x[i] - dist;
			break ;
		} else {
			pq.emplace(-nxt[i], a[t[i]]);
		}
	}

	while (!pq.empty()) {
		auto [nid, cost] = pq.top();
		pq.pop();
		if (-nid <= m) {
			continue ;
		}
		res += cost;
	}

	cout << res << '\n';
}
