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

void Hollwo_Pelw(){
	int n; cin >> n;
	vector<int> l(n + 1), r(n + 1);

	for (int i = 1; i <= n; i++) {
		cin >> l[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> r[i];
	}


	vector<vector<int>> dp(n + 1, vector<int>(3, 1e18));

	vector<int> lst(n + 1), len(n + 1);
	len[0] = 1;

	for (int i = 1; i <= n; i++) {
		len[i] = r[i] - l[i] + 1;
		lst[i] = (l[i] == r[i] && l[i] == l[i - 1] && r[i] == r[i - 1]) ? lst[i - 1] : i;
	}

	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {

		for (int cnt = 10, j = lst[i] - 1; cnt -- && j >= 0; j = lst[j] - 1) {

			// cout << "UPDATE " << i << ' ' << j << '\n';

			if (len[i] >= 3 && len[j] >= 3) {
				dp[i][0] = min(dp[i][0], dp[j][0] + (i - j) * (i - j));
			} else if (len[i] >= 3) {
				for (int vj = 0; vj < len[j]; vj++) {
					dp[i][0] = min(dp[i][0], dp[j][vj] + (i - j) * (i - j));
				}
			} else if (len[j] >= 3) {
				for (int vi = 0; vi < len[i]; vi++) {
					dp[i][vi] = min(dp[i][vi], dp[j][0] + (i - j) * (i - j));
				}
			} else {
				for (int vi = 0; vi < len[i]; vi++) {
					for (int vj = 0; vj < len[j]; vj++) {
						if (l[i] + vi != l[j] + vj) {
							dp[i][vi] = min(dp[i][vi], dp[j][vj] + (i - j) * (i - j));
						}
					}
				}
			}

		}

		// cout << dp[i][0] << ' ' << dp[i][1] << ' ' << dp[i][2] << '\n';
	}

	cout << *min_element(dp[n].begin(), dp[n].end()) << '\n';
}