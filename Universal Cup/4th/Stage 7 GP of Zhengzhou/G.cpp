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

const int N = 1 << 10, inf = 4e18;

int a, b, c, dist[N][N]; // [rem][last]

void Hollwo_Pelw(){
	cin >> a >> b >> c;

	int s = 1;
	while (s <= b) {
		s <<= 1;
	}

	for (int i = 0; i < b; i++) {
		for (int j = 0; j < s; j++) {
			dist[i][j] = inf;
		}
	}

	auto rem = [&](int x) { return x % b; };
	auto lst = [&](int x) { return x & (s - 1); };

	priority_queue<tuple<int, int, int>> pq;

	pq.emplace(-a, rem(a), lst(a));
	dist[rem(a)][lst(a)] = a;

	while (!pq.empty()) {
		auto [x, i, j] = pq.top(); pq.pop();
		x = -x;

		if (dist[i][j] != x) continue;

		{
			int y = x + b;
			if (y < dist[rem(y)][lst(y)]) {
				pq.emplace(-y, rem(y), lst(y));
				dist[rem(y)][lst(y)] = y;
			}
		}
		{
			int y = x ^ b;
			if (y < dist[rem(y)][lst(y)]) {
				pq.emplace(-y, rem(y), lst(y));
				dist[rem(y)][lst(y)] = y;
			}
		}
	}

	for (int i = 0; i < s; i++) {
		if (dist[rem(c)][i] <= c) {
			cout << "YES\n";
			return ;
		}
	}
	cout << "NO\n";
}