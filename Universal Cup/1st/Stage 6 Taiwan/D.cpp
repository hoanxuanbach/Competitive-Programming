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

const int N = 1e4 + 5;

int n, th;
pair<int, int> nxt[N];
bitset<N> dp[N], val[6];

void Hollwo_Pelw(){
	cin >> n >> th;

	for (int i = 2; i <= n + 1; i++) {
		int x, y, z, wx;
		cin >> x >> y >> z >> wx;

		val[wx][x] = 1;
		nxt[x] = {y, z};
	}

	for (int i = n + 1; i >= 2; i--) {
		dp[i][i] = 1;
		auto [y, z] = nxt[i];

		dp[y] |= dp[i];
		dp[z] |= dp[i];
	}

	int cnt = 0;
	for (int i = 2; i <= n + 1; i++) {

		int cur = 0;
		for (int w = 1; w <= 5; w++) {
			cur += w * (val[w] & dp[i]).count();
		}

		if (cur >= th) {
			cout << i << ' ' << cur << '\n';
			cnt ++;
		}
	}
	cout << cnt << '\n';
}
