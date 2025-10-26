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

int n, k, res[55][55];

void Hollwo_Pelw(){
	cin >> n >> k;
	if (k >= n && k <= n * n - n + 1) {
		vector<int> used(n * n + 1, 0);

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				res[i][j] = 0;
			}
		}

		for (int i = 1, t = k; i <= n; i++) {
			res[i][i] = t;
			used[t ++] = 1;
		}

		for (int i = 1, t = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (res[i][j]) continue;

				while (t <= n * n && used[t]) t++;
				res[i][j] = t ++;
			}
		}

		cout << "Yes\n";
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cout << res[i][j] << " \n"[j == n];
			}
		}
	} else {
		cout << "No\n";
	}
}