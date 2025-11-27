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

const int N = 1e6 + 5;

int n, q, bit[N], dp[N];
vector<int> upd[N];

void update(int p, int x) {
	for (; p <= n; p += p & -p) {
		bit[p] = max(bit[p], x);
	}
}

int query(int p) {
	int res = 0;
	for (; p; p -= p & -p) {
		res = max(res, bit[p]);
	}
	return res;
}

void Hollwo_Pelw(){
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		upd[i].clear();
		bit[i] = 0;
		dp[i] = 0;
	}
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		upd[r].push_back(l);
	}

	dp[0] = 0;

	for (int i = 1; i <= n; i++) {
		dp[i] = dp[i - 1];
		for (int j : upd[i]) {
			dp[i] = max(dp[i], query(j - 1) + 1);
		}
		update(i, dp[i]);
	}

	int res = 1;
	while ((1 << res) - 1 < dp[n]) {
		res ++;
	}
	cout << res << '\n';
}